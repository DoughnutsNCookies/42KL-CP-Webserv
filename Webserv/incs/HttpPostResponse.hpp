/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpPostResponse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:22:30 by schuah            #+#    #+#             */
/*   Updated: 2023/03/11 15:13:23 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPOSTRESPONSE_HPP
# define HTTPPOSTRESPONSE_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <unistd.h>
# include <sys/socket.h>

# define RED			"\033[1;31m"
# define RESET			"\033[0m"
# define WS_BUFFER_SIZE	30000
# define WS_TIMEOUT		3

class HttpPostResponse
{
	public:
		HttpPostResponse(int socket, std::string buffer);
		~HttpPostResponse();
		void	handlePost();

	private:
		void		_saveFile(size_t contentLength, int contentLengthSpecified);
		int			_socket;
		std::string	_buffer;
};

#endif
