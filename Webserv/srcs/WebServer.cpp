/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:27:11 by schuah            #+#    #+#             */
/*   Updated: 2023/03/07 17:18:24 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Class constructor that takes in configFilePath string */
WebServer::WebServer(std::string configFilePath)
{
	this->_database = EuleeHand(configFilePath, ConfigManager(configFilePath));
}

WebServer::~WebServer(void) {}

void	WebServer::runServer(void)
{
	this->_database.parseConfigFile();
	this->_database.printTokens();
	std::cout << GREEN "Config File Parsing Done..." RESET << std::endl;
	this->_database.configLibrary();
	this->_database.errorHandleShit();
	std::cout << GREEN "Error Handling File Done..." RESET << std::endl;

}
