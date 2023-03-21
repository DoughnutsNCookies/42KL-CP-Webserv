/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_toupper.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:19:35 by schuah            #+#    #+#             */
/*   Updated: 2023/03/21 14:37:42 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ctype.h>
#include <iostream>
#include <string>
#include <unistd.h>

# define WS_BUFFER_SIZE 100000000

int    main(void)
{
    char	*buffer = new char[WS_BUFFER_SIZE];
	std::cin.getline(buffer, WS_BUFFER_SIZE);

    for (size_t i = 0; buffer[i]; i++)
        buffer[i] = toupper(buffer[i]);
    std::cout << buffer;

	delete[] buffer;
    return (0);
}
