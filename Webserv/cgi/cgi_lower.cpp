/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_lower.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:19:35 by schuah            #+#    #+#             */
/*   Updated: 2023/03/30 15:19:15 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ctype.h>
#include <iostream>
#include <string>
#include <unistd.h>

# define WS_BUFFER_SIZE 100000000

int    main(int ac, char **av, char **envp)
{
    char	*buffer = new char[WS_BUFFER_SIZE];
	std::cin.getline(buffer, WS_BUFFER_SIZE);

    for (size_t i = 0; buffer[i]; i++)
        buffer[i] = tolower(buffer[i]);
    // std::cout << "Status: 200 OK\r\n\r\nCGI: " << av[0] << "\nFileInput: " << av[1] << "\n" << buffer << std::endl;
    std::cout << "Status: 200 OK\r\n\r\n";

    std::cout << "Buffer: " << buffer << "\n" << std::endl;

    std::cout << "File gotten: " << av[1] << "\n" << std::endl;

    std::cout << "Envp: " << std::endl; 
    for (size_t i = 0; envp[i]; i++)
        std::cout << envp[i] << std::endl;
    std::cout << std::endl; 

    char *cwd = getcwd(NULL, 0);
    std::cout << "Current working directory: " << cwd << std::endl;
    free(cwd);

    while (1)
        ;

	delete[] buffer;
    return (0);
}
