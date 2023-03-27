/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:25:05 by schuah            #+#    #+#             */
/*   Updated: 2023/03/25 20:14:52 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <filesystem>
# include <iostream>
# include <sstream>
# include <fstream>
# include <cstring>
# include <string>
# include <limits>
# include <vector>
# include <map>
# include <sys/socket.h>
# include <unistd.h>
# include <netdb.h>
# include <fcntl.h>

# include "webserv.hpp"
# include "ConfigManager.hpp"
# include "EuleeHand.hpp"
# include "EuleeWallet.hpp"
# include "HttpPostResponse.hpp"
# include "HttpCgiResponse.hpp"
# include "HttpGetResponse.hpp"
# include "HttpDeleteResponse.hpp"
# include "HttpHeadResponse.hpp"
# include "HttpPutResponse.hpp"

# define WS_BACKLOG				10
# define WS_BUFFER_SIZE			100000
# define WS_TESTER_SIZE			100000
# define WS_TEMP_FILE_IN		".tempIn"
# define WS_TEMP_FILE_OUT		".tempOut"
# define DEFAULT_CONFIG_PATH	"conf/default.conf"

class WebServer
{
	public:
		WebServer(std::string configFilePath, char **envp);
		~WebServer();
		void			runServer();

	private:
		void			_setupServer();
		void			_acceptConnection(int fd);
		void			_receiveRequest();
		void			_sendResponse();
		void			_serverLoop();
		void			_doRequest();
		int				_parseRequest();
		int				_handleFavicon();
		int				_handleRedirection();

		ConfigManager	_configManager;
		EuleeHand		_database;
};

#endif
