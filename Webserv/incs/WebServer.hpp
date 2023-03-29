/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:25:05 by schuah            #+#    #+#             */
/*   Updated: 2023/03/29 12:47:28 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include "http.hpp"
# include "EuleeHand.hpp"

class WebServer
{
	public:
		WebServer(std::string configFilePath);
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

		EuleeHand		_database;
};

#endif
