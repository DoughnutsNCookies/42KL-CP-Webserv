/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleeHand.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:13:53 by jhii              #+#    #+#             */
/*   Updated: 2023/03/07 17:21:28 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EuleeHand.hpp"

EuleeHand::EuleeHand(void) : _configFilePath(), _configManager() {}

EuleeHand::EuleeHand(std::string configFilePath, ConfigManager const &configManager) : _configFilePath(configFilePath), _configManager(configManager) {}

EuleeHand::EuleeHand(const EuleeHand &ref) : _configFilePath(ref._configFilePath), _configManager(ref._configManager) {}

EuleeHand::~EuleeHand(void) {}

EuleeHand	&EuleeHand::operator=(const EuleeHand &ref)
{
	this->_configFilePath = ref._configFilePath;
	this->_configManager = ref._configManager;
	return (*this);
}

void	EuleeHand::printTokens(void)
{
	this->_configManager.printTokens();
}

void	EuleeHand::parseConfigFile(void)
{
	this->_configManager.parseConfigFile();
}

void	EuleeHand::errorHandleShit(void)
{
	this->_configManager.errorHandleShit();
}

void	EuleeHand::configLibrary(void)
{
	this->_configManager.configLibrary();
}

