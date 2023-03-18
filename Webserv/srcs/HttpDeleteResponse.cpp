/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDeleteResponse.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:22:48 by schuah            #+#    #+#             */
/*   Updated: 2023/03/14 15:21:53 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpDeleteResponse.hpp"

HttpDeleteResponse::HttpDeleteResponse(EuleeHand database) : _database(database) {}

HttpDeleteResponse::~HttpDeleteResponse() {}

void	HttpDeleteResponse::handleDelete()
{
	std::string	filePath = "." + this->_database.methodPath;
	int	result = std::remove(filePath.c_str());
	if (result != 0)
	{
		std::cerr << RED << "Error: " << filePath << " cannot be deleted" << RESET << std::endl;
		this->_database.sendHttp(404, this->_database.methodPath);

		std::string	response = "HTTP/1.1 404 Not Found\r\n\r\nFile to delete is not found...\r\n";
		this->_database.ft_select(this->_database.socket, (void *)response.c_str(), response.length(), WRITE);
		close(this->_database.socket);
		return ;
	}
	std::cout << GREEN << filePath << " has been deleted!" << RESET << std::endl;
	close(this->_database.socket);
}
