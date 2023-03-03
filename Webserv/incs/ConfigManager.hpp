/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:49:34 by schuah            #+#    #+#             */
/*   Updated: 2023/03/03 10:42:08 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGMANAGER_HPP
# define CONFIGMANAGER_HPP

# include <string>
# include <fstream>

# define ValidTokens "{};"
# define ValidSpaces " \f\n\r\t\v"

class ConfigManager
{
	public:
		ConfigManager();
		ConfigManager(std::string configFilePath);
		ConfigManager	&operator=(const ConfigManager &srcs);
		~ConfigManager();
		int	parseConfigFile();

	private:
		std::ifstream	_file;
		std::string		_configFilePath;
		std::string		_fileBuffer;
};

#endif
