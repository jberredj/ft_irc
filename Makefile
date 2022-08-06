# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/12 17:39:23 by jberredj          #+#    #+#              #
#    Updated: 2022/08/06 15:37:00 by jberredj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	ircserv

CXX				=	clang++
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

CHANNEL				=	Channel.cpp
CHANNEL_SRCS		=	$(addprefix srcs/Channel/, $(CHANNEL))
CHANNEL_OBJS		=	$(addprefix objs/Channel., $(subst /,.,\
							$(CHANNEL:.cpp=.o)))

COMMANDS			=	Command.cpp UserModeCommand.cpp ChannelModeCommand.cpp
COMMANDS_SRCS		=	$(addprefix srcs/Command/, $(COMMANDS))
COMMANDS_OBJS		=	$(addprefix objs/Command., $(subst /,.,\
							$(COMMANDS:.cpp=.o)))

IRC					=	$(addprefix Messages/, $(MESSAGES))\
							$(addprefix Replies/, $(REPLIES))
MESSAGES			=	PASS.cpp USER.cpp NICK.cpp MODE.cpp PING.cpp PRIVMSG.cpp NOTICE.cpp QUIT.cpp WHOIS.cpp\
						WHOWAS.cpp JOIN.cpp helpers.cpp KILL.cpp OPER.cpp AWAY.cpp PART.cpp TOPIC.cpp INVITE.cpp KICK.cpp \
						LIST.cpp NAMES.cpp PONG.cpp
REPLIES				=	Reply.cpp ERR.cpp RPL.cpp
IRC_SRCS			=	$(addprefix srcs/Irc/, $(IRC))
IRC_OBJS			=	$(addprefix objs/Irc., $(subst /,., $(IRC:.cpp=.o)))

LOGGER				=	Logger.cpp Output.cpp
LOGGER_SRCS			=	$(addprefix srcs/Logger/, $(LOGGER))
LOGGER_OBJS			=	$(addprefix objs/Logger., $(subst /,., $(LOGGER:.cpp=.o)))

MODE				=	Mode.cpp ChannelMode.cpp UserMode.cpp
MODE_SRCS			=	$(addprefix srcs/Mode/, $(MODE))
MODE_OBJS			=	$(addprefix objs/Mode., $(subst /,., $(MODE:.cpp=.o)))

SERVER				=	ChannelInteraction.cpp run.cpp Server.cpp socketIO.cpp UserInteractions.cpp
SERVER_SRCS			=	$(addprefix srcs/Server/, $(SERVER))
SERVER_OBJS			=	$(addprefix objs/Server., $(subst /,., $(SERVER:.cpp=.o)))

TYPES				=	Nullptr_t.cpp 
TYPES_SRCS			=   $(addprefix srcs/types/, $(TYPES))
TYPES_OBJS			=   $(addprefix objs/types., $(subst /,., $(TYPES:.cpp=.o)))

USER				=	init.cpp User.cpp
USER_SRCS			=	$(addprefix srcs/User/, $(USER))
USER_OBJS			=	$(addprefix objs/User., $(subst /,., $(USER:.cpp=.o)))

MAIN				=	main.cpp
MAIN_SRCS			=   $(addprefix srcs/, $(MAIN))
MAIN_OBJS			=   $(addprefix objs/, $(subst /,., $(MAIN:.cpp=.o)))

SRCS				= 	$(CHANNEL_SRCS) $(COMMANDS_SRCS) $(IRC_SRCS) \
							$(LOGGER_SRCS) $(MODE_SRCS) $(SERVER_SRCS) \
							$(TYPES_SRCS) $(USER_SRCS) $(MAIN_SRCS) 
OBJS				= 	$(CHANNEL_OBJS) $(COMMANDS_OBJS) $(IRC_OBJS) \
							$(LOGGER_OBJS) $(MODE_OBJS) $(SERVER_OBJS) \
							$(TYPES_OBJS) $(USER_OBJS) $(MAIN_OBJS)

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

include $(DEPS_DIR)/dependencies.d

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

re: fclean
	make all

###############################################################################
## 								Extra recipes								 ##
###############################################################################

define COMPILE
	$(foreach source,$(filter-out %.hpp,$^), \
	printf "$(LIGHT_PURPLE)$(subst srcs/,,$(source))\
$(NC)\n"; \
	$(CXX) -I $(INC_DIR) $(CXXFLAGS) -c $(source) -o \
$(addprefix $(OBJ_DIR)/, $(subst /,.,$(subst srcs/,,$(source:.cpp=.o)))) ;)
endef

ffclean: fclean
	printf "$(RED)Removing $(LIGHT_PURPLE)dependencies$(NC)\n"
	rm -rf deps

$(SRCS): $(addprefix $(INC_DIR)/, $(HEADERS))

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

.PHONY:
.SILENT:

commit_all_files: ffclean
	git add .
	git commit