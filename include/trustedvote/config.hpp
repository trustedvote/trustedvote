#ifndef TRUSTEDVOTE_CONFIG_HPP
#define TRUSTEDVOTE_CONFIG_HPP

#include "node.hpp"

#include <filesystem>
#include <string>
#include <vector>

namespace trustedvote {

	struct node_config {
		std::string address;
		node_capability capabilities;
	};

	struct server_config {
		std::vector<node_config> nodes;
		unsigned short port;
	};

	struct network_config {
		server_config server;
	};

	class config final {
	public:
		static std::filesystem::path const default_json_file;

	public:
		network_config network;

	public:
		static config load_json(std::filesystem::path const &path);
	};

}

#endif // TRUSTEDVOTE_CONFIG_HPP
