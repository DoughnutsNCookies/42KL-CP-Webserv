/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_chunk.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:50:26 by schuah            #+#    #+#             */
/*   Updated: 2023/03/11 18:03:55 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
	cout << "HTTP /1.1 200 OK\n";
    cout << "Content-Type: text/plain\r\n";
    cout << "Transfer-Encoding: chunked\r\n\r\n";

    string message = "Hello world from the outside world";
    int size = message.size();

    cout << hex << size << "\r\n";
    cout << message << "\r\n";

    cout << "0\r\n\r\n";
    return (0);
}

// echo -e "POST /cgi/srcs/cgi_post.cgi HTTP/1.1\r\nTransfer-Encoding: chunked\r\n\r\n"
// ------WebKitFormBoundaryT7yEfNmKcB0Jvuyl
// Content-Disposition: form-data; name="outfile"; filename="smallest"
// Content-Type: application/octet-stream

// 1234567890
// ------WebKitFormBoundaryT7yEfNmKcB0Jvuyl--"

// echo -e "GET / HTTP/1.1\r\nTransfer-Encoding: chunked\r\n\r\nC\r\nHello world\n\r\n0\r\n\r\n" | nc localhost 8080