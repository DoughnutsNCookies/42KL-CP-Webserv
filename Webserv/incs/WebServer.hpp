/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:25:05 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 20:47:49 by schuah           ###   ########.fr       */
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
# include "EuleeHand.hpp"
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

class WebServer
{
	public:
		WebServer(std::string configFilePath);
		~WebServer(void);
		void					runServer(void);

	private:
		void						_setupServer();
		int							_unchunkResponse();
		void						_serverLoop();

		std::string					_path, _buffer;
		std::vector<int>			_serverFd;
		int							_socket;
		std::vector<sockaddr_in>	_serverAddr;
		ConfigManager				_configManager;
		EuleeHand					_database;
};

#endif
