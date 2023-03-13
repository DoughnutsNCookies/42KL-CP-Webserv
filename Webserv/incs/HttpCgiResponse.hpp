/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpCgiResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:54:29 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 18:39:35 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPCGIRESPONSE_HPP
# define HTTPCGIRESPONSE_HPP

# include "WebServer.hpp"

class HttpCgiResponse
{
	public:
		HttpCgiResponse(std::string path, std::string method, int socket);
		~HttpCgiResponse();
		void		handleCgi();

	private:
		void		_perrorExit(std::string msg);
		std::string	_path, _method;
		int			_socket;
};

#endif
