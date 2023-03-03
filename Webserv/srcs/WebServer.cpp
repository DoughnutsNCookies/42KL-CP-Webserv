/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:27:11 by schuah            #+#    #+#             */
/*   Updated: 2023/03/03 11:01:37 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Class constructor that takes in configFilePath string */
WebServer::WebServer(std::string configFilePath): _configFilePath(configFilePath)
{
	this->_configManager = ConfigManager(configFilePath);
}

WebServer::~WebServer() {}

void	WebServer::runServer()
{
	this->_configManager.parseConfigFile();
	std::cout << "Server running" << std::endl;
}
