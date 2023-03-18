/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleeHand.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:13:53 by jhii              #+#    #+#             */
/*   Updated: 2023/03/17 14:51:33 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EuleeHand.hpp"

EuleeHand::EuleeHand(void) : statusList(), envp(), cgi(), server(), serverFd(), serverAddr(), methodPath(), buffer(), socket(), serverIndex(), useDefaultIndex(), _configFilePath(), _configManager() {}

EuleeHand::EuleeHand(std::string configFilePath, ConfigManager const &configManager) :  statusList(), envp(), cgi(), server(), serverFd(), serverAddr(), methodPath(), buffer(), socket(), serverIndex(), useDefaultIndex(), _configFilePath(configFilePath), _configManager(configManager) {}

EuleeHand::~EuleeHand(void) {}

void	EuleeHand::printTokens(void)
{
	this->_configManager.printTokens();
}

void	EuleeHand::parseConfigFile(void)
{
	this->_configManager.parseConfigFile();
}

void	EuleeHand::configLibrary(void)
{
	this->_configManager.configLibrary();
}

void	EuleeHand::errorHandleShit(void)
{
	this->_configManager.errorHandleShit();
}

void	EuleeHand::printServers(void)
{
	for (size_t i = 0; i < this->server.size(); ++i)
	{
		std::cout << "=======================" << std::endl;
		std::cout << CYAN "server " << i + 1 << RESET << std::endl;
		for (EuleePocket::iterator it = this->server[i].begin(); it != this->server[i].end(); ++it)
		{
			std::cout << CYANNORM << it->first << " : ";
			for (size_t k = 0; k < it->second.size(); ++k)
			{
				std::cout << it->second[k];
				if (k + 1 < it->second.size())
					std::cout << " ";
			}
			std::cout << std::endl;
		}
		std::cout << RESET << std::endl;
		for (size_t j = 0; j < this->server[i].vectorLocation.size(); ++j)
		{
			std::cout << BLUE "location " << j + 1 << RESET << std::endl;
			for (EuleePocket::iterator it2 = this->server[i].vectorLocation[j].begin(); it2 != this->server[i].vectorLocation[j].end(); ++it2)
			{
				std::cout << BLUENORM << it2->first << " : ";
				for (size_t d = 0; d < it2->second.size(); ++d)
				{
					std::cout << it2->second[d];
					if (d + 1 < it2->second.size())
						std::cout << " ";
				}
				std::cout << std::endl;
			}
			if (j + 1 < this->server[i].vectorLocation.size())
				std::cout << std::endl;
		}
		std::cout << RESET;
		std::cout << "=======================" << std::endl;
	}
}

// size_t	EuleeHand::_parseCgi(std::vector<Token> &tokens, size_t i)
// {
// 	if (tokens[i].token == "cgi_script" && tokens[i].type == KEY)
// 	{
// 		size_t	j = -1;
// 		size_t	size = 0;
// 		std::string	path;
// 		while (tokens[++j].token != ";")
// 		{
// 			if (tokens[j].token.find('/') >= 0)
// 			{
// 				path = tokens[j].token;
// 				size++;
// 			}
// 		}
// 		if (size > 1)
// 			printError();
// 		// while (tokens[++i].token != ";")
// 		// {
// 		// 	this->cgi[key].push_back(tokens[i].token);
// 		// }
// 	}
// 	return (i);
// }

size_t	EuleeHand::_parsingHelper(std::vector<Token> &tokens, size_t i, EuleeWallet &location, std::string needle, Key key)
{
	if (tokens[i].token == needle && tokens[i].type == KEY)
	{
		while (tokens[++i].token != ";")
			location[key].push_back(tokens[i].token);
	}
	return (i);
}

size_t	EuleeHand::_parseLocation(std::vector<Token> &tokens, std::vector<EuleeWallet> &location, size_t i)
{
	EuleeWallet	loc;

	if (tokens[i].token != "{")
		loc[LOCATION_READ_PATH].push_back(tokens[i++].token);
	while (tokens[i].token != "}")
	{
		i = this->_parsingHelper(tokens, i, loc, "cgi_index", CGI);
		i = this->_parsingHelper(tokens, i, loc, "root", ROOT);
		i = this->_parsingHelper(tokens, i, loc, "index", INDEX);
		i = this->_parsingHelper(tokens, i, loc, "return", RETURN);
		i = this->_parsingHelper(tokens, i, loc, "upload", UPLOAD);
		i = this->_parsingHelper(tokens, i, loc, "include", INCLUDE);
		i = this->_parsingHelper(tokens, i, loc, "error_page", ERROR_PAGE);
		i = this->_parsingHelper(tokens, i, loc, "auto_index", AUTO_INDEX);
		i = this->_parsingHelper(tokens, i, loc, "limit_except", LIMIT_EXCEPT);
		i = this->_parsingHelper(tokens, i, loc, "client_max_body_size", CLIENT_MAX_BODY_SIZE);
		++i;
	}
	location.push_back(EuleeWallet(loc));
	return (i);
}

size_t	EuleeHand::_parseServer(std::vector<Token> &tokens, size_t i)
{
	EuleeWallet					serv;
	std::vector<EuleeWallet>	location;

		// i = this->_parseCgi(tokens, i);
	while (i < tokens.size() && tokens[i].token != "server")
	{
		i = this->_parsingHelper(tokens, i, serv, "cgi_index", CGI);
		i = this->_parsingHelper(tokens, i, serv, "root", ROOT);
		i = this->_parsingHelper(tokens, i, serv, "index", INDEX);
		i = this->_parsingHelper(tokens, i, serv, "listen", LISTEN);
		i = this->_parsingHelper(tokens, i, serv, "return", RETURN);
		i = this->_parsingHelper(tokens, i, serv, "upload", UPLOAD);
		i = this->_parsingHelper(tokens, i, serv, "include", INCLUDE);
		i = this->_parsingHelper(tokens, i, serv, "auto_index", AUTO_INDEX);
		i = this->_parsingHelper(tokens, i, serv, "error_page", ERROR_PAGE);
		i = this->_parsingHelper(tokens, i, serv, "server_name", SERVER_NAME);
		i = this->_parsingHelper(tokens, i, serv, "limit_except", LIMIT_EXCEPT);
		i = this->_parsingHelper(tokens, i, serv, "client_max_body_size", CLIENT_MAX_BODY_SIZE);
		if (tokens[i].token == "location")
			i = this->_parseLocation(tokens, location, ++i);
		++i;
	}
	this->server.push_back(EuleePocket(serv, location));
	return (++i);
}

void	EuleeHand::parseConfigServer(void)
{
	std::vector<Token>	tokens = this->_configManager.getToken();

	size_t	i = 1;
	while (i < tokens.size())
		i = this->_parseServer(tokens, i);
	std::map<std::string, std::string>	unique;
	for (size_t n = 0; n < this->server.size(); ++n)
	{
		for (size_t m = 0; m < this->server[n][LISTEN].size(); ++m)
		{
			if (unique.find(this->server[n][LISTEN][m]) == unique.end())
				unique[this->server[n][LISTEN][m]] = this->server[n][LISTEN][m];
			else if (n != 0)
			{
				this->server.erase(this->server.begin() + n--);
				break ;
			}
		}
	}
	for (size_t j = 0; j < this->server.size(); j++)
		for (size_t k = 0; k < this->server[j].vectorLocation.size(); k++)
			this->server[j].location[this->server[j].vectorLocation[k][LOCATION_READ_PATH][0]] = this->server[j].vectorLocation[k];
	this->statusList[200] = "OK";
	this->statusList[404] = "Not Found";
	this->statusList[405] = "Not Allowed";
}

void	EuleeHand::perrorExit(std::string msg, int exitTrue)
{
	std::cerr << RED << msg << ": ";
	perror("");
	std::cerr << RESET;
	if (exitTrue)
		exit(EXIT_FAILURE);
}

long	EuleeHand::ft_select(int fd, void *buff, size_t size, Mode mode)
{
	fd_set	readFds, writeFds;
	FD_ZERO(&readFds);
	FD_ZERO(&writeFds);
	FD_SET(fd, (mode == READ) ? &readFds : &writeFds);

	timeval	timeout;
	timeout.tv_sec = WS_TIMEOUT;
	timeout.tv_usec = 0;

	int	ret = select(FD_SETSIZE, &readFds, &writeFds, NULL, &timeout);
	if (ret == -1)
	{
		this->perrorExit("Select Error", 0);
		return (-1);
	}
	else if (ret == 0)
	{
		std::cout << RED << "Select timeout!" << RESET << std::endl;
		return (0);
	}

	long	val = 0;
	if (FD_ISSET(fd, &readFds) && mode == READ)
	{
		val = recv(fd, buff, size, 0);
		if (val == -1)
			this->perrorExit("Read Error", 0);
	}
	else if (FD_ISSET(fd, &writeFds) && mode == WRITE)
	{
		val = send(fd, buff, size, 0);
		if (val == -1)
			this->perrorExit("Write Error", 0);
	}
	return (val);
}

int	EuleeHand::checkPath(std::string path, int isFile, int isDirectory)
{
    std::ifstream   temp(path + "/");
    if (temp.good() && isFile == 1 && isDirectory == 0)
        return (0);
	std::ifstream	file(path);
	if (file.good()) // is a directory and a file
	{
		if (path[path.length() - 1] == '/')
        {
            if (isDirectory)
                return (1);
            if (isFile)
                return (0);
        }
		std::ifstream	directory(path + "/");
        if (directory.good() && isDirectory) // directory
                return (1);
        if (isFile)
            return (1);
	}
	return (0);
}

int	EuleeHand::isCGI(void)
{
	size_t extensionPos = this->methodPath.find_last_of('.');
	if (extensionPos == std::string::npos)
		return (0);
	std::string extension = this->methodPath.substr(extensionPos);
	for (size_t i = 0; i < this->server[this->serverIndex][CGI].size(); i++)
		if (this->server[this->serverIndex][CGI][i] == extension)
			return (1);
	return (0);
}

int	EuleeHand::checkExcept(void)
{
	if (this->server[this->serverIndex].location.find(this->methodPath) == this->server[this->serverIndex].location.end())
		return (0);
	int	found = 0;
	if (this->server[this->serverIndex].location[this->methodPath][LIMIT_EXCEPT].size() == 0)
		return (0);
	for (size_t j = 0; j < this->server[this->serverIndex].location[this->methodPath][LIMIT_EXCEPT].size(); j++)
	{
		if (this->server[this->serverIndex].location[this->methodPath][LIMIT_EXCEPT][j] == this->method)
			found++;
	}
	if (found == 0)
	{
		std::string response = "HTTP/1.1 405 Method Not Allowed\r\n\r\n";
		this->ft_select(this->socket, (void *)response.c_str(), response.size(), WRITE);
		close(this->socket);
		return (1);
	}
	return (0);
}

int	EuleeHand::unchunkResponse(void)
{
	std::string	output;
	std::string	header = this->buffer.substr(0, this->buffer.find("\r\n\r\n"));

	if (header.find("Transfer-Encoding: chunked") == std::string::npos)
		return (0);
	std::string	remaining = this->buffer.substr(this->buffer.find("\r\n\r\n") + 4);
	std::string	newBody = "";

	while (remaining.find("\r\n") != std::string::npos)
	{
		std::string	chunkSize = remaining.substr(0, remaining.find("\r\n"));
		size_t		size = std::stoul(chunkSize, 0, 16);
		if (size == 0)
			return (0);
		if (size > remaining.size() - std::strlen("\r\n"))
		{
			std::cout << RED << "Error: Chunk size is bigger than remaining size" << RESET << std::endl;
			return (-1);
		}
		newBody += remaining.substr(remaining.find("\r\n") + std::strlen("\r\n"), size);
		remaining = remaining.substr(remaining.find("\r\n") + size + std::strlen("\r\n\r\n"));
	}
	this->buffer = header + "\r\n\r\n" + newBody;
	return (1);
}

void	EuleeHand::convertLocation(void)
{
	/*
	 * Extract methodPath 
	 * strcmp each location path to method path to see whether it is a location or not
	 * -> If yes, check whether it has file trailing behind or not ....
	 * 		-> If yes, then we check whether it is file or directory
	 * 			-> If file, then we serve the file + 200 OK
	 * 			-> If directory, then do step below
	 * 		-> If no, then 404 Not Found
	 * -> If no, then we find whether it has index specified in the location block or not XXX
	 * 		-> If yes, then we append it back to methodPath and find
	 * 			-> If found, then we serve the file + 200 OK
	 * 			-> If not found, 404 Not found
	 * 		-> If no, then we go back to server block to find index
	 * 			-> If yes, then we append it back to methodPath and find
	 * 				-> If found, then we serve the file + 200 OK
	 * 				-> If not found, then 404 Not found
	 * 			-> If no, then 404 Not found
	 */

	this->useDefaultIndex = 0;
	EuleePocket	myServer = this->server[this->serverIndex];
	std::string	methodPathCopy = this->methodPath.c_str();
	size_t		longestPathSize = 0;
	std::string	locationPath, pathToFind, locationRoot, newPath, indexFile;
	for (std::map<std::string, EuleeWallet>::iterator it = myServer.location.begin(); it != myServer.location.end(); it++)
	{
		if (strncmp(it->first.c_str(), methodPathCopy.c_str(), it->first.length()) == 0 && it->first.length() > longestPathSize)
		{
			longestPathSize = it->first.length();
			locationPath = it->first;
		}
	}
	newPath = this->methodPath;
	if (methodPathCopy.length() - locationPath.length() > 1)
	{
		std::cout << "Trailing File" << std::endl;
		if (myServer.location[locationPath][ROOT].size() != 0)
		{
			locationRoot = myServer.location[locationPath][ROOT][0];
			newPath = locationRoot + methodPathCopy.substr(locationPath.length());
		}
		if (this->checkPath(newPath, 1, 1)) // Either file or directory
		{
			std::cout << "Found" << std::endl;
			if (this->checkPath(newPath, 1, 0)) // File
			{
				std::cout << "File" << std::endl;
				this->methodPath = "/" + newPath;
				std::cout << "Location Path: " << locationPath << std::endl;
				std::cout << GREEN << "New Path: " << this->methodPath << RESET << std::endl;
				return ;
			}
			else // Directory
				std::cout << "Directory" << std::endl;
		}
		else // Not Found
		{
			std::cout << "Not Found" << std::endl;
			return ;
		}
	}
	// 	-> If yes, then we append it back to methodPath and find
	//  	-> If found, then we serve the file + 200 OK
	//  	-> If not found, 404 Not found
	//  -> If no, then we go back to server block to find index
	//  	-> If yes, then we append it back to methodPath and find
	//  		-> If found, then we serve the file + 200 OK
	//  		-> If not found, then 404 Not found
	//  	-> If no, then 404 Not found
	std::cout << "No Trailing File" << std::endl;
	if (myServer.location[locationPath][INDEX].size() == 0)
	{
		std::cout << "Append back and find" << std::endl;
		indexFile = myServer[INDEX][0];
		this->methodPath = myServer[ROOT][0] + locationRoot + "/" + indexFile; 
		this->useDefaultIndex = 1;
	}
	else
	{
		std::cout << "Using index: " << newPath << std::endl;
		locationRoot = myServer.location[locationPath][ROOT][0];
		std::string	remainingPath = methodPathCopy.erase(0, locationPath.length());
		indexFile = myServer.location[locationPath][INDEX][0];
		this->methodPath = "/" + myServer.location[locationPath][ROOT][0] + remainingPath + "/" + indexFile;
	}
	std::cout << "Location Path: " << locationPath << std::endl;
	std::cout << GREEN << "New Path: " << this->methodPath << RESET << std::endl;
}
/*
-> int    sendHttp(int statusCode, std::string path = "")
    -> std::cout << MAGENTA << "Closed with status code: " << statusCode << RESET << std::endl;
    -> return (statusCode);
    statusCode = 200, 404, 405
    statusMessage = OK, Not Found, Not Allowed
    "HTTP/1.1 {statusCode} {statusCodeMessage}\r\n\r\n"
    Check if string.size() == 0 -> Use our default page as filePath;
     Else -> Check whether the html file exists or not
    If it doesn't exist, then statusCode becomes 404;    
    path = defaultErrorPage
    Else -> Extract html from file
    Apped the content in the .html file to the header -> output = header + html;
    std::cout << MAGENTA << "Closed with status code: " << statusCode << RESET << std::endl;
    ft_select(this->_database.socket, (void *)output.c_str(), output.length(), WRITE)
    close(this->_database.socket);
    return (statusCode);
*/

