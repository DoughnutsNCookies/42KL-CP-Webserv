/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:27:11 by schuah            #+#    #+#             */
/*   Updated: 2023/03/14 22:44:33 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/WebServer.hpp"

/* Class constructor that takes in configFilePath string */
WebServer::WebServer(std::string configFilePath)
{
	this->_database = EuleeHand(configFilePath, ConfigManager(configFilePath));
	this->_configManager = ConfigManager(configFilePath);
}

WebServer::~WebServer(void) {}

void	WebServer::_setupServer()
{
	addrinfo	hints, *res;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	this->_database.serverAddr.resize(this->_database.server.size());
	this->_database.serverFd.resize(this->_database.server.size()); 

	
	// Default port
	for (size_t i = 0; i < this->_database.server.size(); i++)
	{
		if ((this->_database.serverFd[i] = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			this->_database.perrorExit("Socket Error");

		int	optval = 1;
		if (setsockopt(this->_database.serverFd[i], SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof(optval)) == -1) //Done to keep socket alive even after Broken Pipe
			this->_database.perrorExit("Setsockopt Error");

		this->_database.server[i][SERVER_NAME].push_back("localhost");
		if (getaddrinfo(this->_database.server[i][SERVER_NAME][0].c_str(), this->_database.server[i][LISTEN][0].c_str(), &hints, &res) != 0)
			this->_database.perrorExit("Getaddrinfo Error");
		
		memcpy(&this->_database.serverAddr[i], res->ai_addr, res->ai_addrlen);
		freeaddrinfo(res);
		this->_database.serverAddr[i].sin_port = htons(std::stoi(this->_database.server[i][LISTEN][0]));

		if (bind(this->_database.serverFd[i], (sockaddr *)&this->_database.serverAddr[i], sizeof(this->_database.serverAddr[i])) < 0)
			this->_database.perrorExit("Bind Error");
		if (listen(this->_database.serverFd[i], WS_BACKLOG) < 0)
			this->_database.perrorExit("Listen Error");
	}
}

int	WebServer::_unchunkResponse() // Util
{
	std::string	header = this->_database.buffer.substr(0, this->_database.buffer.find("\r\n\r\n"));
	std::string	output;

	if (header.find("Transfer-Encoding: chunked") == std::string::npos)
		return (0);
	std::string	remaining = this->_database.buffer.substr(this->_database.buffer.find("\r\n\r\n") + 4);
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
	this->_database.buffer = header + "\r\n\r\n" + newBody;
	return (1);
}

int	WebServer::_checkExcept(std::string method) // Util
{
	if (this->_database.server[this->_database.serverIndex].location.find(this->_database.methodPath) == this->_database.server[this->_database.serverIndex].location.end())
		return (0);
	int	found = 0;
	if (this->_database.server[this->_database.serverIndex].location[this->_database.methodPath][LIMIT_EXCEPT].size() == 0)
		return (0);
	for (size_t j = 0; j < this->_database.server[this->_database.serverIndex].location[this->_database.methodPath][LIMIT_EXCEPT].size(); j++)
	{
		if (this->_database.server[this->_database.serverIndex].location[this->_database.methodPath][LIMIT_EXCEPT][j] == method)
			found++;
	}
	if (found == 0)
	{
		std::string response = "HTTP/1.1 405 Method Not Allowed\r\n\r\n";
		this->_database.ft_select(this->_database.socket, (void *)response.c_str(), response.size(), WRITE);
		close(this->_database.socket);
		return (1);
	}
	return (0);
}

// int	WebServer::_checkLocation() // Util
// {
// 	for (size_t i = 0; i < this->_database.server.size(); i++)
// 	{
// 		if (this->_database.server[i].location.find(this->_database.methodPath) != this->_database.server[i].location.end())
// 		{
// 			std::string response = "HTTP/1.1 200 OK\r\n\r\n";
// 			this->_database.ft_select(this->_database.socket, (void *)response.c_str(), response.size(), WRITE);
// 			close(this->_database.socket);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

int		WebServer::_isCGI() // Util
{
	size_t extensionPos = this->_database.methodPath.find_last_of('.');
	if (extensionPos == std::string::npos)
		return (0);
	std::string extension = this->_database.methodPath.substr(extensionPos);
	for (size_t i = 0; i < this->_database.server[this->_database.serverIndex][CGI].size(); i++)
		if (this->_database.server[this->_database.serverIndex][CGI][i] == extension)
			return (1);
	return (0);
}

void	WebServer::_convertLocation()
{
	size_t	firstSlashPos = this->_database.methodPath.find("/", 1);
	std::string	locationToFind = this->_database.methodPath;
	if (firstSlashPos != std::string::npos)
		locationToFind = "/" + this->_database.methodPath.substr(1, firstSlashPos - 1);
	if (this->_database.server[this->_database.serverIndex].location.find(locationToFind) == this->_database.server[this->_database.serverIndex].location.end())
		return ;
	if (this->_database.server[this->_database.serverIndex].location[locationToFind][ROOT].size() == 0)
		return ;
	
	std::string root = this->_database.server[this->_database.serverIndex].location[locationToFind][ROOT][0];
	std::string newPath = root + this->_database.methodPath.substr(this->_database.methodPath.find(root) + root.length());
	std::cout << GREEN << "New path: " << this->_database.methodPath << RESET << std::endl;
	this->_database.methodPath = "/" + root + this->_database.methodPath.substr(this->_database.methodPath.find(root) + root.length());
}

void	WebServer::_serverLoop()
{
	while(1)
	{
		std::cout << CYAN << "Port Accepted: ";
		for (size_t i = 0; i < this->_database.server.size(); i++)
			std::cout << this->_database.server[i][LISTEN][0] << " ";
		std::cout << "\nWaiting for new connection..." << RESET << std::endl;
		this->_database.socket = 0;
		for (size_t i = 0; i < this->_database.server.size(); i++)
			fcntl(this->_database.serverFd[i], F_SETFL, O_NONBLOCK);
		while (this->_database.socket <= 0)
		{
			for (size_t i = 0; i < this->_database.server.size(); i++)
			{
				this->_database.socket = accept(this->_database.serverFd[i], NULL, NULL);
				if (this->_database.socket != -1)
				{
					this->_database.serverIndex = i;
					break ;
				}
			}
		}
		if (this->_database.socket < 0)
			this->_database.perrorExit("Accept Error");

		size_t		total = 0;
		char		readBuffer[WS_BUFFER_SIZE];
		this->_database.buffer.clear();
		long		valread = this->_database.ft_select(this->_database.socket, readBuffer, WS_BUFFER_SIZE, READ);
		while (valread > 0)
		{
			total += valread;
			std::cout << GREEN << "Received: " << valread << "\tTotal: " << total << RESET << std::endl;
			if (valread < 0)
			{
				close(this->_database.socket);
				return ;
			}
			this->_database.buffer.append(readBuffer, valread);
			valread = this->_database.ft_select(this->_database.socket, readBuffer, WS_BUFFER_SIZE, READ);
		}

		if (this->_unchunkResponse() == -1)
		{
			close(this->_database.socket);
			continue ;
		}

		std::string			method;
		std::istringstream	request(this->_database.buffer);
		
		request >> method >> this->_database.methodPath;
		if (this->_database.methodPath == "/favicon.ico") // Ignore favicon
		{
			std::string	message = "Go away favicon";
			std::cout << RED << message << RESET << std::endl;
			std::string response = "HTTP/1.1 404 Not Found\r\n\r\n" + message;

			this->_database.ft_select(this->_database.socket, (void *)response.c_str(), response.length(), WRITE);
			close(this->_database.socket);
			continue;
		}
		std::cout << BLUE << this->_database.buffer.substr(0, this->_database.buffer.find("\r\n\r\n")) << RESET << std::endl;
		// std::cout << BLUE << this->_database.buffer << RESET << std::endl;

		// std::cout << this->_database.methodPath << std::endl;
		// if (this->_database.methodPath == "/directory/youpi.bad_extension")
		// {
		// 	std::string response = "HTTP/1.1 200 OK\r\n\r\n";
		// 	this->_database.ft_select(this->_database.socket, (void *)response.c_str(), response.size(), WRITE);
		// 	close(this->_database.socket);
		// 	continue ;
		// }

		this->_convertLocation();
		if (this->_checkExcept(method))
			continue ;
		// if (this->_checkDirectory())
		// 	continue ;

		if (method == "HEAD")
		{
			std::cout << MAGENTA << "Head method called" << RESET << std::endl;
			HttpHeadResponse	headResponse(this->_database);
			headResponse.handleHead();
		}
		else if (method == "POST")
		{
			std::cout << MAGENTA << "Post method called" << RESET << std::endl;
			HttpPostResponse	postResponse(this->_database);
			postResponse.handlePost();
		}
		else if (method == "PUT")
		{
			std::cout << MAGENTA << "Put method called" << RESET << std::endl;
			HttpPutResponse	putResponse(this->_database);
			putResponse.handlePut();
		}
		else if (method == "DELETE")
		{
			std::cout << MAGENTA << "Delete method called" << RESET << std::endl;
			HttpDeleteResponse	deleteResponse(this->_database);
			deleteResponse.handleDelete();
		}
		else if (method == "GET" && this->_database.methodPath != "/" && this->_isCGI() == 0) // Will be determined by the config
		{
			std::cout << MAGENTA << "Get method called" << RESET << std::endl;
			HttpGetResponse	getResponse(this->_database);
			getResponse.handleGet();
		}
		else if (this->_database.methodPath.find('.') != std::string::npos)
		{
			std::cout << MAGENTA << "CGI method called" << RESET << std::endl;
			HttpCgiResponse	cgiResponse(this->_database);
			cgiResponse.handleCgi();
		}
		else
		{
			std::cout << MAGENTA << "Default method called" << RESET << std::endl;
			HttpDefaultResponse	defaultResponse(this->_database);
			defaultResponse.handleDefault();
		}
	}
}

void	WebServer::runServer(void)
{
	this->_database.parseConfigFile();
	std::cout << GREEN "Config File Parsing Done..." RESET << std::endl;
	this->_database.configLibrary();
	this->_database.errorHandleShit();
	std::cout << GREEN "Error Handling File Done..." RESET << std::endl;
	this->_database.parseConfigServer();
	this->_database.printServers();
	std::cout << GREEN "Config Server Parsing Done..." RESET << std::endl;
	this->_setupServer();
	this->_serverLoop();
}
