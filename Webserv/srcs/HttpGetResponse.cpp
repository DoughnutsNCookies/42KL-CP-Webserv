/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpGetResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:20:26 by schuah            #+#    #+#             */
/*   Updated: 2023/03/14 18:59:26 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpGetResponse.hpp"

HttpGetResponse::HttpGetResponse(EuleeHand database) : _database(database) {}

HttpGetResponse::~HttpGetResponse() {}

void	HttpGetResponse::handleGet()
{
	std::string	failedResponse = "HTTP/1.1 404 Not Found\r\n\r\nFile to get is not found...\r\n";
	size_t	queryPos = this->_database.methodPath.find('?');
	if (queryPos != std::string::npos)
		this->_database.methodPath = this->_database.methodPath.substr(0, queryPos);

	std::ifstream	file(this->_database.methodPath.c_str() + 1);
	if (file.fail())
	{
		std::cerr << RED << "Error opening " << this->_database.methodPath << "!\n" << RESET << std::endl;
		this->_database.ft_select(this->_database.socket, (void *)failedResponse.c_str(), failedResponse.length(), WRITE);
		close(this->_database.socket);
		return ;
	}

	file.seekg(0, std::ios::end);
	long	file_size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::string	fileContents;
	fileContents.resize(file_size + 1);
	if (file.read(&fileContents[0], file_size).fail())
	{
		std::cerr << RED << "Error reading " << this->_database.methodPath << "!\n" << RESET << std::endl;
		this->_database.ft_select(this->_database.socket, (void *)failedResponse.c_str(), failedResponse.length(), WRITE);
		file.close();
		close(this->_database.socket);
		return ;
	}
	file.close();

	std::string	httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: */*\r\nContent-Length: " + std::to_string(file_size) + "\r\n\r\n" + fileContents;
	int	total = 0;
	while (total < (int)httpResponse.size())
	{
		int sent = this->_database.ft_select(this->_database.socket, &httpResponse[total], httpResponse.size() - total, WRITE);
		if (sent <= 0)
		{
			close(this->_database.socket);
			return ;
		}
		total += sent;
		std::cout << GREEN << "Sent: " << sent << "\tTotal: " << total << " / " << httpResponse.size() << RESET << std::endl;
	}
	close(this->_database.socket);
}
