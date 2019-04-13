#include <boost/asio/io_context.hpp>
#include <boost/asio/signal_set.hpp>

#include <csignal>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>

static boost::asio::io_context asio;

static void terminate()
{
	std::cout << "Terminating..." << std::endl;
}

static void on_terminate_signal(const boost::system::error_code& e, int s)
{
	terminate();
}

int main(int argc, char *argv[])
{
	std::cout << "Initializing..." << std::endl;

	// setup signal handling
	boost::asio::signal_set sigs(asio);

	sigs.add(SIGINT);
	sigs.add(SIGTERM);

	sigs.async_wait(on_terminate_signal);

	// enter event loop
	std::cout << "Ready" << std::endl;

	try {
		asio.run();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
