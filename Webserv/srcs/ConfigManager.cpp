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
	const char	*serverlib[11] = {"server", "location", "listen", "root", "index", "server_name", "error_page", "client_max_body_size", "auto_index", "return", "location"};
	const char	*locationlib[6] = {"root", "index", "include", "cgi_pass", "cgi_index", "cgi_param"};

	this->_serverVar = std::vector<std::string>(serverlib, serverlib + 11);
	this->_locationVar = std::vector<std::string>(locationlib, locationlib + 6);
}

int		ConfigManager::checkKey(int i, int previous, int *braces, int *main_block)
{
	if (this->_tokens[i].getType() == KEY) // 1
	{
		if ((previous == 3 || previous == 4 || previous == 5) || *main_block == 0)
			return (1); // check this shit
		else
			printError("Key is not after braces or semicolon. ", i);


		
		if (this->_tokens[i].getToken() == this->_serverVar[1]) // location
		{
			int = this->locationBlock(i++); // think how to handle if it happens twice
			return ();

			// if (this->_tokens[i + 1].getType() != VALUE)
			// 	printError("I handled it bitch ( not a value after location ). ", i);
			// if (!(std::find(this->_locationVar.begin(), this->_locationVar.end(), this->_tokens[i + 1].getToken()) != this->_locationVar.end()))
			// 	printError("Not a valid string for Location block. ", i);
		}


		if (*main_block == 1 && this->_tokens[i].getToken() == this->_serverVar[0])
				printError("Server cannot be non-main directive. ", i);


		if (*main_block == 0)
		{
			// std::cout << "entered: " << braces << std::endl;
			if (this->_tokens[i].getToken() != this->_serverVar[0])
				printError("Invalid main directive (should be server). ", i);
			if (*braces > 0)
				printError("Invalid number of braces.", i);
			*main_block -= 1;
		}
		if (!(std::find(this->_serverVar.begin(), this->_serverVar.end(),
			this->_tokens[i].getToken()) != this->_serverVar.end())) // server
			printError("Not a valid string for Server block. ", i);
	}
	return (previous);
}

int		ConfigManager::checkValue(int i, int previous)
{
	if (this->_tokens[i].getType() == VALUE) // 2
	{
		if (previous == 1 || previous == 2)
			return (2);
			// previous = 2;
		else
			printError("Not a key/value before another value. ", i);
	}
	return (previous);
}

int	ConfigManager::checkSemicolon(int i, int previous)
{
	if (this->_tokens[i].getType() == SEMICOLON) // 3
	{
		if (previous == 2)
			return (3);
			// previous = 3;
		else
			printError("Semicolon not after value. ", i);
	}
	return (previous);
}

int		ConfigManager::checkOpenBrace(int i, int previous, int *braces, int main_block)
{
	if (this->_tokens[i].getType() == OPEN_BRACE) // 4
	{
		if (main_block > 0)
			*braces += 1;
		if (previous == 1 || previous  == 2)
			return (4);
		else
			printError("Open braces not after key or value. ", i);
	}
	return (previous);
}

int		ConfigManager::checkCloseBrace(int i, int previous, int *braces, int *main_block)
{
	if (this->_tokens[i].getType() == CLOSE_BRACE) // 5
	{
		if (*braces > 0)
			*braces -= 1;
		if (previous == 3 || previous == 5)
			return (5);
		else
			printError("Close braces not after close braces or semicolon. ", i);

	}
	if (*braces == 0)
		*main_block = 0;
	return (previous);
}

int	ConfigManager::locationBlock(int *i)
{
	static int		main_block;
	static int		braces;
	static int		previous;

	while (i < this->_tokens.size())
	{
		previous = this->checkKey(i, previous, &braces, &main_block);
		previous = this->checkValue(i, previous);
		previous = this->checkSemicolon(i, previous);
		previous = this->checkOpenBrace(i, previous, &braces, main_block);
		previous = this->checkCloseBrace(i , previous, &braces, &main_block);
		if (previous == 5 && braces == 0)
			return (i);
		i++;
	}
	return (i);
}

void	ConfigManager::errorHandleShit(void)
{
	static size_t	i;
	static int		main_block;
	static int		braces;
	static int		previous;

	while (i < this->_tokens.size())
	{
		if (this->_tokens[i].getType() == CONTEXT) // 0
			printError("Random word out of blocks. ", i);
	
		// if (this->_tokens[i].getType() == KEY) // 1
		// {
		// 	if ((previous == 3 || previous == 4 || previous == 5) || main_block == 0)
		// 		previous = 1;
		// 	else
		// 		printError("Key is not after braces or semicolon. ", i);


			
		// 	if (this->_tokens[i].getToken() == this->_serverVar[1]) // location
		// 	{
		// 		// i = this->locationBlock(i, previous);

		// 		if (this->_tokens[i + 1].getType() != VALUE)
		// 			printError("I handled it bitch ( not a value after location ). ", i);
		// 		if (!(std::find(this->_locationVar.begin(), this->_locationVar.end(), this->_tokens[i + 1].getToken()) != this->_locationVar.end()))
		// 			printError("Not a valid string for Location block. ", i);
		// 	}


		// 	if (main_block == 1 && this->_tokens[i].getToken() == this->_serverVar[0])
		// 			printError("Server cannot be non-main directive. ", i);


		// 	if (main_block == 0)
		// 	{
		// 		// std::cout << "entered: " << braces << std::endl;
		// 		if (this->_tokens[i].getToken() != this->_serverVar[0])
		// 			printError("Invalid main directive (should be server). ", i);
		// 		if (braces > 0)
		// 			printError("Invalid number of braces.", i);
		// 		main_block = 1;
		// 	}
		// 	if (!(std::find(this->_serverVar.begin(), this->_serverVar.end(),
		// 		this->_tokens[i].getToken()) != this->_serverVar.end())) // server
		// 		printError("Not a valid string for Server block. ", i);
		// }
		previous = this->checkKey(i, previous, &braces, &main_block);
		previous = this->checkValue(i, previous);
		previous = this->checkSemicolon(i, previous);
		previous = this->checkOpenBrace(i, previous, &braces, main_block);
		previous = this->checkCloseBrace(i , previous, &braces, &main_block);
		i++;
	}
	if (braces > 0)
		std::cout << "Not enough closing braces. " << std::endl;
		// printError("Not enough closing braces at the end. ", i);
	return ;
}
