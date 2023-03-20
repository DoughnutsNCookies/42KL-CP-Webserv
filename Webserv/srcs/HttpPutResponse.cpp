/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpPutResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:01:49 by schuah            #+#    #+#             */
/*   Updated: 2023/03/16 13:52:33 by schuah           ###   ########.fr       */
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

	std::ofstream	originalPath(this->_database.methodPath.c_str() + 1, std::ios::binary);
	if (originalPath.fail())
	{
		std::cout << RED << "Directory not found, using upload from config..." << RESET << std::endl;
		if (this->_database.server[this->_database.serverIndex].location[this->_database.locationPath][UPLOAD].size() == 0)
			std::cout << RED << "Upload not set in config, cannot save file..." << RESET << std::endl;
		else
		{
			int	pathCanUse = 0;
			for (size_t i = 0; this->_database.server[this->_database.serverIndex].location[this->_database.locationPath][UPLOAD].size() && pathCanUse == 0; i++)
			{
				std::ofstream	locationPath(this->_database.server[this->_database.serverIndex].location[this->_database.locationPath][UPLOAD][i] + this->_database.methodPath.substr(this->_database.methodPath.find_last_of("/")));
				if (locationPath.fail() == false)
				{
					std::cout << GREEN << "Put to: " << this->_database.methodPath.c_str() + 1 << RESET << std::endl;
					std::string		toWrite = this->_database.buffer.substr(this->_database.buffer.find("\r\n\r\n") + std::strlen("\r\n\r\n"));
					if (contentLengthSpecified)
						locationPath.write(toWrite.c_str(), contentLength);
					else
						locationPath.write(toWrite.c_str(), toWrite.length());
					locationPath.close();
					pathCanUse = 1;
				}
			}
			if (pathCanUse == 0)
				std::cout << RED << "Upload path cannot be used to save file..." << RESET << std::endl;
		}
	}
	else
	{
		std::cout << GREEN << "Put to: " << this->_database.methodPath.c_str() + 1 << RESET << std::endl;
		std::string		toWrite = this->_database.buffer.substr(this->_database.buffer.find("\r\n\r\n") + std::strlen("\r\n\r\n"));
		if (contentLengthSpecified)
			originalPath.write(toWrite.c_str(), contentLength);
		else
			originalPath.write(toWrite.c_str(), toWrite.length());
		originalPath.close();
	}

	std::string responseBody = "Server has received your POST request!";
	std::string response = "HTTP/1.1 200 OK\r\nContent-Length: " + std::to_string(responseBody.length()) + "\r\n\r\n" + responseBody;
	this->_database.ft_select(this->_database.socket, (void *)response.c_str(), response.length(), WRITE);
	close(this->_database.socket);
}
