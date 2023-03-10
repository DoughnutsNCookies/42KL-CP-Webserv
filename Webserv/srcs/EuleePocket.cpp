/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleePocket.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:51:53 by jhii              #+#    #+#             */
/*   Updated: 2023/03/10 16:28:14 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EuleePocket.hpp"

EuleePocket::EuleePocket(void) : envp(), location(), port(), root(), index(), domain(), autoIndex(), uploadSize(), errorPath(), serverFd(), serverAddr(), path(), method(), buffer(), socket(), contentLength(), valread() {}

EuleePocket::EuleePocket(std::string port, std::string root, std::string index, std::string domain, std::string autoIndex, std::string uploadSize, std::string errorPath) : envp(), location(), port(), root(), index(), domain(), autoIndex(), uploadSize(), errorPath(), serverFd(), serverAddr(), path(), method(), buffer(), socket(), contentLength(), valread()
{
	this->port = port;
	this->root = root;
	this->index = index;
	this->domain = domain;
	this->autoIndex = autoIndex;
	this->uploadSize = uploadSize;
	this->errorPath = errorPath;
}

EuleePocket::~EuleePocket(void) {}

void	EuleePocket::perrorExit(std::string msg, int exitTrue)
{
	std::cerr << RED << msg << ": ";
	perror("");
	std::cerr << RESET;
	if (exitTrue)
		exit(EXIT_FAILURE);
}

long	EuleePocket::ft_select(int fd, void *buff, size_t size, Mode mode)
{
	fd_set	read_fds, write_fds;
	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
	FD_SET(fd, (mode == READ) ? &read_fds : &write_fds);

	timeval	timeout;
	timeout.tv_sec = WS_TIMEOUT;
	timeout.tv_usec = 0;

	int	num_ready = select(fd + 1, &read_fds, &write_fds, NULL, &timeout);
	if (num_ready == -1)
	{
		this->perrorExit("Select Error", 0);
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
		val = read(fd, buff, size);
		if (val == -1)
			this->perrorExit("Read Error", 0);
	}
	else if (FD_ISSET(fd, &write_fds) && mode == WRITE)
	{
		val = write(fd, buff, size);
		if (val == -1)
			this->perrorExit("Write Error", 0);
	}
	return (val);
}
