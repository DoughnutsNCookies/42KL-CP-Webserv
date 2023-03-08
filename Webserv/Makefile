# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 17:38:48 by jhii              #+#    #+#              #
#    Updated: 2023/03/08 15:48:02 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	webserv
CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -Wshadow -std=c++98 -pedantic
ifeq ($(DB), 1)
    CXXFLAGS += -fsanitize=thread -g3
endif
INCLUDES	=	-Iincs
RM			=	rm -rf
MKDIR		=	mkdir -p

SRC_PATH	=	srcs
OBJ_PATH	=	objs
ANNOYING	=	*.dSYM .vscode
MAIN		=	srcs/main.cpp
SRC			=	WebServer.cpp \
				ConfigManager.cpp \
				Token.cpp \
				HttpPostResponse.cpp \
				HttpDefaultResponse.cpp
OBJ			=	${addprefix ${OBJ_PATH}/, ${SRC:.cpp=.o}}

all: ${NAME}

${NAME}: ${OBJ} $(MAIN)
	${CXX} ${CXXFLAGS} ${INCLUDES} ${MAIN} ${OBJ} -o ${NAME}

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