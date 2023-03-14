/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:18:53 by schuah            #+#    #+#             */
/*   Updated: 2023/03/10 17:37:32 by jhii             ###   ########.fr       */
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

struct Token
{
	Token(std::string context, Type type, int lineNum);
	~Token(void);

	Type		type;
	std::string	token;
	int			lineNum;
};

#endif
