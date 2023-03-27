/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpCgiResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:55:14 by schuah            #+#    #+#             */
/*   Updated: 2023/03/24 23:04:03 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpCgiResponse.hpp"

HttpCgiResponse::HttpCgiResponse(EuleeHand *database) : _database(database) {}

HttpCgiResponse::~HttpCgiResponse() {}

void    HttpCgiResponse::handleCgi()
{
    std::ofstream   inFile(WS_TEMP_FILE_IN, std::ios::binary);
    inFile << this->_database->buffer[this->_database->socket].substr(this->_database->buffer[this->_database->socket].find("\r\n\r\n") + std::strlen("\r\n\r\n"));
    inFile.close();

    pid_t pid = fork();
    if (pid == 0)
    {
        int inFd = open(WS_TEMP_FILE_IN, O_RDONLY, 0777);
		int outFd = open(WS_TEMP_FILE_OUT, O_CREAT | O_TRUNC | O_RDWR, 0777);
        dup2(inFd, STDIN_FILENO);
        close(inFd);
        dup2(outFd, STDOUT_FILENO);
		close(outFd);
        std::string ext = this->_database->methodPath.substr(this->_database->methodPath.find_last_of("."));
        std::cerr << GREEN << "CGI Path: " << this->_database->cgi[ext].c_str() << RESET << std::endl;
        char *args[3] = {(char *)this->_database->cgi[ext].c_str(), (char *)this->_database->methodPath.c_str(), NULL};
        this->_database->addEnv("PATH_INFO=" + this->_database->cgi[ext]);
        execve(args[0], args, this->_database->envp);
        std::remove(WS_TEMP_FILE_IN);
        std::remove(WS_TEMP_FILE_OUT);
        std::cerr << RED << "Execve failed..." << RESET << std::endl;
        exit(1);
    }
    waitpid(pid, NULL, 0);
    std::string output = "";
    int     outfd2 = open(WS_TEMP_FILE_OUT, O_RDWR, 0777);
    char    *buffer = new char[WS_TESTER_SIZE];
    long    bytes_read = 0, total = 0;
    while ((bytes_read = read(outfd2, buffer, WS_TESTER_SIZE)) > 0)
    {
        output.append(buffer, bytes_read);
        total += bytes_read;
    }
    close(outfd2);
    size_t  startPos = output.find("\r\n\r\n") + std::strlen("\r\n\r\n");
    std::string newOutput = output.substr(startPos);

    this->_database->response[this->_database->socket] = "HTTP/1.1 200 OK\r\n\r\n" + newOutput;
    std::cout << GREEN << "CGI ran successfully!" << RESET << std::endl;
    std::remove(WS_TEMP_FILE_IN);
    std::remove(WS_TEMP_FILE_OUT);
}
