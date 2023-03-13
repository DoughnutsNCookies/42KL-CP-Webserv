/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpGetResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:20:41 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 18:39:26 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPGETRESPONSE_HPP
# define HTTPGETRESPONSE_HPP

# include "WebServer.hpp"

class HttpGetResponse
{
	public:
		HttpGetResponse(std::string path, int socket);
		~HttpGetResponse();
		void		handleGet();

	private:
		int			_socket;
		std::string	_path;
};

#endif
