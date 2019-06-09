#include <trustedvote/config.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/system/error_code.hpp>

#include <csignal>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <vector>

static trustedvote::config conf;
static boost::asio::io_context asio;
static std::vector<boost::asio::ip::tcp::acceptor> servers;

static void terminate()
{
	for (auto &server : servers) {
		std::cout << "Stopping server " << server.local_endpoint() << ".";
		std::cout << std::endl;

		server.close();
	}
}

static void on_terminate_signal(const boost::system::error_code& e, int s)
{
	terminate();
}

static void accept_connection(
	boost::system::error_code const &ec,
	boost::asio::ip::tcp::socket s)
{
}

int main(int argc, char *argv[])
{
	// load config
	std::cout << "Loading " << trustedvote::config::default_json_file << ".";
	std::cout << std::endl;

	try {
		conf = trustedvote::config::load_json(
			trustedvote::config::default_json_file
		);
	} catch (std::exception &e) {
		std::cout << "Failed to load ";
		std::cout << trustedvote::config::default_json_file << ": " << e.what();
		std::cout << std::endl;
		return EXIT_FAILURE;
	}

	// start servers.
	for (auto &iface : conf.network.server.interfaces) {
		boost::asio::ip::tcp::endpoint addr;

		addr.address(boost::asio::ip::make_address(iface));
		addr.port(conf.network.server.port);

		std::cout << "Starting server " << addr << "." << std::endl;

		servers.emplace_back(asio, addr).async_accept(accept_connection);
	}

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
