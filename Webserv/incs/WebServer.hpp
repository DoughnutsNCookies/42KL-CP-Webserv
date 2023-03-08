/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:25:05 by schuah            #+#    #+#             */
/*   Updated: 2023/03/08 21:47:53 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <string>
# include <sstream>
# include <fstream>
# include <vector>
# include <unistd.h>
# include <netdb.h>
# include <poll.h>
# include <fcntl.h>


# include "../incs/ConfigManager.hpp"
# include "../incs/HttpPostResponse.hpp"
# include "../incs/HttpDefaultResponse.hpp"
# include "webserv.hpp"

# define WS_DOMAIN		AF_INET
# define WS_TYPE		SOCK_STREAM
# define WS_PROTOCOL	0
# define WS_FLAGS		AI_PASSIVE
# define WS_SERVER_NAME	"localhost"
# define WS_BACKLOG		10
# define WS_PORT		8082
# define WS_BUFFER_SIZE	30000
# define WS_TIMEOUT		10000

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
		void				_serverLoop();

		std::string					_configFilePath, _path;
		std::vector<int>			_serverFd;
		int							_newSocket;
		std::vector<sockaddr_in>	_serverAddr;
		pollfd						_fds[1];
		ConfigManager				_configManager;
};

#endif
