#include <trustedvote/config.hpp>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <fstream>
#include <ios>
#include <utility>

static trustedvote::config parse_config(boost::property_tree::ptree const &data)
{
	trustedvote::config conf;

	// server binding interfaces
	if (auto ifaces = data.get_child_optional("network.server.interfaces")) {
		for (auto &iface : ifaces.get()) {
			auto value = iface.second.get_value<std::string>();
			conf.network.server.interfaces.emplace_back(std::move(value));
		}
	} else {
		conf.network.server.interfaces.push_back("0.0.0.0");
	}

	if (conf.network.server.interfaces.empty()) {
		throw std::runtime_error("No network interface to bind");
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
