/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDefaultResponse.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:39:08 by schuah            #+#    #+#             */
/*   Updated: 2023/03/08 17:34:38 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpDefaultResponse.hpp"

HttpDefaultResponse::HttpDefaultResponse(pollfd (&fds)[1], int socket) : _fds(fds), _socket(socket) {}

HttpDefaultResponse::~HttpDefaultResponse() {}

void	HttpDefaultResponse::handleDefault()
{
	std::string http = "HTTP/1.1 200 OK\n";
	std::string message = "This should display the default page";
	std::string content_length_str = "Content-Length: " + std::to_string(message.length()) + "\n\n";
	std::string output = http + content_length_str + message;

	int	ret = poll(this->_fds, 1, WS_TIMEOUT);
	if (ret == -1)
		std::cout << RED << "Poll error" << RESET << std::endl;
	else if (ret == 0)
		std::cout << RED << "Poll timeout" << RESET << std::endl;
	else if (this->_fds[0].revents & POLLOUT)
	{
		write(this->_socket, output.c_str(), output.length());
		std::cout << "Default page sent" << std::endl;
	}
	close(this->_socket);
}
