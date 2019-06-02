#include <trustedvote/config.hpp>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <fstream>
#include <ios>

namespace trustedvote {

	config config::load_json(std::filesystem::path const &path)
	{
		// open json.
		std::ifstream file;

		file.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		file.open(path);

		// read json.
		boost::property_tree::ptree json;
		boost::property_tree::read_json(file, json);

		// construct model
		config conf;

		return conf;
	}

}
