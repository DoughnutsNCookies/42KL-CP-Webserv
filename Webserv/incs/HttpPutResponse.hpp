/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpPutResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:00:35 by schuah            #+#    #+#             */
/*   Updated: 2023/03/14 14:51:22 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPUTRESPONSE_HPP
# define HTTPPUTRESPONSE_HPP

# include "WebServer.hpp"

class HttpPutResponse
{
	public:
		HttpPutResponse(int socket, std::string buffer, std::string path, EuleeHand database);
		~HttpPutResponse();
		void		handlePut();

	private:
		int			_socket;
		std::string	_buffer, _path;
		EuleeHand	_database;
};

#endif
