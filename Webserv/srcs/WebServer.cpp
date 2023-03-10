/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:27:11 by schuah            #+#    #+#             */
/*   Updated: 2023/03/10 14:01:06 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/WebServer.hpp"

WebServer::WebServer(std::string configFilePath): _configFilePath(configFilePath)
{
	this->_configManager = ConfigManager(configFilePath);
	
	//Temporary to host 2 ports
	this->_serverAddr.resize(2);
	this->_serverFd.resize(2); 
}

WebServer::~WebServer() {}

/* TO BE REMOVED */
void	WebServer::_perrorExit(std::string msg)
{
	std::cerr << RED << msg << ": ";
	perror("");
	std::cerr << RESET;
	exit(EXIT_FAILURE);
}

/* TO BE REMOVED */
int	ft_poll2(pollfd (&fds)[1], int fd, void *buffer, size_t size, Mode mode)
{
	int	ret;

	ret = poll(fds, 1, WS_TIMEOUT);
	if (ret == -1)
	{
		std::cout << RED << "Poll error" << RESET << std::endl;
		return (-1);
	}
	else if (ret == 0)
	{
		std::cout << RED << "Poll timeout" << RESET << std::endl;
		return (-1);
	}
	else if (fds[0].revents & POLLIN && mode == READ)
		return (read(fd, buffer, size));
	else if (fds[0].revents & POLLOUT && mode == WRITE)
		return (write(fd, buffer, size));
	return (0);
}

/* TO BE REMOVED */
int	WebServer::ft_select2(int fd, void *buffer, size_t size, Mode mode)
{
    if (mode == READ)
        FD_SET(fd, &this->read_fds);
    else if (mode == WRITE)
        FD_SET(fd, &this->write_fds);

    timeval	timeout;
    timeout.tv_sec = WS_TIMEOUT;
    timeout.tv_usec = 0;

    int num_ready = select(fd + 1, &this->read_fds, &this->write_fds, nullptr, &timeout);
    if (num_ready == -1)
	{
        std::cerr << RED << "Error: select() failed." << RESET << std::endl;
        return (-1);
    }
    else if (num_ready == 0)
	{
        std::cout << RED << "Select timeout." << RESET << std::endl;
        return (0);
    }

    if (FD_ISSET(fd, &read_fds) && mode == READ)
        return (read(fd, buffer, size));
    else if (FD_ISSET(fd, &write_fds) && mode == WRITE)
        return (write(fd, buffer, size));
    return (0);
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

	if (getaddrinfo(WS_SERVER_NAME, std::to_string(WS_PORT).c_str(), &hints, &res) != 0)
		this->_perrorExit("Getaddrinfo Error");
	
	memcpy(&this->_serverAddr[0], res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	this->_serverAddr[0].sin_port = htons(WS_PORT);

	if (bind(this->_serverFd[0], (sockaddr *)&this->_serverAddr[0], sizeof(this->_serverAddr[0])) < 0)
		this->_perrorExit("Bind Error 1");
	if (listen(this->_serverFd[0], WS_BACKLOG) < 0)
		this->_perrorExit("Listen Error");

	// Trying port 9090
	int	port = 9090;
	if ((this->_serverFd[1] = socket(WS_DOMAIN, WS_TYPE, WS_PROTOCOL)) < 0)
		this->_perrorExit("Socket Error");

	if (getaddrinfo(WS_SERVER_NAME, std::to_string(port).c_str(), &hints, &res) != 0)
		this->_perrorExit("Getaddrinfo Error");
	
	memcpy(&this->_serverAddr[1], res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	this->_serverAddr[1].sin_port = htons(port);

	if (bind(this->_serverFd[1], (sockaddr *)&this->_serverAddr[1], sizeof(this->_serverAddr[1])) < 0)
		this->_perrorExit("Bind Error 2");
	if (listen(this->_serverFd[1], WS_BACKLOG) < 0)
		this->_perrorExit("Listen Error");

	FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
}

int	WebServer::_handleGet()
{
	std::ifstream	file(this->_path.c_str() + 1);
	if (file.fail())
	{
		std::cerr << RED << "Error opening " << this->_path << "!\n" << RESET << std::endl;
		std::string response_body = "404 Not Found";
		std::string response = "HTTP/1.1 404 Not Found\r\nContent-Length: " + std::to_string(response_body.length()) + "\r\n\r\n" + response_body;
		send(this->_socket, response.c_str(), response.length(), 0);
		close(this->_socket);
		return (1);
	}

	file.seekg(0, std::ios::end);
	long	file_size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::string	file_contents;
	file_contents.resize(file_size + 1);
	if (file.read(&file_contents[0], file_size).fail())
	{
		std::cerr << RED << "Error reading " << this->_path << "!\n" << RESET << std::endl;
		file.close();
		close(this->_socket);
		return (1);
	}
	file.close();

	std::string	http_response = "HTTP/1.1 200 OK\r\nContent-Type: */*\r\nContent-Length: " + std::to_string(file_size) + "\r\n\r\n" + file_contents;
	size_t	sent = 0;
	while (sent < http_response.size())
	{
		size_t actually_sent = ft_select2(this->_socket, &http_response[sent], http_response.size() - sent, WRITE);
		if (actually_sent < 0)
			std::cerr << RED << "WRITE FAILED" << RESET << std::endl;
		if (actually_sent == 0)
		{
			close(this->_socket);
			return (0);
		}
		std::cout << "Actually sent: " << actually_sent << "\tSent: " << sent << " / " << http_response.size() << std::endl;
		sent += actually_sent;
	}
	
	std::cout << "Stopped\n";
	close(this->_socket);
	return (0);
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

		std::string	buffer;
		buffer.resize(WS_BUFFER_SIZE, '\0');
		valread = ft_select2(this->_socket, &buffer[0], WS_BUFFER_SIZE, READ);
		buffer.resize(valread);

		std::string	method, query, contentType;
		int		contentLength = 0;
		std::istringstream	request(buffer);
		
		request >> method >> this->_path;
		if (this->_path == "/favicon.ico") // Ignore favicon
		{
			std::cout << RED << "Go away favicon" << RESET << std::endl;
			close(this->_socket);
			continue;
		}
		std::cout << buffer;

		if (method == "POST")
		{
			HttpPostResponse	postResponse(this->_fds, this->_socket, contentLength, valread, buffer);
			postResponse.handlePost();
		}
		else if (method == "GET" && this->_path != "/" && this->_path.find(".php") == std::string::npos && this->_path.find(".py") == std::string::npos && this->_path.find(".cgi") == std::string::npos) // Will be determined by the config
		{
			if (this->_handleGet())
				continue ;
		}
		else if (this->_path.find('.') != std::string::npos)
		{
			HttpCgiResponse	cgiResponse(this->_fds, this->_path, method, this->_socket, contentLength);
			cgiResponse.handleCgi();
		}
		else
		{
			HttpDefaultResponse	defaultResponse(this->_fds, this->_socket);
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
