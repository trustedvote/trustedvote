#include <trustedvote/config.hpp>

#include <boost/test/unit_test.hpp>

#include <filesystem>
#include <fstream>
#include <ios>
#include <ostream>
#include <stdexcept>

struct load_json_file_fixture {
	std::filesystem::path path;

	load_json_file_fixture() {
		auto name = "libtrustedvote-test-config.json";
		path = std::filesystem::temp_directory_path() / name;
	}

	~load_json_file_fixture() {
		std::filesystem::remove(path);
	}
};

BOOST_AUTO_TEST_SUITE(config)

BOOST_AUTO_TEST_CASE(load_json_with_non_existent_file)
{
	BOOST_CHECK_THROW(
		trustedvote::config::load_json("not-exists.json"),
		std::ios_base::failure
	);
}

BOOST_FIXTURE_TEST_CASE(load_json_with_empty_file, load_json_file_fixture)
{
	// create json
	std::ofstream file;

	file.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	file.open(path);

	file << std::endl;

	file.close();

	// load json
	BOOST_CHECK_THROW(
		trustedvote::config::load_json(path),
		std::runtime_error
	);
}

BOOST_FIXTURE_TEST_CASE(
	load_json_with_empty_object_file,
	load_json_file_fixture)
{
	// create json
	std::ofstream file;

	file.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	file.open(path);

	file << "{}" << std::endl;

	file.close();

	// load json
	trustedvote::config::load_json(path);
}

BOOST_AUTO_TEST_SUITE_END()
