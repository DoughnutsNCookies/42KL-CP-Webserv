/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:32:49 by jhii              #+#    #+#             */
/*   Updated: 2023/03/29 12:37:38 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# define RESET		"\033[0m"
# define BLACK		"\033[1;30m"
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define MAGENTA	"\033[1;35m"
# define CYAN		"\033[1;36m"
# define WHITE		"\033[1;37m"

# define WS_BACKLOG				10
# define WS_BUFFER_SIZE			100000
# define WS_TEMP_FILE_IN		".tempIn"
# define WS_TEMP_FILE_OUT		".tempOut"
# define WS_UNCHUNK_INFILE		".unchunkInfile"
# define WS_UNCHUNK_OUTFILE		".unchunkOutfile"
# define WS_ERROR_PAGE_PATH 	"./html/server_html/error.html"
# define WS_DEFAULT_PAGE_PATH	"./html/server_html/default.html"
# define DEFAULT_CONFIG_PATH	"conf/default.conf"

# include <map>
# include <vector>
# include <string>
# include <limits>
# include <netdb.h>
# include <sstream>
# include <fstream>
# include <cstring>
# include <iostream>
# include <algorithm>
# include <filesystem>
# include <fcntl.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>

#endif
