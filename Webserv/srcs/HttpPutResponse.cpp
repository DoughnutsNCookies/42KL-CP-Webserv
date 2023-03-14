/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpPutResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:01:49 by schuah            #+#    #+#             */
/*   Updated: 2023/03/14 15:20:49 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpPutResponse.hpp"

HttpPutResponse::HttpPutResponse(EuleeHand database) : _database(database) {}

HttpPutResponse::~HttpPutResponse() {}

void	HttpPutResponse::handlePut()
{
	int		contentLengthSpecified = 0;
	size_t	contentLength = 0;
	size_t	contentLengthPos = this->_database.buffer.find("Content-Length: ");
	if (contentLengthPos != std::string::npos)
	{
		contentLengthPos += std::strlen("Content-Length: ");
		contentLength = std::stoul(this->_database.buffer.substr(contentLengthPos));
		contentLengthSpecified = 1;
	}

	std::ofstream	newFile(this->_path.c_str() + 1, std::ios::binary);
	std::string		toWrite = this->_database.buffer.substr(this->_database.buffer.find("\r\n\r\n") + std::strlen("\r\n\r\n"));
	if (contentLengthSpecified)
		newFile.write(toWrite.c_str(), contentLength);
	else
		newFile.write(toWrite.c_str(), toWrite.length());
	newFile.close();

	std::string responseBody = "Server has received your POST request!";
	std::string response = "HTTP/1.1 200 OK\r\nContent-Length: " + std::to_string(responseBody.length()) + "\r\n\r\n" + responseBody;
	this->_database.ft_select(this->_socket, (void *)response.c_str(), response.length(), WRITE);
	close(this->_socket);
}
