/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpCgiResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:55:14 by schuah            #+#    #+#             */
/*   Updated: 2023/03/28 19:32:43 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpCgiResponse.hpp"

HttpCgiResponse::HttpCgiResponse(EuleeHand *database) : _database(database) {}

HttpCgiResponse::~HttpCgiResponse() {}

void    HttpCgiResponse::handleCgi()
{
	std::cout << "CGI Socket[" << this->_database->socket << "] size: " << this->_database->buffer[this->_database->socket].size() << std::endl;
	static int count = 0;
	std::string		inFileName = WS_TEMP_FILE_IN + std::to_string(count);
	std::string		outFileName = WS_TEMP_FILE_OUT + std::to_string(count);
	std::cout << this->_database->buffer[this->_database->socket].find("\r\n\r\n") << std::endl;
	std::string		toWrite = this->_database->buffer[this->_database->socket].substr(this->_database->buffer[this->_database->socket].find("\r\n\r\n") + std::strlen("\r\n\r\n"));
	std::remove(inFileName.c_str());
	int tempFd = open(inFileName.c_str(), O_CREAT | O_TRUNC | O_RDWR, 0777);
	
	std::cerr << "Writing size: " << toWrite.size() << std::endl;
	std::cerr << "Wrote: " << write(tempFd, toWrite.c_str(), toWrite.size()) << std::endl;
	close(tempFd);

	std::string ext = this->_database->methodPath[this->_database->socket].substr(this->_database->methodPath[this->_database->socket].find_last_of("."));
	this->_database->clearEnv();
	this->_database->addEnv("HTTP_X_SECRET_HEADER_FOR_TEST=1");
	this->_database->addEnv("REDIRECT_STATUS=200");
	this->_database->addEnv("CONTENT_LENGTH=" + std::to_string(toWrite.size()));
	this->_database->addEnv("CONTENT_TYPE=*/*");
	this->_database->addEnv("GATEWAY_INTERFACE=CGI/1.1");
	this->_database->addEnv("PATH_INFO=" + this->_database->cgi[ext]);
	this->_database->addEnv("PATH_TRANSLATED=" + this->_database->cgi[ext]);
	this->_database->addEnv("QUERY_STRING=");
	this->_database->addEnv("REMOTE_ADDR=127.0.0.1");
	this->_database->addEnv("REQUEST_URI=" + this->_database->cgi[ext]);
	this->_database->addEnv("REQUEST_METHOD=" + this->_database->method[this->_database->socket]);
	this->_database->addEnv("SCRIPT_NAME=" + this->_database->cgi[ext]);
	this->_database->addEnv("SERVER_PROTOCOL=HTTP/1.1");
	this->_database->addEnv("SERVER_SOFTWARE=webserv");
	this->_database->addEnv("SERVER_PORT=" + this->_database->server[this->_database->serverIndex[this->_database->socket]][LISTEN][this->_database->server[this->_database->serverIndex[this->_database->socket]].portIndex]);

	for (size_t i = 0; this->_database->envp[i]; i++)
		std::cerr << "Envp: " << this->_database->envp[i] << std::endl;
	std::cout << GREEN << "CGI Path: " << this->_database->cgi[ext].c_str() << RESET << std::endl;
	std::cerr << "Socket: " << this->_database->socket << std::endl;

	std::remove(outFileName.c_str());
	int	stdinFd = dup(STDIN_FILENO);
	int	stdoutFd = dup(STDOUT_FILENO);
	pid_t pid = fork();
	if (pid == 0)
	{
		int inFd = open(inFileName.c_str(), O_RDONLY, 0777);
		int outFd = open(outFileName.c_str(), O_CREAT | O_TRUNC | O_RDWR, 0777);
		std::cerr << "DUP1 IN return: " << dup2(inFd, STDIN_FILENO) << std::endl;
		close(inFd);
		std::cerr << "DUP2 OUT return: " << dup2(outFd, STDOUT_FILENO) << std::endl;
		close(outFd);
		char *args[3] = {(char *)this->_database->cgi[ext].c_str(), (char *)this->_database->methodPath[this->_database->socket].c_str(), NULL};
		execve(args[0], args, this->_database->envp);
		std::remove(inFileName.c_str());
		std::remove(outFileName.c_str());
		std::cerr << RED << "Execve failed..." << RESET << std::endl;
		exit(1);
	}
	int status;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) == 0)
		std::cerr << RED << "CGI exited abnormally" << RESET << std::endl;
	std::string output = "";
	int     outfd2 = open(outFileName.c_str(), O_RDWR, 0777);
	char    *buffer = new char[WS_BUFFER_SIZE + 1];
	std::memset(buffer, 0, WS_BUFFER_SIZE + 1);
	long    bytesRead = 0, total = 0;
	while ((bytesRead = read(outfd2, buffer, WS_BUFFER_SIZE)) > 0)
	{
		output.append(buffer, bytesRead);
		std::memset(buffer, 0, WS_BUFFER_SIZE + 1);
		total += bytesRead;
	}
	std::cerr << "Output size: " << total << " Actual: " << output.length() << std::endl;
	close(outfd2);
	size_t  startPos = output.find("\r\n\r\n") + std::strlen("\r\n\r\n");
	std::cout << "startPos: " << startPos << std::endl;
	std::string newOutput = output.substr(startPos);

	this->_database->response[this->_database->socket] = "HTTP/1.1 200 OK\r\n\r\n" + newOutput;
	std::cout << GREEN << "CGI ran successfully!" << RESET << std::endl;
	std::remove(inFileName.c_str());
	std::remove(outFileName.c_str());
	dup2(stdinFd, STDIN_FILENO);
	close(stdinFd);
	dup2(stdoutFd, STDOUT_FILENO);
	close(stdoutFd);
	std::cerr << count << ": Socket: " << this->_database->socket << " done" << std::endl;
	count++;
}
