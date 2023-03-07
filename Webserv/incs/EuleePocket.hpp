/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleePocket.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:12:48 by jhii              #+#    #+#             */
/*   Updated: 2023/03/07 16:46:54 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EULEEPOCKET_HPP
# define EULEEPOCKET_HPP

# include <iostream>
# include "ConfigManager.hpp"

class EuleePocket
{
	public:
		EuleePocket(void);
		EuleePocket(std::string configFilePath, const ConfigManager &configManager);
		EuleePocket(const EuleePocket &ref);
		~EuleePocket(void);

		EuleePocket	&operator=(const EuleePocket &ref);

		void	printData(void);
		void	parseConfigFile(void);

	private:
		std::string		_configFilePath;
		ConfigManager	_configManager;
};

#endif
