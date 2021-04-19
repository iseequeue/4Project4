#include <iostream>

#include <boost/asio.hpp>

void write_data(boost::asio::ip::tcp::socket& socket)
{
	std::string data;

	do
	{
		std::getline(std::cin, data);
		boost::asio::write(socket, boost::asio::buffer(data + "\n"));

	} while (data != "exit");
	std::cout << "write ended\n";
}

void read_data_until(boost::asio::ip::tcp::socket& socket, const std::string &name)
{
	while (true)
	{
		boost::asio::streambuf buffer;

		boost::asio::read_until(socket, buffer, '\n');

		std::string message;

		std::istream input_stream(&buffer);
		std::getline(input_stream, message, '\n');

		if (message != "exit")
			std::cout << name << ": " << message << std::endl;
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
	std::string name;
	std::cout << "Enter your name: \n";
	std::cin >> name;
	const std::size_t size = 30;

	auto port = 8000;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);

	boost::asio::io_service io_service;
	

	try
	{
		boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());

		acceptor.bind(endpoint);

		acceptor.listen(size);

		boost::asio::ip::tcp::socket socket(io_service);

		acceptor.accept(socket);
			
		std::thread t(read_data_until, std::ref(socket), std::ref(name));
		write_data(socket);
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