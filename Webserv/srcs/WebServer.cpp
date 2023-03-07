/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:27:11 by schuah            #+#    #+#             */
/*   Updated: 2023/03/07 20:59:50 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"

WebServer::WebServer(std::string configFilePath): _configFilePath(configFilePath)
{
	this->_configManager = ConfigManager(configFilePath);
}

WebServer::~WebServer() {}

void	WebServer::_perrorExit(std::string msg)
{
	std::cerr << RED + msg + ": ";
	perror("");
	std::cerr << RESET;
	exit(EXIT_FAILURE);
}

void	WebServer::_setupServer()
{
	struct addrinfo	hints, *res;

	if ((this->_serverFd = socket(WS_DOMAIN, WS_TYPE, WS_PROTOCOL)) < 0)
		this->_perrorExit("Socket Error");
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = WS_DOMAIN;
	hints.ai_socktype = WS_TYPE;
	hints.ai_flags = WS_FLAGS;

	if (getaddrinfo(WS_SERVER_NAME, std::to_string(WS_PORT).c_str(), &hints, &res) != 0)
		this->_perrorExit("Getaddrinfo Error");
	
	memcpy(&this->_serverAddr, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	this->_serverAddr.sin_port = htons(WS_PORT);

	if (bind(this->_serverFd, (struct sockaddr *)&this->_serverAddr, sizeof(this->_serverAddr)) < 0)
		this->_perrorExit("Bind Error");
	if (listen(this->_serverFd, WS_BACKLOG) < 0)
		this->_perrorExit("Listen Error");
}

void	WebServer::_handlePost(std::string buffer, int content_length, int valread)
{
	size_t	content_length_pos = buffer.find("Content-Length: ");
	if (content_length_pos != std::string::npos)
	{
		content_length_pos += std::strlen("Content-Length: ");
		content_length = std::stoi(buffer.substr(content_length_pos));
	}

	std::string	message_body;
	message_body.resize(content_length);
	valread = read(this->_newSocket, &message_body[0], content_length);

	std::string response_body = "This is the response to your POST request.";
	std::string response = "HTTP/1.1 200 OK\r\nContent-Length: " + std::to_string(response_body.length()) + "\r\n\r\n" + response_body;
	printf("Response: %s\n", response.c_str());
	send(this->_newSocket, response.c_str(), response.length(), 0);
}

int	WebServer::_handleGet()
{
	std::ifstream	file(this->_path.c_str() + 1);
	if (file.fail())
	{
		std::cerr << "Error opening file!" << std::endl;
		std::string response_body = "404 Not Found";
		std::string response = "HTTP/1.1 404 Not Found\r\nContent-Length: " + std::to_string(response_body.length()) + "\r\n\r\n" + response_body;
		send(this->_newSocket, response.c_str(), response.length(), 0);
		close(this->_newSocket);
		return (1);
	}

	file.seekg(0, std::ios::end);
	long	file_size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::string	file_contents;
	file_contents.resize(file_size + 1);
	if (file.read(&file_contents[0], file_size).fail())
	{
		std::cerr << "Error reading file!" << std::endl;
		file.close();
		close(this->_newSocket);
		return (1);
	}
	file.close();

	std::string	http_response = "HTTP/1.1 200 OK\r\nContent-Type: video/mp4\r\nContent-Length: " + std::to_string(file_size) + "\r\n\r\n" + file_contents;
	// printf("Response: %s\n", http_response.c_str());
	printf("File content: %s\n", file_contents.c_str());
	write(this->_newSocket, &http_response[0], http_response.size());
	close(this->_newSocket);
	return (0);
}

// void	WebServer::_handleCgi(std::string method, int contentLength, const char *path)
void	WebServer::_handleCgi(std::string method, int contentLength)
{
	int		cgi_input[2], cgi_output[2], status;
	pid_t	pid;
	char	c;

    if (pipe(cgi_input) < 0 || pipe(cgi_output) < 0)
		this->_perrorExit("pipe failed");
    if ((pid = fork()) < 0)
		this->_perrorExit("fork failed");

    if (pid == 0)	// child process
	{
        close(cgi_input[1]);
        close(cgi_output[0]);

        dup2(cgi_input[0], STDIN_FILENO);
        dup2(cgi_output[1], STDOUT_FILENO);

		// setenv("REQUEST_METHOD", method, 1);
        // setenv("SCRIPT_NAME", path, 1);
        // setenv("QUERY_STRING", query_string, 1);
        // setenv("CONTENT_TYPE", content_type, 1);
        setenv("CONTENT_LENGTH", "69", 1);

		char	*cmds[2] = {(char *)(this->_path.c_str() + 1), NULL};
		execve(cmds[0], cmds, NULL);
		std::cerr << "Failed..." << std::endl; 
        exit(EXIT_FAILURE);
    }
	else	// parent process
	{
        close(cgi_input[0]);
        close(cgi_output[1]);

        if (method == "POST")
		{
            int n = read(this->_newSocket, &c, 1);
            int i = 0;
            while (n > 0 && i < contentLength) {
                write(cgi_input[1], &c, 1);
                n = read(this->_newSocket, &c, 1);
                i++;
            }
        }

		std::string	buffer(WS_BUFFER_SIZE, '\0');
        int n = read(cgi_output[0], &buffer[0], WS_BUFFER_SIZE);
        while (n > 0)
		{
            write(this->_newSocket, &buffer[0], n);
            n = read(cgi_output[0], &buffer[0], WS_BUFFER_SIZE);
        }

        close(cgi_input[1]);
        close(cgi_output[0]);

        waitpid(pid, &status, 0);
		close(this->_newSocket);
    }
}

void	WebServer::_serverLoop()
{
	long	valread;

	while(1)
	{
		std::cout << "Port: " << WS_PORT << "\nWaiting for new connection..." << std::endl;
		this->_newSocket = accept(this->_serverFd, NULL, NULL);
		if (this->_newSocket < 0)
			this->_perrorExit("Accept Error");
		std::string	buffer(WS_BUFFER_SIZE, '\0');
		valread = read(this->_newSocket, &buffer[0], WS_BUFFER_SIZE);
		buffer.resize(valread);

		std::string	method, query, contentType;
		int		contentLength = 0;
		std::istringstream	request(buffer);
		
		request >> method >> this->_path;
		if (this->_path == "/favicon.ico") // Ignore favicon
		{
			std::cout << "Fuck you favicon" << std::endl;
			close(this->_newSocket);
			continue;
		}
		std::cout << buffer << std::endl;
		std::cout << "Method: " << method << std::endl;
		std::cout << "Path: " << this->_path << std::endl;
		
		if (method == "POST")
			this->_handlePost(buffer, contentLength, valread);
		else if (method == "GET" && this->_path != "/" && this->_path.find(".php") == std::string::npos && this->_path.find(".py") == std::string::npos && this->_path.find(".cgi") == std::string::npos) // Will be determined by the config
		{
			if (this->_handleGet())
				continue ;
		}
		else if (this->_path.find('.') != std::string::npos)
			this->_handleCgi(method, contentLength);
		else
		{
			std::string hello = "HTTP/1.1 200 OK\nContent-Length: 12\n\nHello World!";
			write(this->_newSocket, hello.c_str(), hello.length());
			printf("Hello message sent\n\n");
			close(this->_newSocket);
		}
	}
}

void	WebServer::runServer()
{
	this->_configManager.parseConfigFile();
	this->_setupServer();
	this->_serverLoop();
}
