/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:18:53 by schuah            #+#    #+#             */
/*   Updated: 2023/03/03 13:12:46 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>

enum Type
{
    CONTEXT,
    KEY,
    VALUE,
    SEMICOLON,
    OPEN_BRACE,
    CLOSE_BRACE
};

class Token
{
	public:
		Token(std::string context, Type type, int lineNum);
		~Token();
		std::string	getToken();
		int			getLineNum();
		Type		getType();
	private:
		std::string	_token;
		int			_lineNum;
		Type		_type;
};

#endif
