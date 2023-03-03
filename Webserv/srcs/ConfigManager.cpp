/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:55:11 by schuah            #+#    #+#             */
/*   Updated: 2023/03/02 19:46:33 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigManager.hpp"

ConfigManager::ConfigManager(): _configFilePath() {}

ConfigManager::ConfigManager(std::string configFilePath): _configFilePath(configFilePath) {}

ConfigManager::~ConfigManager() {}

ConfigManager	&ConfigManager::operator=(const ConfigManager &srcs)
{
	this->_fileBuffer = srcs._fileBuffer;
	this->_configFilePath = srcs._configFilePath;
	return (*this);
}

int	ConfigManager::parseConfigFile()
{
	if (this->_configFilePath.empty())
		throw std::runtime_error("Failed to open config file");
	this->_file.open(this->_configFilePath.c_str(), std::ios::binary);
	if (this->_file.is_open() == false)
		throw std::runtime_error("Failed to open config file");
	return (1);
}
