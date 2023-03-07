/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleePocket.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:13:53 by jhii              #+#    #+#             */
/*   Updated: 2023/03/07 16:49:42 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EuleePocket.hpp"

EuleePocket::EuleePocket(void) : _configFilePath(), _configManager() {}

EuleePocket::EuleePocket(std::string configFilePath, ConfigManager const &configManager) : _configFilePath(configFilePath), _configManager(configManager) {}

EuleePocket::EuleePocket(const EuleePocket &ref) : _configFilePath(ref._configFilePath), _configManager(ref._configManager) {}

EuleePocket::~EuleePocket(void) {}

EuleePocket	&EuleePocket::operator=(const EuleePocket &ref)
{
	this->_configFilePath = ref._configFilePath;
	this->_configManager = ref._configManager;
	return (*this);
}

void	EuleePocket::printData(void)
{
	this->_configManager.printTokens();
}

void	EuleePocket::parseConfigFile(void)
{
	this->_configManager.parseConfigFile();
}
