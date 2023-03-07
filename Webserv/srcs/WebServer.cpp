/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:27:11 by schuah            #+#    #+#             */
/*   Updated: 2023/03/07 16:46:26 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Class constructor that takes in configFilePath string */
WebServer::WebServer(std::string configFilePath)
{
	this->_database = EuleePocket(configFilePath, ConfigManager(configFilePath));
}

WebServer::~WebServer(void) {}

void	WebServer::runServer(void)
{
	this->_database.parseConfigFile();
	this->_database.printData();
	std::cout << GREEN "Config File Parsing Done..." RESET << std::endl;
}
