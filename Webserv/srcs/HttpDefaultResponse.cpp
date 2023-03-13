/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDefaultResponse.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:39:08 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 18:48:59 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpDefaultResponse.hpp"

HttpDefaultResponse::HttpDefaultResponse(int socket) : _socket(socket) {}

HttpDefaultResponse::~HttpDefaultResponse() {}

void	HttpDefaultResponse::handleDefault()
{
	std::string http = "HTTP/1.1 200 OK\r\n";
	std::string message = "This should display the default page";
	std::string content_length_str = "Content-Length: " + std::to_string(message.length()) + "\r\n\r\n";
	std::string output = http + content_length_str + message;

	ft_select(this->_socket, (void *)output.c_str(), output.length(), WRITE);
	close(this->_socket);
}
