#include <iostream>

#include <boost/asio.hpp>

void write_data(boost::asio::ip::tcp::socket& socket, const std::string& name)
{
	std::string data;

	do
	{
		std::getline(std::cin, data);

		boost::asio::write(socket, boost::asio::buffer(name + " : " + data + "\n"));

	} while (data != "exit");

	boost::asio::write(socket, boost::asio::buffer("exit\n"));

	std::cout << "write ended\n";
}

void read_data_until(boost::asio::ip::tcp::socket& socket)
{
	while (true)
	{
		boost::asio::streambuf buffer;

		boost::asio::read_until(socket, buffer, '\n');

		std::string message;

		std::istream input_stream(&buffer);

		

		std::getline(input_stream, message, '\n');
		
		if (message != "exit")
			std::cout << message << std::endl;
		else
		{
			std::cout << "read ended\n";
			return;
		}
	}
	
}

int main(int argc, char** argv)
{
	system("chcp 1251");

	std::string raw_ip_address = "93.175.8.189";

	auto port = 8000;

	std::string name;
	std::cout << "Enter your name, client: ";
	std::cin >> name;
	try
	{
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(raw_ip_address), port);

		boost::asio::io_service io_service;

		boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());

		socket.connect(endpoint);

		std::thread t(read_data_until, std::ref(socket));		

		write_data(socket, name);

		t.join();
	}

	catch (boost::system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

		system("pause");

		return e.code().value();
	}

	system("pause");

	return EXIT_SUCCESS;
}