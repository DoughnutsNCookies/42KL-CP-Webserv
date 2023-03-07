/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:18:53 by schuah            #+#    #+#             */
/*   Updated: 2023/03/07 16:31:43 by jhii             ###   ########.fr       */
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
		~Token(void);

		Type		getType(void);
		std::string	getToken(void);
		int			getLineNum(void);

	private:
		Type		_type;
		std::string	_token;
		int			_lineNum;
};

#endif
