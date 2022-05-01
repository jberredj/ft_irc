# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 15:10:09 by ddiakova          #+#    #+#              #
#    Updated: 2022/05/01 16:00:30 by ddiakova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= parsing

SRCS			= main1.cpp \
					command.cpp			
				
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