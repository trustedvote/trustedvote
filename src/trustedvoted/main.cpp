#include "local_node.hpp"
#include "options.hpp"

#include <trustedvote/config.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/program_options.hpp>
#include <boost/system/error_code.hpp>

#include <csignal>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <vector>

namespace tv = trustedvote;

static options opts;
static tv::config conf;
static boost::asio::io_context asio;
static std::vector<local_node> servers; // this must come after asio

static void terminate()
{
	for (auto &server : servers) {
		std::cout << "Stopping server " << server.endpoint() << ".";
		std::cout << std::endl;

		server.stop();
	}
}

static void on_terminate_signal(boost::system::error_code const &e, int s)
{
	terminate();
}

static bool parse_arguments(int argc, char *argv[])
{
	// setup available options
	boost::program_options::options_description desc("Available options");

	desc.add_options()
		("help,h", "show this help")
	;

	// parse
	boost::program_options::variables_map parsed;

	boost::program_options::store(
		boost::program_options::parse_command_line(argc, argv, desc),
		parsed
	);

	boost::program_options::notify(parsed);

	if (parsed.count("help")) {
		std::cout << "Usage: " << argv[0] << " [OPTION]..." << std::endl;
		std::cout << std::endl;
		std::cout << desc;
		return false;
	}

	return true;
}

int main(int argc, char *argv[])
{
	// parse arguments
	try {
		if (!parse_arguments(argc, argv)) {
			return EXIT_SUCCESS;
		}
	} catch (std::exception &e) {
		std::cerr << e.what() << "." << std::endl;
		return EXIT_FAILURE;
	}

	// load config
	std::cout << "Loading " << tv::config::default_json_file << "." << std::endl;

	try {
		conf = tv::config::load_json(tv::config::default_json_file);
	} catch (std::exception &e) {
		std::cout << "Failed to load ";
		std::cout << tv::config::default_json_file << ": " << e.what();
		std::cout << "." << std::endl;
		return EXIT_FAILURE;
	}

	// start nodes
	for (auto &node : conf.network.server.nodes) {
		boost::asio::ip::tcp::endpoint addr;

		addr.address(boost::asio::ip::make_address(node.address));
		addr.port(conf.network.server.port);

		std::cout << "Starting node " << addr;

		if (auto caps = node.capabilities; caps != tv::node_capability()) {
			std::cout << " with capabilities " << std::to_string(caps) << "." << std::endl;
		} else {
			std::cout << "." << std::endl;
		}

		servers.emplace_back(node.capabilities, asio).start(addr);
	}

	// setup signal handling
	boost::asio::signal_set sigs(asio);

	sigs.add(SIGINT);
	sigs.add(SIGTERM);

	sigs.async_wait(on_terminate_signal);

	// enter event loop
	std::cout << "Ready." << std::endl;

	try {
		asio.run();
	} catch (std::exception& e) {
		std::cerr << e.what() << "." << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
