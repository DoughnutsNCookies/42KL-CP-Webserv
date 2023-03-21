/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_toupper.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:19:35 by schuah            #+#    #+#             */
/*   Updated: 2023/03/20 22:30:32 by schuah           ###   ########.fr       */
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
    // char    buffer[30000000];

    // std::string buffer(10000000, '\0');
    std::string buffer(WS_BUFFER_SIZE, '\0');
    // buffer.resize(1000000);
    read(STDIN_FILENO, &buffer[0], WS_BUFFER_SIZE);
    // std::cerr << "Buffer: " << buffer <<std::endl;

    for (size_t i = 0; buffer[i]; i++)
        buffer[i] = toupper(buffer[i]);
    std::cout << buffer;
}
