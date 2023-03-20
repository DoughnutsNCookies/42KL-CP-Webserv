/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDeleteResponse.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:22:48 by schuah            #+#    #+#             */
/*   Updated: 2023/03/20 15:31:35 by schuah           ###   ########.fr       */
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
		this->_database.sendHttp(404, 1);
		return ;
	}
	std::cout << GREEN << filePath << " has been deleted!" << RESET << std::endl;
	close(this->_database.socket);
}
