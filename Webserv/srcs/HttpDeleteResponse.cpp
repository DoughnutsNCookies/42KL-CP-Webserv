/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDeleteResponse.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:22:48 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 16:40:17 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpDeleteResponse.hpp"

HttpDeleteResponse::HttpDeleteResponse(int socket, std::string path) : _socket(socket), _path(path) {}

HttpDeleteResponse::~HttpDeleteResponse() {}

void	HttpDeleteResponse::handleDelete()
{
	std::string	filePath = "." + this->_path;
	int	result = std::remove(filePath.c_str());
	if (result != 0)
	{
		std::cerr << RED << "Error: " << filePath << " cannot be deleted" << RESET << std::endl;
		close(this->_socket);
		return ;
	}
	std::cout << GREEN << filePath << " has been deleted!" << RESET << std::endl;
	close(this->_socket);
}
