/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeadResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:44:45 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 18:57:10 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpHeadResponse.hpp"

HttpHeadResponse::HttpHeadResponse(int socket, std::string path) : _socket(socket), _path(path) {}

HttpHeadResponse::~HttpHeadResponse() {}

void	HttpHeadResponse::handleHead()
{
	std::ifstream	file(this->_path.c_str() + 1);
	std::string		http = "";
	if (file.fail() && this->_path != "/")
	{
		std::cerr << RED << "Error opening " << this->_path << "!\n" << RESET << std::endl;
		http = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n";
	}
	else
	{
		std::cout << GREEN << "File " << this->_path << " found!!\n" << RESET << std::endl;
		http = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n";
	}
	ft_select(this->_socket, (void *)http.c_str(), http.length(), WRITE);
	file.close();
	close(this->_socket);
}
