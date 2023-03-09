/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleeHand.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:12:48 by jhii              #+#    #+#             */
/*   Updated: 2023/03/09 12:26:11 by jhii             ###   ########.fr       */
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
		void	errorHandleShit(void);
		void	configLibrary(void);
		


		std::vector<EuleePocket>	block;

	private:
		std::string					_configFilePath;
		ConfigManager				_configManager;
};

#endif
