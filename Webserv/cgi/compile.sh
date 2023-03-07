clean="rm -rf srcs/cgi_env.cgi srcs/cpptest.cgi srcs/cgi_post.cgi"

function compile()
{
	g++ cpptest.cpp -o srcs/cpptest.cgi
	g++ cgi_env.cpp -o srcs/cgi_env.cgi
	g++ cgi_post.cpp -o srcs/cgi_post.cgi
}

if [ "$1" == "clean" ]
then
	$clean
elif [ "$1" == "re" ]
then
	$clean
	compile
else
	compile
fi