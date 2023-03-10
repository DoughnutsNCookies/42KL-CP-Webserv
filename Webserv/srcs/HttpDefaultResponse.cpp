/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDefaultResponse.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:39:08 by schuah            #+#    #+#             */
/*   Updated: 2023/03/14 15:23:28 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpDefaultResponse.hpp"

HttpDefaultResponse::HttpDefaultResponse(EuleeHand database) : _database(database) {}

HttpDefaultResponse::~HttpDefaultResponse() {}

void	HttpDefaultResponse::handleDefault()
{
	std::string http = "HTTP/1.1 200 OK\r\n";
	std::string message = "This should display the default page";
	std::string content_length_str = "Content-Length: " + std::to_string(message.length()) + "\r\n\r\n";
	std::string output = http + content_length_str + message;

	this->_database.ft_select(this->_database.socket, (void *)output.c_str(), output.length(), WRITE);
	close(this->_database.socket);
}
