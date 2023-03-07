rm -rf srcs/cgi_env.cgi srcs/client srcs/cpptest.cgi srcs/server webserver
gcc client.c -o srcs/client
g++ cpptest.cpp -o srcs/cpptest.cgi
g++ cgi_env.cpp -o srcs/cgi_env.cgi
g++ cgi_post.cpp -o srcs/cgi_post.cgi
g++ -Wall -Wextra -Werror webserver.cpp -o webserver
gcc server.c -o srcs/server