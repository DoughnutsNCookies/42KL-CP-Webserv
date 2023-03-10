/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleePocket.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:51:51 by jhii              #+#    #+#             */
/*   Updated: 2023/03/10 16:23:25 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EULEEPOCKET_HPP
# define EULEEPOCKET_HPP

# include <map>
# include <vector>
# include <unistd.h>
# include <sys/select.h>
# include <netinet/in.h>
# include "EuleeWallet.hpp"

# define RESET		"\033[0m"
# define RED		"\033[1;31m"
# define WS_TIMEOUT	3

enum	Mode
{
	READ,
	WRITE
};

// server block
struct EuleePocket
{
	EuleePocket(void);
	EuleePocket(std::string port, std::string root, std::string index, std::string domain, std::string autoIndex, std::string uploadSize, std::string errorPath);
	~EuleePocket(void);

	// member variables
	std::map<std::string, std::string>	envp;
	std::vector<EuleeWallet>			location;
	std::string							port, root, index, domain;
	std::string							autoIndex, uploadSize, errorPath;

	std::vector<int>					serverFd;
	std::vector<sockaddr_in>			serverAddr;
	std::string							path, method, buffer;
	int									socket, contentLength, valread;

	// member functions
	void	perrorExit(std::string msg, int exitTrue = 1);
	long	ft_select(int fd, void *buff, size_t size, Mode mode);
};

#endif
