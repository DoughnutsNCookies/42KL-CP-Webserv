/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:49:34 by schuah            #+#    #+#             */
/*   Updated: 2023/03/29 15:54:37 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGMANAGER_HPP
# define CONFIGMANAGER_HPP

# include "Token.hpp"

class ConfigManager
{
	public:
		ConfigManager();
		ConfigManager(std::string configFilePath);
		~ConfigManager();

		ConfigManager		&operator=(const ConfigManager &ref);

		void			parseConfigFile();
		void			printTokens();
		void			configLibrary();

		void			checkImportantCheck(int i);
		bool			checkCompulsories(int i);

		int				checkServerKey(size_t i, int previous, int *braces, int *main_block);
		int				checkLocationKey(size_t i, int previous, int *braces, int *main_block);
		int				checkValue(int i, int previous);
		int				checkSemicolon(int i, int previous);
		int				checkOpenBrace(int i, int previous, int *braces, int main_block);
		int				checkCloseBrace(int i, int previous, int *braces, int *main_block);

		int				locationBlock(size_t i);
		void			errorHandleShit();

		void				printError(std::string str, int i);
		std::vector<Token>	&getToken();

	private:
		void						_lexLine(std::string line, int lineNum);
		void						_createToken(std::string *token, Type *currentType, Type type, std::string c, int lineNum);

		std::string					_configFilePath;
		std::vector<Token>			_tokens;
		std::vector<std::string>	_validStr;
		std::vector<std::string>	_serverVar;
		std::vector<std::string>	_locationVar;

};

#endif
