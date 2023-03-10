/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDefaultResponse.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:39:08 by schuah            #+#    #+#             */
/*   Updated: 2023/03/10 19:39:37 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpDefaultResponse.hpp"

HttpDefaultResponse::HttpDefaultResponse(int socket) : _socket(socket) {}

HttpDefaultResponse::~HttpDefaultResponse() {}

/* TO BE REMOVED */
int	ft_select(int fd, void *buffer, size_t size, Mode mode)
{
	fd_set readFds, writeFds;
    FD_ZERO(&readFds);
    FD_ZERO(&writeFds);
    if (mode == READ)
        FD_SET(fd, &readFds);
    else if (mode == WRITE)
        FD_SET(fd, &writeFds);

    timeval	timeout;
    timeout.tv_sec = WS_TIMEOUT;
    timeout.tv_usec = 0;

    int ret = select(FD_SETSIZE, &readFds, &writeFds, NULL, &timeout);
    if (ret == -1)
	{
        std::cerr << "Error: select() failed.\n";
        return (-1);
    }
    else if (ret == 0)
	{
        std::cout << "Select timeout.\n";
        return (0);
    }

	for (int i = 0; i < FD_SETSIZE; i++)
	{
		if (FD_ISSET(fd, &readFds) && mode == READ && i == fd)
			return (read(fd, buffer, size));
		else if (FD_ISSET(fd, &writeFds) && mode == WRITE && i == fd)
			return (write(fd, buffer, size));
	}
    return (0);
}

void	HttpDefaultResponse::handleDefault()
{
	std::string http = "HTTP/1.1 200 OK\n";
	std::string message = "This should display the default page";
	std::string content_length_str = "Content-Length: " + std::to_string(message.length()) + "\n\n";
	std::string output = http + content_length_str + message;

	ft_select(this->_socket, (void *)output.c_str(), output.length(), WRITE);
	close(this->_socket);
}
