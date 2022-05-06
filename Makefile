# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 15:10:09 by ddiakova          #+#    #+#              #
#    Updated: 2022/05/06 21:34:13 by ddiakova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= parsing

SRCS			= main2.cpp \
					Command.cpp	\
					User.cpp

HEADERS			= User.hpp		
				
CC 				= c++

CFLAGS 			= -g -Wall -Werror -Wextra -std=c++98

RM 				= rm -rf

OBJS            = $(SRCS:%.cpp=%.o)

all : $(NAME)

$(NAME):    $(OBJS) 
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:				
				$(RM) $(OBJS)
                                
fclean:         clean 
				$(RM) $(NAME)

re:             fclean all

%.o: %.cpp
		$(CC) $(CFLAGS) -c $< -o $@

.PHONY: 		all clean fclean re