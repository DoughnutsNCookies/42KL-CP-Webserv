/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDefaultResponse.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:39:08 by schuah            #+#    #+#             */
/*   Updated: 2023/03/08 15:50:24 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpDefaultResponse.hpp"

HttpDefaultResponse::HttpDefaultResponse(int socket) : _socket(socket) {}

HttpDefaultResponse::~HttpDefaultResponse() {}

void	HttpDefaultResponse::handleDefault()
{
	std::string http = "HTTP/1.1 200 OK\n";
	std::string message = "This should display the default page";
	std::string content_length_str = "Content-Length: " + std::to_string(message.length()) + "\n\n";
	std::string output = http + content_length_str + message;
	write(this->_socket, output.c_str(), output.length());
	std::cout << "Default page sent" << std::endl;
	close(this->_socket);
}
