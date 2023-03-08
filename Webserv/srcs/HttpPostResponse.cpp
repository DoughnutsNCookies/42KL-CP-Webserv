/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpPostResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:27:42 by schuah            #+#    #+#             */
/*   Updated: 2023/03/08 15:36:27 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpPostResponse.hpp"

HttpPostResponse::HttpPostResponse(int socket, int content_length, int valread, std::string buffer) : _socket(socket), _content_length(content_length), _valread(valread), _buffer(buffer) {}

HttpPostResponse::~HttpPostResponse() {}

void	HttpPostResponse::handlePost()
{
	size_t	content_length_pos = this->_buffer.find("Content-Length: ");
	if (content_length_pos != std::string::npos)
	{
		content_length_pos += std::strlen("Content-Length: ");
		this->_content_length = std::stoi(this->_buffer.substr(content_length_pos));
	}

	std::string	message_body;
	message_body.resize(this->_content_length);
	this->_valread = read(this->_socket, &message_body[0], this->_content_length);

	std::string response_body = "Server has received your POST request!";
	std::string response = "HTTP/1.1 200 OK\r\nContent-Length: " + std::to_string(response_body.length()) + "\r\n\r\n" + response_body;
	send(this->_socket, response.c_str(), response.length(), 0);
}