/*

statusCode
take the statusCode, check from your map, return the statusMessage;
check = statuslist.find(statusCode);
response = "http//1.1 " + statusCode + " " + statusList[statusCode] + " \r\n\r\n";
 
response = response + read(path); //if exist
ft_select();
close(socket);

*/

std::string EuleeHand::extractHTML(std::string path)
{
	std::ifstream file(path);

	if (!file.is_open())
	{
		std::cerr << "Error: Could not open file" << std::endl;
		exit(1);
	}
	std::string extract;
	std::string output;

	while (std::getline(file, output))
		extract = extract + output;
	return (extract);
}

int		EuleeHand::sendHttp(int statusCode, std::string path)
{
	// this->statusList[200] = "OK";
	// this->statusList[404] = "Not Found"; // temps
	// this->statusList[405] = "Not Allowed";

	std::string statusStr = std::to_string(statusCode);
	if (this->statusList.find(statusCode) == this->statusList.end())
	{
		std::cerr << "Find error" << std::endl;
		exit(1);
	}
	std::string response = "http//1.1" + statusStr + " " + statusList[statusCode] + " \r\n\r\n";
	if (path.size() == 0)
	{
		// std::cout << "html default page" << std::endl;
		path =  "./html/index.html";
	}
	else
	{
		if (this->checkPath(path, 1, 0 ) == 0)
		{
			statusCode = 404;
			// std::cout << "error default page" << std::endl;
			path =  "./html/error.html";
		}
	}
	response = response + extractHTML(path);
	std::string code = "{{error_code}}"; // maybe I can find a way to change this trash
	std::string msg = "{{error_message}}";

	if (statusCode != 200)
	{
		response.replace(response.find(code), code.length(), std::to_string(statusCode));	
		response.replace(response.find(code), code.length(), std::to_string(statusCode));	
		response.replace(response.find(msg), msg.length(), this->statusList[statusCode]);
	}
	ft_select(this->socket, (void *)response.c_str(), response.length(), WRITE);
	close (this->socket);
	return (statusCode);
}
