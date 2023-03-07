/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:55:11 by schuah            #+#    #+#             */
/*   Updated: 2023/03/07 17:57:57 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigManager.hpp"
#include <unistd.h>

ConfigManager::ConfigManager(): _configFilePath() {}

ConfigManager::ConfigManager(std::string configFilePath): _configFilePath(configFilePath) {}

ConfigManager::~ConfigManager() {}

ConfigManager	&ConfigManager::operator=(const ConfigManager &srcs)
{
	this->_configFilePath = srcs._configFilePath;
	return (*this);
}

void	ConfigManager::_createToken(std::string *token, Type *currentType, Type type, std::string c, int lineNum)
{
	if (token->empty() == false)
	{
		this->_tokens.push_back(Token(*token, *currentType, lineNum));
		token->clear();
	}
	this->_tokens.push_back(Token(c, type, lineNum));
	*currentType = CONTEXT;
}

void	ConfigManager::_lexLine(std::string line, int lineNum)
{
	std::string	token;
	Type		type = CONTEXT;
	int			count = 0;

	for (int i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == '#')
			break;
		else if (line[i] == '{')
			this->_createToken(&token, &type, OPEN_BRACE, "{", lineNum);
		else if (line[i] == '}')
			this->_createToken(&token, &type, CLOSE_BRACE, "}", lineNum);
		else if (line[i] == ';')
		{
			this->_createToken(&token, &type, SEMICOLON, ";", lineNum);
			count = 0;
		}
		else if (std::string(" \f\n\r\t\v").find(line[i]) != std::string::npos)
		{
			if (token.empty() == false)
			{
				type = (count == 0) ? KEY : VALUE;
				count++;
				this->_tokens.push_back(Token(token, type, lineNum));
				token.clear();
			}
			type = VALUE;
		}
		else
			token.push_back(line[i]);
	}
	if (token.empty() == false)
		this->_tokens.push_back(Token(token, type, lineNum));
}

void	ConfigManager::parseConfigFile()
{
	if (this->_configFilePath.empty())
		throw std::runtime_error("Failed to open config file");
	std::ifstream	file(this->_configFilePath.c_str(), std::ios::binary);
	if (file.is_open() == false)
		throw std::runtime_error("Failed to open config file");
	std::string	line;
	int			lineNum = 0;
	// this->_fileBuffer = "{" + this->_fileBuffer + "}";
	while (std::getline(file, line))
	{
		lineNum++;
		this->_lexLine(line, lineNum);
	}
	file.close();
	// for (size_t i = 0; i < this->_tokens.size(); i++)
	// {
	// 	std::cout << "Token: " << this->_tokens[i].getToken() << ", Type: " << this->_tokens[i].getType() << ", Line: " << this->_tokens[i].getLineNum() <<std::endl;
	// }
}
