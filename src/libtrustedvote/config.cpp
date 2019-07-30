#include <trustedvote/config.hpp>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <cstddef>
#include <fstream>
#include <ios>
#include <iterator>
#include <string>
#include <utility>

namespace tv = trustedvote;

static tv::node_config parse_node_config(boost::property_tree::ptree const &data, std::size_t num)
{
	auto addr = data.get_optional<std::string>("address");
	auto caps = data.get_optional<std::string>("capabilities");

	if (!addr) {
		throw std::runtime_error("No 'address' configured for node " + std::to_string(num));
	}

	auto node = tv::node_config{.address = addr.get()};

	if (caps) {
		auto r = std::from_chars(
			caps.get().c_str(),
			caps.get().c_str() + caps.get().size(),
			node.capabilities
		);

		if (r.ec != std::errc()) {
			throw std::runtime_error("Invalid 'capabilities' for node " + std::to_string(num));
		}
	}

	return node;
}

static tv::config parse_config(boost::property_tree::ptree const &data)
{
	tv::config conf;

	// server nodes
	if (auto nodes = data.get_child_optional("network.server.nodes"); nodes) {
		for (auto it = nodes.get().begin(); it != nodes.get().end(); it++) {
			auto num = std::distance(nodes.get().begin(), it);
			auto node = parse_node_config(it->second, num);
			conf.network.server.nodes.push_back(std::move(node));
		}
	} else {
		conf.network.server.nodes.push_back(tv::node_config{
			.address = "0.0.0.0"
		});
	}

	if (conf.network.server.nodes.empty()) {
		throw std::runtime_error("No any local nodes to start");
	}

	// server port
	conf.network.server.port = data.get<unsigned short>(
		"network.server.port",
		3333
	);

	return conf;
}

namespace trustedvote {

	std::filesystem::path const config::default_json_file("trustedvote.json");

	config config::load_json(std::filesystem::path const &path)
	{
		// open json.
		std::ifstream file;

		file.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		file.open(path);

		// read json.
		boost::property_tree::ptree json;
		boost::property_tree::read_json(file, json);

		return parse_config(json);
	}

}
