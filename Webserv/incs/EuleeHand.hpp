/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleeHand.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:12:48 by jhii              #+#    #+#             */
/*   Updated: 2023/03/13 20:02:43 by jhii             ###   ########.fr       */
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
		EuleeHand(const EuleeHand &ref);
		~EuleeHand(void);

		EuleeHand	&operator=(const EuleeHand &ref);

		void	printTokens(void);
		void	parseConfigFile(void);
		void	configLibrary(void);
		void	errorHandleShit(void);
		void	printServers(void);
		void	parseConfigServer(void);

		std::vector<EuleePocket>	server;

	private:
		std::string		_configFilePath;
		ConfigManager	_configManager;
		size_t			_parseServer(std::vector<Token> &tokens, size_t i);
		size_t			_parseLocation(std::vector<Token> &tokens, std::vector<EuleeWallet> &location, size_t i);
		size_t			_parsingHelper(std::vector<Token> &tokens, size_t i, EuleeWallet &location, std::string needle, Key key);
};

#endif
