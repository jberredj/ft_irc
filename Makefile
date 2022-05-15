# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/12 17:39:23 by jberredj          #+#    #+#              #
#    Updated: 2022/05/16 01:51:50 by jberredj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	ircserv

CXX				=	c++
OPTI			=	-O3
CXXFLAGS		=	-Wall -Werror -Wextra -std=c++98 $(OPTI)
LDFLAGS			=	

SRC_DIR			= 	srcs
INC_DIR			=	includes
OBJ_DIR			=	objs
DEPS_DIR		=	deps

LIBS			=	

###############################################################################
##								Source files								 ##
###############################################################################

TYPES				=	Nullptr_t.cpp 
TYPES_SRCS			=   $(addprefix srcs/types/, $(TYPES))
TYPES_OBJS			=   $(addprefix objs/types., $(subst /,., $(TYPES:.cpp=.o)))

MAIN				=	main.cpp IrcServ.cpp User.cpp
MAIN_SRCS			=   $(addprefix srcs/, $(MAIN))
MAIN_OBJS			=   $(addprefix objs/, $(subst /,., $(MAIN:.cpp=.o)))

COMMANDS			=	Command.cpp Pass.cpp
COMMANDS_SRCS		=	$(addprefix srcs/Commands/, $(COMMANDS))
COMMANDS_OBJS		=	$(addprefix objs/Commands., $(subst /,., $(COMMANDS:.cpp=.o)))

LOGGER				=	Logger.cpp Output.cpp
LOGGER_SRCS			=	$(addprefix srcs/Logger/, $(LOGGER))
LOGGER_OBJS			=	$(addprefix objs/Logger., $(subst /,., $(LOGGER:.cpp=.o)))

SRCS				= 	$(TYPES_SRCS) $(MAIN_SRCS) $(LOGGER_SRCS) $(COMMANDS_SRCS)
OBJS				=	$(TYPES_OBJS) $(MAIN_OBJS) $(LOGGER_OBJS) $(COMMANDS_OBJS)

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
	$(foreach source,$(filter-out %.hpp,$?), \
	printf "$(YELLOW)[..]   $(NC) $(LIGHT_PURPLE)$(subst srcs/,,$(source))\
$(NC)\n"; \
	$(CXX) -I $(INC_DIR) $(CXXFLAGS) -c $(source) -o \
$(addprefix $(OBJ_DIR)/, $(subst /,.,$(subst srcs/,,$(source:.cpp=.o)))) ; \
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

include $(DEPS_DIR)/dependencies.d

ffclean: fclean
	printf "$(RED)Removing $(LIGHT_PURPLE)dependencies$(NC)\n"
	rm -rf deps

$(SRCS): $(addprefix $(INC_DIR)/, $(HEADERS))
 
libft.a:
	make -C libs/libft ft_io ft_string ft_to ft_ctype get_next_line lib
	cp libs/libft/libft.a .

libmlx.a:
	make -C libs/minilibx-linux
	cp libs/minilibx-linux/libmlx.a .

dependencies: $(DEPS_DIR)/dependencies.d

debug: CXXFLAGS = -std=c++98 -g
debug: all

$(DEPS_DIR)/dependencies.d: $(SRCS)
	printf "$(GREEN)Generating $(LIGHT_PURPLE)dependencies$(GREEN) file$(NC)\n"
	mkdir -p $(DEPS_DIR)
	$(foreach source,$(SRCS),\
	echo "$(subst $(SRC_DIR).,$(OBJ_DIR)/,$(subst /,.,$(dir $(source))))`\
$(CXX) -I $(INC_DIR) $(source) -MM`\n\t \$$(COMPILE)"\
	> $(DEPS_DIR)/$(subst /,.,$(subst srcs/,,$(source:.cpp=.d)));)
	cd $(DEPS_DIR)&& cat `ls | grep -v dependencies.d` > dependencies.d

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.SILENT:

commit_all_files: ffclean
	git add .
	git commit