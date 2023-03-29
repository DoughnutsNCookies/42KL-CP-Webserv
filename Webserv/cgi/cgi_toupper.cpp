/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_toupper.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:19:35 by schuah            #+#    #+#             */
/*   Updated: 2023/03/29 15:54:37 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ctype.h>
#include <iostream>
#include <string>
#include <unistd.h>

# define WS_BUFFER_SIZE 100000000

int    main()
{
    char	*buffer = new char[WS_BUFFER_SIZE];
	std::cin.getline(buffer, WS_BUFFER_SIZE);

    for (size_t i = 0; buffer[i]; i++)
        buffer[i] = toupper(buffer[i]);
    std::cout << buffer;

	delete[] buffer;
    return (0);
}
