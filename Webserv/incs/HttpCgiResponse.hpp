/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpCgiResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:54:29 by schuah            #+#    #+#             */
/*   Updated: 2023/03/09 11:32:28 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPCGIRESPONSE_HPP
# define HTTPCGIRESPONSE_HPP

# include <string>
# include <iostream>
# include <unistd.h>
# include <poll.h>

# define RED			"\033[1;31m"
# define RESET			"\033[0m"
# define WS_BUFFER_SIZE	30000
# define WS_TIMEOUT		3000

class HttpCgiResponse
{
	public:
		HttpCgiResponse(pollfd (&fds)[1], std::string path, std::string method, int socket, int contentLength);
		~HttpCgiResponse();
		void	handleCgi();

	private:
		void		_perrorExit(std::string msg);
		std::string	_path, _method;
		int			_socket, _contentLength;
		pollfd		(&_fds)[1];
};

#endif
