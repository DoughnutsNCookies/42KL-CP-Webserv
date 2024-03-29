/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpGetResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:20:26 by schuah            #+#    #+#             */
/*   Updated: 2023/03/29 17:58:03 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpGetResponse.hpp"

HttpGetResponse::HttpGetResponse(EuleeHand *database) : _database(database) {}

HttpGetResponse::~HttpGetResponse() {}

void	HttpGetResponse::handleGet()
{
	size_t	queryPos = this->_database->methodPath[this->_database->socket].find('?');
	if (queryPos != std::string::npos)
		this->_database->methodPath[this->_database->socket] = this->_database->methodPath[this->_database->socket].substr(0, queryPos);

	if (this->_database->checkPath(this->_database->methodPath[this->_database->socket].c_str() + 1, 0, 0))
	{
		std::cerr << RED << "Error opening " << this->_database->methodPath[this->_database->socket] << "!\n" << RESET << std::endl;
		this->_database->sendHttp(404);
		return ;
	}

	std::ifstream	file(this->_database->methodPath[this->_database->socket].c_str() + 1);
	file.seekg(0, std::ios::end);
	long	file_size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::string	fileContents;
	fileContents.resize(file_size + 1);

	if (file.read(&fileContents[0], file_size).fail())
	{
		std::cerr << RED << "Error reading " << this->_database->methodPath[this->_database->socket] << "!" << RESET << std::endl;
		if (this->_database->useDirectoryListing[this->_database->socket])
		{
			std::string	directoryPath = this->_database->methodPath[this->_database->socket].substr(1, this->_database->methodPath[this->_database->socket].find_last_of('/'));
			this->_database->response[this->_database->socket] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n" + this->_database->directoryListing(directoryPath);
			std::cout << GREEN << "Autoindex is set on, directory listing sent!" << RESET << std::endl;
		}
		else if (this->_database->checkPath(this->_database->methodPath[this->_database->socket].c_str() + 1, 0, 1) || this->_database->useDefaultIndex[this->_database->socket])
			this->_database->sendHttp(200);
		else
			this->_database->sendHttp(404);
		file.close();
		return ;
	}
	file.close();

	this->_database->sendHttp(200, fileContents);
}
