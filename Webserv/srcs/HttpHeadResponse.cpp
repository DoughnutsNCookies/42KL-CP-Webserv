/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeadResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:44:45 by schuah            #+#    #+#             */
/*   Updated: 2023/03/14 15:12:31 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpHeadResponse.hpp"

HttpHeadResponse::HttpHeadResponse(EuleeHand database) : _database(database) {}

HttpHeadResponse::~HttpHeadResponse() {}

void	HttpHeadResponse::handleHead()
{
	std::ifstream	file(this->_database.methodPath.c_str() + 1);
	std::string		http = "";
	if (file.fail() && this->_database.methodPath != "/")
	{
		std::cerr << RED << "Error opening " << this->_database.methodPath << "!\n" << RESET << std::endl;
		http = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n";
	}
	else
	{
		std::cout << GREEN << "File " << this->_database.methodPath << " found!!\n" << RESET << std::endl;
		http = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n";
	}
	this->_database.ft_select(this->_database.socket, (void *)http.c_str(), http.length(), WRITE);
	file.close();
	close(this->_database.socket);
}
