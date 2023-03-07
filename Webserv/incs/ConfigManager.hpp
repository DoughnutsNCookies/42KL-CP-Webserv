/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:49:34 by schuah            #+#    #+#             */
/*   Updated: 2023/03/03 14:36:12 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGMANAGER_HPP
# define CONFIGMANAGER_HPP

# include <string>
# include <fstream>
# include <vector>
# include <iostream>

# include "Token.hpp"

class ConfigManager
{
	public:
		ConfigManager();
		ConfigManager(std::string configFilePath);
		ConfigManager	&operator=(const ConfigManager &srcs);
		~ConfigManager();
		void			parseConfigFile();

	private:
		void						_lexLine(std::string line, int lineNum);
		void						_createToken(std::string *token, Type *currentType, Type type, std::string c, int lineNum);
		std::string					_configFilePath;
		std::vector<Token>			_tokens;
};

#endif
