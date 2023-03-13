/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDeleteResponse.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:22:15 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 18:39:28 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPDELETERESPONSE_HPP
# define HTTPDELETERESPONSE_HPP

# include "WebServer.hpp"

class HttpDeleteResponse
{
	public:
		HttpDeleteResponse(int socket, std::string path);
		~HttpDeleteResponse();
		void	handleDelete();

	private:
		int		_socket;
		std::string	_path;
};

#endif
