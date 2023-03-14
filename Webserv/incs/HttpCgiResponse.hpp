/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpCgiResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:54:29 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 20:50:14 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPCGIRESPONSE_HPP
# define HTTPCGIRESPONSE_HPP

# include "WebServer.hpp"

class HttpCgiResponse
{
	public:
		HttpCgiResponse(std::string path, std::string method, int socket, EuleeHand database);
		~HttpCgiResponse();
		void		handleCgi();

	private:
		std::string	_path, _method;
		int			_socket;
		EuleeHand	_database;
};

#endif
