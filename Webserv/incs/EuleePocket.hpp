/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleePocket.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:51:51 by jhii              #+#    #+#             */
/*   Updated: 2023/03/10 19:26:36 by jhii             ###   ########.fr       */
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
# define BLUE		"\033[1;34m"
# define CYAN		"\033[1;36m"
# define BLUENORM	"\033[34m"
# define CYANNORM	"\033[36m"
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
	EuleePocket(std::string port, std::string root, std::string index, std::string domain, std::string autoIndex, std::string uploadSize, std::string errorPath, std::vector<EuleeWallet> location = std::vector<EuleeWallet>());
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
