/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:27:11 by schuah            #+#    #+#             */
/*   Updated: 2023/03/11 18:16:09 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/WebServer.hpp"

#include <signal.h>

WebServer::WebServer(std::string configFilePath): _configFilePath(configFilePath)
{
	this->_configManager = ConfigManager(configFilePath);
	
	//Temporary to host 2 ports
	this->_serverAddr.resize(2);
	this->_serverFd.resize(2); 
}

WebServer::~WebServer() {}

/* TO BE REMOVED */
void	WebServer::_perrorExit(std::string msg, int exitTrue)
{
	std::cerr << RED << msg << ": ";
	perror("");
	std::cerr << RESET;
	if (exitTrue)
		exit(EXIT_FAILURE);
}

/* TO BE REMOVED */
long	WebServer::ft_select2(int fd, void *buffer, size_t size, Mode mode)
{
	fd_set read_fds, write_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);

	FD_SET(fd, (mode == READ) ? &read_fds : &write_fds);

    timeval	timeout;
    timeout.tv_sec = WS_TIMEOUT;
    timeout.tv_usec = 0;

    int num_ready = select(fd + 1, &read_fds, &write_fds, NULL, &timeout);
    if (num_ready == -1)
	{
		this->_perrorExit("Select Error", 0);
        return (-1);
    }
    else if (num_ready == 0)
	{
        std::cout << RED << "Select timeout!" << RESET << std::endl;
        return (0);
    }

	long	val = 0;
    if (FD_ISSET(fd, &read_fds) && mode == READ)
	{
		val = read(fd, buffer, size);
		if (val == -1)
			this->_perrorExit("Read Error", 0);
	}
    else if (FD_ISSET(fd, &write_fds) && mode == WRITE)
	{
		val = write(fd, buffer, size);
		if (val == -1)
			this->_perrorExit("Write Error", 0);
	}
	return (val);
}

void	WebServer::_setupServer()
{
	addrinfo	hints, *res;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = WS_DOMAIN;
	hints.ai_socktype = WS_TYPE;
	hints.ai_flags = WS_FLAGS;

	// Default port
	if ((this->_serverFd[0] = socket(WS_DOMAIN, WS_TYPE, WS_PROTOCOL)) < 0)
		this->_perrorExit("Socket Error");

	int	optval = 1;
	if (setsockopt(this->_serverFd[0], SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof(optval)) == -1) //Done to keep socket alive even after Broken Pipe
		this->_perrorExit("Setsockopt Error");

	if (getaddrinfo(WS_SERVER_NAME, std::to_string(WS_PORT).c_str(), &hints, &res) != 0)
		this->_perrorExit("Getaddrinfo Error");
	
	memcpy(&this->_serverAddr[0], res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	this->_serverAddr[0].sin_port = htons(WS_PORT);

	if (bind(this->_serverFd[0], (sockaddr *)&this->_serverAddr[0], sizeof(this->_serverAddr[0])) < 0)
		this->_perrorExit("Bind Error");
	if (listen(this->_serverFd[0], WS_BACKLOG) < 0)
		this->_perrorExit("Listen Error");

	// Trying port 9090
	int	port = 9090;
	if ((this->_serverFd[1] = socket(WS_DOMAIN, WS_TYPE, WS_PROTOCOL)) < 0)
		this->_perrorExit("Socket Error");

	int	optval2 = 1;
	if (setsockopt(this->_serverFd[1], SOL_SOCKET, SO_NOSIGPIPE, &optval2, sizeof(optval)) == -1)
		this->_perrorExit("Setsockopt Error");

	if (getaddrinfo(WS_SERVER_NAME, std::to_string(port).c_str(), &hints, &res) != 0)
		this->_perrorExit("Getaddrinfo Error");
	
	memcpy(&this->_serverAddr[1], res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	this->_serverAddr[1].sin_port = htons(port);

	if (bind(this->_serverFd[1], (sockaddr *)&this->_serverAddr[1], sizeof(this->_serverAddr[1])) < 0)
		this->_perrorExit("Bind Error");
	if (listen(this->_serverFd[1], WS_BACKLOG) < 0)
		this->_perrorExit("Listen Error");
}

int	WebServer::_unchunkResponse()
{
	std::string	header = this->_buffer.substr(0, this->_buffer.find("\r\n\r\n"));
	std::string	output;

	if (header.find("Transfer-Encoding: chunked") == std::string::npos)
		return (0);
	std::string	remaining = this->_buffer.substr(this->_buffer.find("\r\n\r\n") + 4);
	std::string	newBody = "";

	while (remaining.find("\r\n") != std::string::npos)
	{
		std::string	chunkSize = remaining.substr(0, remaining.find("\r\n"));
		int			size = std::stoi(chunkSize, 0, 16);
		std::cout << size << std::endl;
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
	this->_buffer = header + "\r\n\r\n" + newBody;
	return (1);
}

void	WebServer::_serverLoop()
{
	long	valread;

	while(1)
	{
		std::cout << CYAN << "Port: " << WS_PORT << "\nWaiting for new connection..." << RESET << std::endl;
		this->_socket = 0;
		fcntl(this->_serverFd[0], F_SETFL, O_NONBLOCK);
		fcntl(this->_serverFd[1], F_SETFL, O_NONBLOCK);
		int i = 0;
		while (this->_socket <= 0)
		{
			for (i = 0; i < 2; i++)
			{
				this->_socket = accept(this->_serverFd[i], NULL, NULL);
				if (this->_socket != -1)
					break ;
			}
		}
		if (this->_socket < 0)
			this->_perrorExit("Accept Error");

		size_t		total = 0;
		char		readBuffer[WS_BUFFER_SIZE];
		valread = ft_select2(this->_socket, readBuffer, WS_BUFFER_SIZE, READ);
		while (valread > 0)
		{
			total += valread;
			std::cout << GREEN << "Received: " << valread << "\tTotal: " << total << RESET << std::endl;
			if (valread < 0)
			{
				close(this->_socket);
				return ;
			}
			this->_buffer.append(readBuffer, valread);
			valread = ft_select2(this->_socket, readBuffer, WS_BUFFER_SIZE, READ);
		}

		if (this->_unchunkResponse() == -1)
		{
			close(this->_socket);
			continue ;
		}

		std::string	method, query, contentType;
		std::istringstream	request(this->_buffer);
		
		request >> method >> this->_path;
		if (this->_path == "/favicon.ico") // Ignore favicon
		{
			std::cout << RED << "Go away favicon" << RESET << std::endl;
			close(this->_socket);
			continue;
		}
		std::cout << BLUE << this->_buffer.substr(0, this->_buffer.find("\r\n\r\n")) << RESET << std::endl;

		if (method == "POST")
		{
			HttpPostResponse	postResponse(this->_socket, this->_buffer);
			postResponse.handlePost();
		}
		else if (method == "GET" && this->_path != "/" && this->_path.find(".php") == std::string::npos && this->_path.find(".py") == std::string::npos && this->_path.find(".cgi") == std::string::npos) // Will be determined by the config
		{
			HttpGetResponse	getResponse(this->_path, this->_socket);
			getResponse.handleGet();
		}
		else if (this->_path.find('.') != std::string::npos)
		{
			HttpCgiResponse	cgiResponse(this->_path, method, this->_socket);
			cgiResponse.handleCgi();
		}
		else
		{
			HttpDefaultResponse	defaultResponse(this->_socket);
			defaultResponse.handleDefault();
		}
	}
}

void	WebServer::runServer()
{
	this->_configManager.parseConfigFile();
	this->_setupServer();
	this->_serverLoop();
}
