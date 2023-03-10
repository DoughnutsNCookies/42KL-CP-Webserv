/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:25:05 by schuah            #+#    #+#             */
/*   Updated: 2023/03/14 21:52:22 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <iostream>
# include <sstream>
# include <fstream>
# include <string>
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
# include "HttpDefaultResponse.hpp"
# include "HttpCgiResponse.hpp"
# include "HttpGetResponse.hpp"
# include "HttpDeleteResponse.hpp"
# include "HttpHeadResponse.hpp"
# include "HttpPutResponse.hpp"

# define WS_BACKLOG				10
# define WS_PORT				8081
# define WS_BUFFER_SIZE			30000
# define WS_TIMEOUT				3
# define DEFAULT_CONFIG_PATH	"conf/default.conf"

class WebServer
{
	public:
		WebServer(std::string configFilePath);
		~WebServer(void);
		void			runServer(void);

	private:
		int				_checkExcept(std::string method);
		int				_isCGI();
		void			_setupServer();
		void			_convertLocation();
		int				_unchunkResponse();
		void			_serverLoop();

		ConfigManager	_configManager;
		EuleeHand		_database;
};

#endif
