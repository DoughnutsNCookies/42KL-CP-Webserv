/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleeHand.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:12:48 by jhii              #+#    #+#             */
/*   Updated: 2023/03/20 14:26:10 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EULEEHAND_HPP
# define EULEEHAND_HPP

# include "EuleePocket.hpp"
# include "ConfigManager.hpp"

class EuleeHand
{
	public:
		EuleeHand();
		EuleeHand(std::string configFilePath, const ConfigManager &configManager, char **envp);
		~EuleeHand();

		void		printTokens();
		void		parseConfigFile();
		void		configLibrary();
		void		errorHandleShit();
		void		printServers();
		void		parseConfigServer();
		void		perrorExit(std::string msg, int exitTrue = 1);
		long		ft_select(int fd, void *buff, size_t size, Mode mode);
		int			checkPath(std::string path, int	isFile, int isDirectory);

		int			isCGI();
		int			checkExcept();
		int			unchunkResponse();
		void		convertLocation();
		std::string	cgiPath();

		char								**envp;
		std::map<std::string, std::string>	cgi;
		std::vector<EuleePocket>			server;
		std::vector<int>					serverFd;
		std::vector<sockaddr_in>			serverAddr;
		int									socket, serverIndex, useDefaultIndex;
		std::string							method, methodPath, buffer, locationPath;

	private:
		std::string		_configFilePath;
		ConfigManager	_configManager;
		size_t			_parseServer(std::vector<Token> &tokens, size_t i);
		size_t			_parseCgi(std::vector<Token> &tokens, size_t i, EuleeWallet &location, int blockType);
		size_t			_parseLocation(std::vector<Token> &tokens, std::vector<EuleeWallet> &location, size_t i);
		size_t			_parsingHelper(std::vector<Token> &tokens, size_t i, EuleeWallet &location, std::string needle, Key key);
};

#endif
