#include <trustedvote/config.hpp>

#include <boost/test/unit_test.hpp>

#include <filesystem>
#include <fstream>
#include <ios>
#include <ostream>
#include <stdexcept>
#include <string>

namespace tv = trustedvote;

namespace {
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
}

static void create_json(std::filesystem::path const &path, char const *json)
{
	std::ofstream file;

	file.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	file.open(path);

	file << json << std::endl;

	file.close();
}

BOOST_AUTO_TEST_SUITE(config)

BOOST_AUTO_TEST_CASE(load_json_with_non_existent_file)
{
	BOOST_CHECK_THROW(tv::config::load_json("not-exists.json"), std::ios_base::failure);
}

BOOST_FIXTURE_TEST_CASE(load_json_with_empty_file, load_json_file_fixture)
{
	create_json(path, "");

	BOOST_CHECK_THROW(tv::config::load_json(path), std::runtime_error);
}

BOOST_FIXTURE_TEST_CASE(load_json_with_empty_object_file, load_json_file_fixture)
{
	create_json(path, "{}");

	auto conf = tv::config::load_json(path);

	BOOST_TEST(conf.network.server.nodes.size() == 1);
	BOOST_TEST(conf.network.server.nodes[0].address == "0.0.0.0");
	BOOST_TEST(conf.network.server.nodes[0].capabilities == tv::node_capability());
	BOOST_TEST(conf.network.server.port == 3333);
}

BOOST_FIXTURE_TEST_CASE(load_json_with_no_node_address, load_json_file_fixture)
{
	create_json(path, R"(
{
  "network": {
    "server": {
      "nodes": [
		{"address": "::1"},
        {"capabilities": "seeding"}
      ]
    }
  }
})");

	BOOST_CHECK_EXCEPTION(
		tv::config::load_json(path),
		std::runtime_error,
		[](std::runtime_error const &e) { return e.what() == std::string("No 'address' configured for node 1"); }
	);
}

BOOST_FIXTURE_TEST_CASE(load_json_with_invalid_node_capabilities, load_json_file_fixture)
{
	create_json(path, R"(
{
  "network": {
    "server": {
      "nodes": [
		{"address": "::1"},
        {"address": "127.0.0.1", "capabilities": "foo"}
      ]
    }
  }
})");

	BOOST_CHECK_EXCEPTION(
		tv::config::load_json(path),
		std::runtime_error,
		[](std::runtime_error const &e) { return e.what() == std::string("Invalid 'capabilities' for node 1"); }
	);
}

BOOST_FIXTURE_TEST_CASE(load_json_with_empty_nodes, load_json_file_fixture)
{
	create_json(path, R"(
{
  "network": {
    "server": {
      "nodes": []
    }
  }
})");

	BOOST_CHECK_EXCEPTION(
		tv::config::load_json(path),
		std::runtime_error,
		[](std::runtime_error const &e) { return e.what() == std::string("No any local nodes to start"); }
	);
}

BOOST_FIXTURE_TEST_CASE(load_json, load_json_file_fixture)
{
	create_json(path, R"(
{
  "network": {
    "server": {
      "nodes": [
        {"address": "127.0.0.1", "capabilities": "seeding"},
        {"address": "::1"}
      ],
      "port": 7777
    }
  }
})");

	auto conf = trustedvote::config::load_json(path);

	BOOST_TEST(conf.network.server.nodes.size() == 2);

	BOOST_TEST(conf.network.server.nodes[0].address == "127.0.0.1");
	BOOST_TEST(conf.network.server.nodes[0].capabilities == tv::node_capability::seeding);
	BOOST_TEST(conf.network.server.nodes[1].address == "::1");
	BOOST_TEST(conf.network.server.nodes[1].capabilities == tv::node_capability());

	BOOST_TEST(conf.network.server.port == 7777);
}

BOOST_AUTO_TEST_SUITE_END()
