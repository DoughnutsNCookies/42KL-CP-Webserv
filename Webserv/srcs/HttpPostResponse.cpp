/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpPostResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:27:42 by schuah            #+#    #+#             */
/*   Updated: 2023/03/21 21:02:46 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpPostResponse.hpp"

HttpPostResponse::HttpPostResponse(EuleeHand database) : _database(database), _contentLength(), _contentLengthSpecified() {}

HttpPostResponse::~HttpPostResponse() {}

void	HttpPostResponse::_normalSave()
{
	std::cout << GREEN << "Post to: " << this->_database.methodPath.c_str() + 1 << RESET << std::endl;
	std::ofstream	originalPath(this->_database.methodPath.c_str() + 1, std::ios::binary);
	if (originalPath.fail())
	{
		std::cout << RED << "Directory not found, using upload from config..." << RESET << std::endl;
		if (this->_database.server[this->_database.serverIndex].location[this->_database.locationPath][UPLOAD].empty())
			std::cout << RED << "Upload not set in config, cannot save file..." << RESET << std::endl;
		else
		{
			int	pathCanUse = 0;
			if (this->_database.methodPath.substr(this->_database.methodPath.find_last_of("/")) == "/")
			{
				std::cout << RED << "File to save is a directory..." << RESET << std::endl;
				return ;
			}
			for (size_t i = 0; this->_database.server[this->_database.serverIndex].location[this->_database.locationPath][UPLOAD].size() && pathCanUse == 0; i++)
			{
				std::ofstream	locationPath(this->_database.server[this->_database.serverIndex].location[this->_database.locationPath][UPLOAD][i] + this->_database.methodPath.substr(this->_database.methodPath.find_last_of("/")));
				if (locationPath.fail() == false)
				{
					std::cout << GREEN << "Put to: " << this->_database.methodPath.c_str() + 1 << RESET << std::endl;
					std::string		toWrite = this->_database.buffer.substr(this->_database.buffer.find("\r\n\r\n") + std::strlen("\r\n\r\n"));
					if (this->_contentLengthSpecified)
						locationPath << toWrite;
					else
						locationPath << toWrite;
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
		if (this->_contentLengthSpecified)
			originalPath << toWrite;
		else
			originalPath << toWrite;
		originalPath.close();
	}
}

void	HttpPostResponse::_saveFile()
{
	size_t	boundaryPos = this->_database.buffer.find("boundary=");
	if (boundaryPos == std::string::npos)
	{
		std::cerr << RED << "No boundary found!" << RESET << std::endl;
		std::cerr << GREEN <<  "Saving file normally..." << RESET << std::endl;
		this->_normalSave();
		return ;
	}
	boundaryPos += std::strlen("boundary=");
	std::string	boundary = this->_database.buffer.substr(boundaryPos, this->_database.buffer.find("\r\n", boundaryPos) - boundaryPos);
	boundaryPos = this->_database.buffer.find(boundary, boundaryPos + boundary.length());
	
	if (this->_contentLengthSpecified && this->_database.buffer.substr(boundaryPos).length() + std::strlen("\r\n") != this->_contentLength)
	{
		std::cerr << RED << "Error: Content-Length does not match actual content length!" << RESET << std::endl;
		return ;
	}
	size_t		namePos = this->_database.buffer.find("filename=\"");
	std::string	fileName;
	if (namePos == std::string::npos)
	{
		std::cerr << RED << "No file name found in header! Extracting from path..." << RESET << std::endl;
		fileName = this->_database.methodPath.substr(this->_database.methodPath.find_last_of("/"));
	}
	else
	{
		namePos += std::strlen("filename=\"");
		fileName = this->_database.buffer.substr(namePos, this->_database.buffer.find("\"", namePos) - namePos);
	}
	std::cout << GREEN << "File name to be saved as: " << fileName << std::endl;

	size_t		boundaryEndPos = this->_database.buffer.find("--" + boundary + "--");
	if (boundaryEndPos == std::string::npos)
	{
		std::cerr << RED << "No end boundary found!" << RESET << std::endl;
		return ;
	}
	size_t		dataLength = boundaryEndPos - (boundaryPos + boundary.length());
	std::string	fileData = this->_database.buffer.substr(boundaryPos + boundary.length(), dataLength - std::strlen("\r\n"));

	std::ofstream	newFile(fileName, std::ios::binary);
	if (newFile.is_open() == false)
	{
		std::cerr << RED << "Error: Failed to create new file!" << RESET << std::endl;
		return ;
	}
	std::string	toWrite = fileData.substr(fileData.find("\r\n\r\n") + std::strlen("\r\n\r\n"));
	newFile << toWrite;
	newFile.close();
}

void	HttpPostResponse::handlePost()
{
	size_t	contentLengthPos = this->_database.buffer.find("Content-Length: ");
	if (contentLengthPos != std::string::npos)
	{
		contentLengthPos += std::strlen("Content-Length: ");
		this->_contentLength = std::stoul(this->_database.buffer.substr(contentLengthPos));
		this->_contentLengthSpecified = 1;
	}

	this->_saveFile();
	this->_database.sendHttp(200, 1);
}
