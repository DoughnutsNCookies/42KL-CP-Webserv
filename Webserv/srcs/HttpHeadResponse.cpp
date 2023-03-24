/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeadResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:44:45 by schuah            #+#    #+#             */
/*   Updated: 2023/03/24 16:21:10 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpHeadResponse.hpp"

HttpHeadResponse::HttpHeadResponse(EuleeHand *database) : _database(database) {}

HttpHeadResponse::~HttpHeadResponse() {}

void	HttpHeadResponse::handleHead()
{
	std::ifstream	file(this->_database->methodPath.c_str() + 1);
	std::string		http = "";
	if (file.fail() && this->_database->methodPath != "/")
	{
		std::cerr << RED << "Error opening " << this->_database->methodPath << "!" << RESET << std::endl;
		this->_database->sendHttp(404);
	}
	else
	{
		std::cout << GREEN << "File " << this->_database->methodPath << " found!" << RESET << std::endl;
		this->_database->sendHttp(200);
	}
	file.close();
}
