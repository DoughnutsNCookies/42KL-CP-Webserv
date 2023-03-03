/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:18:53 by schuah            #+#    #+#             */
/*   Updated: 2023/03/03 10:49:52 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>

class Token
{
	public:
		enum Type
		{
			OPEN_BRACE,
			CLOSE_BRACE,
			SEMICOLON,
			TEXT,
			INVALID
		};
		Token(const std::string &context, Type type, int lineNum);
		~Token();
		std::string	getContext();
		int			getLineNum();
		Type		getType();
	private:
		std::string	_context;
		int			_lineNum;
		Type		_type;
};

#endif
