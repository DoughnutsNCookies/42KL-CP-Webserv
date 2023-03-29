# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 17:38:48 by jhii              #+#    #+#              #
#    Updated: 2023/03/24 16:16:23 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	webserv
CXX			=	g++
CXXFLAGS	=	-Wall -Wextra -Werror -Wshadow -std=c++98 -pedantic
ifeq ($(DB), 1)
    CXXFLAGS += -fsanitize=thread -g3
endif
INCLUDES	=	-Iincs
RM			=	rm -rf
MKDIR		=	mkdir -p
SRC_PATH	=	srcs
OBJ_PATH	=	objs
ANNOYING	=	*.dSYM ../.vscode
MAIN		=	srcs/main.cpp
SRC			=	WebServer.cpp \
				ConfigManager.cpp \
				Token.cpp \
				Cookies.cpp \
				EuleeHand.cpp \
				EuleePocket.cpp \
				EuleeWallet.cpp \
				HttpPostResponse.cpp \
				HttpCgiResponse.cpp \
				HttpGetResponse.cpp \
				HttpDeleteResponse.cpp \
				HttpHeadResponse.cpp \
				HttpPutResponse.cpp
OBJ			=	${addprefix ${OBJ_PATH}/, ${SRC:.cpp=.o}}

all: 
	${MKDIR} ${OBJ_PATH}
	make ${NAME}
	./${NAME}

${NAME}: ${OBJ} $(MAIN)
	${CXX} ${CXXFLAGS} ${INCLUDES} ${MAIN} ${OBJ} -o ${NAME}

${OBJ_PATH}/%.o: ${SRC_PATH}/%.cpp
	${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@

test: fclean all
	./${NAME}

clean:
	${RM} ${ANNOYING} ${OBJ_PATH}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY = all clean fclean re