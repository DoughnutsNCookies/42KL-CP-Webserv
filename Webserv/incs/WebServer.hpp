/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:25:05 by schuah            #+#    #+#             */
/*   Updated: 2023/03/07 19:32:27 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <string>
# include <sstream>
# include <fstream>

# include <unistd.h>
# include <netdb.h>

# include "ConfigManager.hpp"

# define RED			"\033[1;31m"
# define RESET			"\033[0m"
# define WS_DOMAIN		AF_INET
# define WS_TYPE		SOCK_STREAM
# define WS_PROTOCOL	0
# define WS_FLAGS		AI_PASSIVE
# define WS_SERVER_NAME	"localhost"
# define WS_BACKLOG		10
# define WS_PORT		8080
# define WS_BUFFER_SIZE	30000

class WebServer
{
	public:
		WebServer(std::string configFilePath);
		~WebServer();
		void	runServer();

	private:
		void				_perrorExit(std::string msg);
		void				_setupServer();
		void				_handleCgi(std::string method, int contentLength);
		int					_handleGet();
		void				_handlePost(std::string buffer, int content_length, int valread);
		void				_serverLoop();

		std::string			_configFilePath, _path;
		int					_serverFd, _newSocket;
		struct sockaddr_in	_serverAddr;
		ConfigManager		_configManager;
};

#endif
