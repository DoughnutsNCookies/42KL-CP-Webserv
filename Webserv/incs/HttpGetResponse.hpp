/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpGetResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:20:41 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 20:54:18 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPGETRESPONSE_HPP
# define HTTPGETRESPONSE_HPP

# include "WebServer.hpp"

class HttpGetResponse
{
	public:
		HttpGetResponse(std::string path, int socket, EuleeHand database);
		~HttpGetResponse();
		void		handleGet();

	private:
		int			_socket;
		std::string	_path;
		EuleeHand	_database;
};

#endif
