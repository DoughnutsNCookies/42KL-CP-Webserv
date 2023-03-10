/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpPostResponse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:22:30 by schuah            #+#    #+#             */
/*   Updated: 2023/03/10 13:58:37 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPOSTRESPONSE_HPP
# define HTTPPOSTRESPONSE_HPP

# include <iostream>
# include <string>
# include <unistd.h>
# include <sys/socket.h>
# include <poll.h>

# define RED			"\033[1;31m"
# define RESET			"\033[0m"
# define WS_BUFFER_SIZE	30000
# define WS_TIMEOUT		3

class HttpPostResponse
{
	public:
		HttpPostResponse(pollfd (&fds)[1], int socket, int content_length, int valread, std::string buffer);
		~HttpPostResponse();
		void	handlePost();

	private:
		int			_socket, _content_length, _valread;
		std::string	_buffer;
		pollfd		(&_fds)[1];
};

#endif
