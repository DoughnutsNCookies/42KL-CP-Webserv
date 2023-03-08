/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpPostResponse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:22:30 by schuah            #+#    #+#             */
/*   Updated: 2023/03/08 15:36:17 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPOSTRESPONSE_HPP
# define HTTPPOSTRESPONSE_HPP

# include <iostream>
# include <string>
# include <unistd.h>
# include <sys/socket.h>

class HttpPostResponse
{
	public:
		HttpPostResponse(int socket, int content_length, int valread, std::string buffer);
		~HttpPostResponse();
		void	handlePost();

	private:
		int					_socket, _content_length, _valread;
		std::string			_buffer;
};

#endif
