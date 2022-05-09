# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/12 17:39:23 by jberredj          #+#    #+#              #
#    Updated: 2022/05/09 18:32:48 by jberredj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	ircserv

CXX				=	c++
OPTI			=	-O3
CXXFLAGS		=	-Wall -Werror -Wextra -std=c++98 $(OPTI)
LDFLAGS			=	

SRC_DIR			= 	srcs
INC_DIR			=	includes
OBJ_DIR			=	objs/

LIBS			=	



###############################################################################
##								Source files								 ##
###############################################################################

TYPES				=   Nullptr_t.cpp 
TYPES_SRCS			=   $(addprefix srcs/types/, $(TYPES))
TYPES_OBJS			=   $(addprefix objs/types., $(subst /,., $(TYPES:.cpp=.o)))

MAIN				=   main.cpp IrcServ.cpp User.cpp Logger.cpp
MAIN_SRCS			=   $(addprefix srcs/, $(MAIN))
MAIN_OBJS			=   $(addprefix objs/, $(subst /,., $(MAIN:.cpp=.o)))

SRCS				= 	$(TYPES_SRCS) $(MAIN_SRCS)
OBJS				=	$(TYPES_OBJS) $(MAIN_OBJS) 

###############################################################################
##							Color output char								 ##
###############################################################################
BLUE			=\033[0;34m
NC				=\033[0m
LIGHT_PURPLE	=\033[1;35m
GREEN			=\033[0;32m
RED				=\033[0;31m

###############################################################################
## 							Mandatory recipes								 ##
###############################################################################

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBS) $(OBJS)
	printf "$(BLUE)Linking $(LIGHT_PURPLE)$(NAME) $(BLUE)executable$(NC)\n"
	$(CXX) -I $(INC_DIR) $(OBJS) $(LIBS) $(LDFLAGS) $(CXXFLAGS) -o $(NAME)
	printf "$(GREEN)Completed$(NC)\n"

clean:
	printf "$(RED)Removing objects files$(NC)\n"
	rm -rf objs
	rm -rf *.o;

fclean: clean
	printf "$(RED)Removing $(LIGHT_PURPLE)$(NAME) \
	$(RED)executable\nRemoving libraries$(NC)\n"	
	rm -rf $(NAME)
	rm -rf $(LIBS)

re: fclean all

###############################################################################
## 								Extra recipes								 ##
###############################################################################

define COMPILE
	find ./objs/ -type f -exec touch {} +
	$(foreach source,$?, \
	printf "$(YELLOW)[..]   $(NC) $(LIGHT_PURPLE)$(subst srcs/,,$(source))\
$(NC)\n"; \
	$(CXX) -I $(INC_DIR) $(CXXFLAGS) -c $(source) -o \
$(addprefix $(OBJ_DIR), $(subst /,.,$(subst srcs/,,$(source:.cpp=.o)))) ; \
	if [ $$? -ne "0" ];\
	then \
		exit 1;\
	fi; \
	norminette $(source) > /dev/null ;\
	if [ $$? -ne "0" ];\
	then \
		printf "\033[F$(RED)[NORM]$(NC) $(LIGHT_PURPLE)\
$(subst srcs/,,$(source))$(NC)\n";\
	else \
		printf "\033[F$(GREEN)[OK]  $(NC) $(LIGHT_PURPLE)\
$(subst srcs/,,$(source))$(NC)\n";\
	fi;)
endef

types: $(OBJ_DIR) $(TYPES_OBJS)
$(TYPES_OBJS): $(TYPES_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)types $(BLUE)functions$(NC)\n"
	$(COMPILE)

main: $(OBJ_DIR) $(MAIN_OBJS)
$(MAIN_OBJS): $(MAIN_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)main $(BLUE)functions$(NC)\n"
	$(COMPILE)

ffclean: fclean
	make -C libs/libft fclean
	make -C libs/minilibx-linux clean

$(SRCS): $(addprefix $(INC_DIR)/, $(HEADERS))
 
libft.a:
	make -C libs/libft ft_io ft_string ft_to ft_ctype get_next_line lib
	cp libs/libft/libft.a .

libmlx.a:
	make -C libs/minilibx-linux
	cp libs/minilibx-linux/libmlx.a .

debug: CXXFLAGS = -std=c++98 -g
debug: all

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.SILENT:

commit_all_files: ffclean
	git add .
	git commit

###############################################################################
## 								Norm recipe									 ##
###############################################################################

norm:
	printf "$(BLUE)Checking norm$(NC)\n"
	norminette $(SRCS) $(addprefix $(INC_DIR)/, $(filter-out mlx.h, $(HEADERS))) \
	; if [ "$$?" -ne "0" ]; then printf "$(RED)NORM ERROR$(NC)\n"; \
	else printf "$(GREEN)NORM OK$(NC)\n";fi
