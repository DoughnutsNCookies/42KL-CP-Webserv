/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpGetResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:20:26 by schuah            #+#    #+#             */
/*   Updated: 2023/03/22 17:55:22 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpGetResponse.hpp"

HttpGetResponse::HttpGetResponse(EuleeHand database) : _database(database) {}

HttpGetResponse::~HttpGetResponse() {}

void	HttpGetResponse::handleGet()
{
	size_t	queryPos = this->_database.methodPath.find('?');
	if (queryPos != std::string::npos)
		this->_database.methodPath = this->_database.methodPath.substr(0, queryPos);

	if (this->_database.checkPath(this->_database.methodPath.c_str() + 1, 0, 0))
	{
		std::cerr << RED << "Error opening " << this->_database.methodPath << "!\n" << RESET << std::endl;
		this->_database.sendHttp(404, 1);
		return ;
	}

	std::ifstream	file(this->_database.methodPath.c_str() + 1);
	file.seekg(0, std::ios::end);
	long	file_size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::string	fileContents;
	fileContents.resize(file_size + 1);

	if (file.read(&fileContents[0], file_size).fail())
	{
		std::cerr << RED << "Error reading " << this->_database.methodPath << "!" << RESET << std::endl;
		if (this->_database.useDirectoryListing)
		{
			std::string	directoryListingResponse = "HTTP/1.1 200 OK\r\n\r\n" + this->_database.directoryListing(this->_database.methodPath);
			this->_database.ft_select(this->_database.socket, &directoryListingResponse[0], directoryListingResponse.size(), WRITE);
			std::cout << GREEN << "Autoindex is set on, directory listing sent!" << RESET << std::endl;
			close(this->_database.socket);
		}
		else if (this->_database.checkPath(this->_database.methodPath.c_str() + 1, 0, 1) || this->_database.useDefaultIndex)
			this->_database.sendHttp(200, 1);
		else
			this->_database.sendHttp(404, 1);
		file.close();
		return ;
	}
	file.close();

	std::string	httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: */*\r\nContent-Length: " + std::to_string(file_size) + "\r\n\r\n" + fileContents;
	this->_database.ft_select(this->_database.socket, &httpResponse[0], httpResponse.size(), WRITE);
	close(this->_database.socket);
}
