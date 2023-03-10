/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpCgiResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:55:14 by schuah            #+#    #+#             */
/*   Updated: 2023/03/14 15:24:33 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpCgiResponse.hpp"

HttpCgiResponse::HttpCgiResponse(EuleeHand database) : _database(database) {}

HttpCgiResponse::~HttpCgiResponse() {}

void	HttpCgiResponse::handleCgi()
{
	int		cgiInput[2], cgiOutput[2], status;
	pid_t	pid;

    if (pipe(cgiInput) < 0 || pipe(cgiOutput) < 0)
        this->_database.perrorExit("Pipe Error");
    if ((pid = fork()) < 0)
        this->_database.perrorExit("Fork Error");

    if (pid == 0)	// child process
	{
        close(cgiInput[1]);
        close(cgiOutput[0]);

        dup2(cgiInput[0], STDIN_FILENO);
        dup2(cgiOutput[1], STDOUT_FILENO);

		// setenv("REQUEST_METHOD", method, 1);
        // setenv("SCRIPT_NAME", path, 1);
        // setenv("QUERY_STRING", query_string, 1);
        // setenv("CONTENT_TYPE", content_type, 1);
        // setenv("CONTENT_LENGTH", std::to_string(contentLength.c_str(), 1);
		setenv("CONTENT_LENGTH", "69", 1);

		char	*cmds[2] = {(char *)(this->_database.methodPath.c_str() + 1), NULL};
		execve(cmds[0], cmds, NULL);
		std::cerr << RED << "Failed to execve CGI: " << strerror(errno) << RESET << std::endl;
        std::cout << "HTTP/1.1 404 Not Found\r\n\r\nCGI requested is not found...\r\n" << std::endl;
        exit(EXIT_FAILURE);
    }
	else	// parent process
	{
        close(cgiInput[0]);
        close(cgiOutput[1]);

		std::string	buffer(WS_BUFFER_SIZE, '\0');
        int n = read(cgiOutput[0], &buffer[0], WS_BUFFER_SIZE);
        while (n > 0)
		{
			this->_database.ft_select(this->_database.socket, &buffer[0], n, WRITE);
			n = read(cgiOutput[0], &buffer[0], WS_BUFFER_SIZE);
        }

        close(cgiInput[1]);
        close(cgiOutput[0]);
        waitpid(pid, &status, 0);
		close(this->_database.socket);
    }
}
