/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:25:05 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 19:04:27 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
# include <vector>
# include <unistd.h>
# include <netdb.h>
# include <fcntl.h>
# include <sys/socket.h>

# include "webserv.hpp"
# include "ConfigManager.hpp"
# include "HttpPostResponse.hpp"
# include "HttpDefaultResponse.hpp"
# include "HttpCgiResponse.hpp"
# include "HttpGetResponse.hpp"
# include "HttpDeleteResponse.hpp"
# include "HttpHeadResponse.hpp"

# define WS_DOMAIN				AF_INET
# define WS_TYPE				SOCK_STREAM
# define WS_PROTOCOL			0
# define WS_FLAGS				AI_PASSIVE
# define WS_SERVER_NAME			"localhost"
# define WS_BACKLOG				10
# define WS_PORT				8080
# define WS_BUFFER_SIZE			30000
# define WS_TIMEOUT				3
# define DEFAULT_CONFIG_PATH	"conf/default.conf"

/* TO BE REMOVED */
enum	Mode
{
	READ,
	WRITE
};
#include <string>
void	perrorExit(std::string msg, int exitTrue = 1);
long	ft_select(int fd, void *buffer, size_t size, Mode mode);

class WebServer
{
	public:
		WebServer(std::string configFilePath);
		~WebServer();
		void						runServer();

	private:
		void						_setupServer();
		int							_unchunkResponse();
		void						_serverLoop();

		std::string					_configFilePath, _path, _buffer;
		std::vector<int>			_serverFd;
		int							_socket;
		std::vector<sockaddr_in>	_serverAddr;
		ConfigManager				_configManager;
};

#endif
