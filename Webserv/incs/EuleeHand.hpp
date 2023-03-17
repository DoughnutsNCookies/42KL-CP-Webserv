/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleeHand.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:12:48 by jhii              #+#    #+#             */
/*   Updated: 2023/03/17 18:41:05 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EULEEHAND_HPP
# define EULEEHAND_HPP

# include "EuleePocket.hpp"
# include "ConfigManager.hpp"

class EuleeHand
{
	public:
		EuleeHand(void);
		EuleeHand(std::string configFilePath, const ConfigManager &configManager);
		~EuleeHand(void);

		void		printTokens(void);
		void		parseConfigFile(void);
		void		configLibrary(void);
		void		errorHandleShit(void);
		void		printServers(void);
		void		parseConfigServer(void);
		void		perrorExit(std::string msg, int exitTrue = 1);
		long		ft_select(int fd, void *buff, size_t size, Mode mode);
		int			checkPath(std::string path, int	isFile, int isDirectory);

		int			isCGI(void);
		int			checkExcept(void);
		int			unchunkResponse(void);
		void		convertLocation(void);
		std::string	cgiPath(void);

		std::map<std::string, std::string>	envp, cgi;
		std::vector<EuleePocket>			server;
		std::vector<int>					serverFd;
		std::vector<sockaddr_in>			serverAddr;
		std::string							method, methodPath, buffer;
		int									socket, serverIndex, useDefaultIndex;

	private:
		std::string		_configFilePath;
		ConfigManager	_configManager;
		size_t			_parseServer(std::vector<Token> &tokens, size_t i);
		size_t			_parseCgi(std::vector<Token> &tokens, size_t i, EuleeWallet &location, int blockType);
		size_t			_parseLocation(std::vector<Token> &tokens, std::vector<EuleeWallet> &location, size_t i);
		size_t			_parsingHelper(std::vector<Token> &tokens, size_t i, EuleeWallet &location, std::string needle, Key key);
};

#endif
