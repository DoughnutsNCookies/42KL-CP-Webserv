/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:25:05 by schuah            #+#    #+#             */
/*   Updated: 2023/03/10 21:09:21 by schuah           ###   ########.fr       */
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
# include <fcntl.h>

# include "../incs/ConfigManager.hpp"
# include "../incs/HttpPostResponse.hpp"
# include "../incs/HttpDefaultResponse.hpp"
# include "../incs/HttpCgiResponse.hpp"
# include "../incs/HttpGetResponse.hpp"
# include "webserv.hpp"

# define WS_DOMAIN		AF_INET
# define WS_TYPE		SOCK_STREAM
# define WS_PROTOCOL	0
# define WS_FLAGS		AI_PASSIVE
# define WS_SERVER_NAME	"localhost"
# define WS_BACKLOG		10
# define WS_PORT		8081
# define WS_BUFFER_SIZE	30000
# define WS_TIMEOUT		3

/* TO BE REMOVED */
enum	Mode
{
	READ,
	WRITE
};

class WebServer
{
	public:
		WebServer(std::string configFilePath);
		~WebServer();
		void	runServer();

	private:
		void				_perrorExit(std::string msg, int exitTrue = 1);
		void				_setupServer();
		void				_serverLoop();
		long				ft_select2(int fd, void *buffer, size_t size, Mode mode);

		std::string					_configFilePath, _path;
		std::vector<int>			_serverFd;
		int							_socket;
		std::vector<sockaddr_in>	_serverAddr;
		ConfigManager				_configManager;
};

#endif
