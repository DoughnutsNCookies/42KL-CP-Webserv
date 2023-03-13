/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:49:34 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 20:11:59 by jhii             ###   ########.fr       */
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

		ConfigManager		&operator=(const ConfigManager &ref);

		void			parseConfigFile(void);
		void			printTokens(void);
		void			configLibrary(void);

		void			checkImportantCheck(int i);

		int				checkServerKey(size_t i, int previous, int *braces, int *main_block);
		int				checkLocationKey(size_t i, int previous, int *braces, int *main_block);
		int				checkValue(int i, int previous);
		int				checkSemicolon(int i, int previous);
		int				checkOpenBrace(int i, int previous, int *braces, int main_block);
		int				checkCloseBrace(int i, int previous, int *braces, int *main_block);

		int				locationBlock(size_t *i);
		void			errorHandleShit(void);

		// Utils
		void				printError(std::string str, int i);
		std::vector<Token>	&getToken(void);

	private:
		std::string					_configFilePath;
		std::vector<Token>			_tokens;
		std::vector<std::string>	_validStr;
		std::vector<std::string>	_serverVar;
		std::vector<std::string>	_locationVar;

		void						_lexLine(std::string line, int lineNum);
		void						_createToken(std::string *token, Type *currentType, Type type, std::string c, int lineNum);
};

#endif
