/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:49:34 by schuah            #+#    #+#             */
/*   Updated: 2023/03/07 16:34:15 by jhii             ###   ########.fr       */
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
		ConfigManager(void);
		ConfigManager(std::string configFilePath);
		~ConfigManager(void);

		ConfigManager	&operator=(const ConfigManager &ref);

		void			parseConfigFile(void);
		void			printTokens(void);
		void			configLibrary(void);
		void			errorHandleShit(void);

		// Utils
		void			printError(std::string str, int i);

	private:
		std::vector<Token>			_tokens;
		std::string					_configFilePath;
		std::vector<std::string>	_validStr;

		void				_lexLine(std::string line, int lineNum);
		void				_createToken(std::string *token, Type *currentType, Type type, std::string c, int lineNum);
};

#endif
