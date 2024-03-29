/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpPutResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:01:49 by schuah            #+#    #+#             */
/*   Updated: 2023/03/31 18:23:49 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpPutResponse.hpp"

HttpPutResponse::HttpPutResponse(EuleeHand *database) : _database(database) {}

HttpPutResponse::~HttpPutResponse() {}

void	HttpPutResponse::handlePut()
{
	int		contentLengthSpecified = 0;
	size_t	contentLength = 0;
	size_t	contentLengthPos = this->_database->buffer[this->_database->socket].find("Content-Length: ");
	if (contentLengthPos != std::string::npos)
	{
		contentLengthPos += std::strlen("Content-Length: ");
		contentLength = std::stoul(this->_database->buffer[this->_database->socket].substr(contentLengthPos));
		contentLengthSpecified = 1;
	}

	std::ofstream	originalPath(this->_database->methodPath[this->_database->socket].c_str() + 1, std::ios::binary);
	if (originalPath.fail())
	{
		std::cerr << RED << "Directory not found, using upload from config..." << RESET << std::endl;
		if (this->_database->server[this->_database->serverIndex[this->_database->socket]].location[this->_database->locationPath[this->_database->socket]][UPLOAD].empty())
			std::cerr << RED << "Upload not set in config, cannot save file..." << RESET << std::endl;
		else
		{
			int	pathCanUse = 0;
			if (this->_database->methodPath[this->_database->socket].substr(this->_database->methodPath[this->_database->socket].find_last_of("/")) == "/")
			{
				std::cerr << RED << "File to save is a directory..." << RESET << std::endl;
				return ;
			}
			for (size_t i = 0; this->_database->server[this->_database->serverIndex[this->_database->socket]].location[this->_database->locationPath[this->_database->socket]][UPLOAD].size() && pathCanUse == 0; i++)
			{
				std::ofstream	locationPathStream(this->_database->server[this->_database->serverIndex[this->_database->socket]].location[this->_database->locationPath[this->_database->socket]][UPLOAD][i] + this->_database->methodPath[this->_database->socket].substr(this->_database->methodPath[this->_database->socket].find_last_of("/")));
				if (locationPathStream.fail() == false)
				{
					std::cout << GREEN << "Put to: " << this->_database->methodPath[this->_database->socket].c_str() + 1 << RESET << std::endl;
					std::string		toWrite = this->_database->buffer[this->_database->socket].substr(this->_database->buffer[this->_database->socket].find("\r\n\r\n") + std::strlen("\r\n\r\n"));
					if (contentLengthSpecified)
						locationPathStream << toWrite;
					else
						locationPathStream << toWrite;
					locationPathStream.close();
					pathCanUse = 1;
				}
			}
			if (pathCanUse == 0)
				std::cerr << RED << "Upload path cannot be used to save file..." << RESET << std::endl;
		}
	}
	else
	{
		std::cout << GREEN << "Put to: " << this->_database->methodPath[this->_database->socket].c_str() + 1 << RESET << std::endl;
		std::string		toWrite = this->_database->buffer[this->_database->socket].substr(this->_database->buffer[this->_database->socket].find("\r\n\r\n") + std::strlen("\r\n\r\n"));
		originalPath << toWrite;
		originalPath.close();
	}
	this->_database->sendHttp(200);
}
