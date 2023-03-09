/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:55:11 by schuah            #+#    #+#             */
/*   Updated: 2023/03/07 16:34:28 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigManager.hpp"
#include <unistd.h>

ConfigManager::ConfigManager(void): _configFilePath() {}

ConfigManager::ConfigManager(std::string configFilePath): _configFilePath(configFilePath) {}

ConfigManager::~ConfigManager() {}

ConfigManager	&ConfigManager::operator=(const ConfigManager &ref)
{
	this->_configFilePath = ref._configFilePath;
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
	while (std::getline(file, line))
		this->_lexLine(line, ++lineNum);
	file.close();
}

void	ConfigManager::printTokens(void)
{
	for (size_t i = 0; i < this->_tokens.size(); i++)
		std::cout << "Token: |" << this->_tokens[i].getToken() << "| Type: |" << this->_tokens[i].getType() << "| Line: |" << this->_tokens[i].getLineNum() << "|" << std::endl;
}

void	ConfigManager::printError(std::string str, int i)
{
	std::cout << str << "Line: " << this->_tokens[i].getLineNum() << std::endl;
	std::cout << this->_tokens[i].getToken() << std::endl;
	exit(1);
}

void	ConfigManager::configLibrary(void)
{
	const char	*library[12] = {"server", "server_name", "listen", "autoindex", "access_log", "root", "index", "return", "location", "expires", "proxy_pass", "fastcgi_pass"};

	this->_validStr = std::vector<std::string>(library, library + 12);
}

void	ConfigManager::errorHandleShit(void)
{
	static int	juan;
	static int	braces;
	static int	previous;

	for (size_t i = 0; i < this->_tokens.size(); i++) 
	{
		if (this->_tokens[i].getType() == CONTEXT) // 0
			printError("Random word out of blocks. ", i);
		if (this->_tokens[i].getType() == KEY) // 1
		{
			if (!(std::find(this->_validStr.begin(), this->_validStr.end(), this->_tokens[i].getToken()) != this->_validStr.end()))
				printError("Not a valid string. ", i);
			if ((previous == 3 || previous == 4 || previous == 5) || juan == 0)
				previous = 1;
			else
				printError("Key is not after braces or semicolon. ", i);
			juan = 1;
		}
		if (this->_tokens[i].getType() == VALUE) // 2
		{
			if (previous == 1 || previous == 2)
				previous = 2;
			else
				printError("Not a key/value before another value. ", i);
		}
		if (this->_tokens[i].getType() == SEMICOLON) // 3
		{
			if (previous == 2)
				previous = 3;
			else
				printError("Semicolon not after value. ", i);
		}
		if (this->_tokens[i].getType() == OPEN_BRACE) // 4
		{
			if (juan > 0)
				braces++;
			else
				printError("Not starting with top level directives. ", i);
			if (previous == 1 || previous  == 2)
				previous = 4;
			else
				printError("Open braces not after key or value. ", i);
		}
		if (this->_tokens[i].getType() == CLOSE_BRACE) // 5
		{
			if (braces > 0)
				braces--;
			else
				printError("Close braces before open braces. ", i);
			if (previous == 3 || previous == 5)
				previous = 5;
			else
				printError("Close braces not after close braces or semicolon. ", i);
			if (braces == 0)
				juan = 0;
		}
	}
	return ;
}
