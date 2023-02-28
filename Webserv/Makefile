# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 17:38:48 by jhii              #+#    #+#              #
#    Updated: 2023/02/28 18:01:09 by jhii             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	webserv
CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -Wshadow -std=c++98 -pedantic
CXXFLAGS	=	-fsanitize=address -g3
INCLUDES	=	-Iincs
RM			=	rm -rf
MKDIR		=	mkdir -p

SRC_PATH	=	srcs
OBJ_PATH	=	objs
ANNOYING	=	*.dSYM .vscode
MAIN		=	srcs/main.cpp
SRC			=	
OBJ			=	${addprefix ${OBJ_PATH}/, ${SRC:.cpp=.o}}

all: ${NAME}

${NAME}: ${OBJ} $(MAIN)
	${CXX} ${CXXFLAGS} ${INCLUDES} -o ${NAME} ${MAIN} ${OBJ}

${OBJ_PATH}/%.o: ${SRC_PATH}/%.cpp
	${MKDIR} ${@D}
	${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@

test: fclean all
	./${NAME}

clean:
	${RM} ${ANNOYING} ${OBJ_PATH}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY = all clean fclean re