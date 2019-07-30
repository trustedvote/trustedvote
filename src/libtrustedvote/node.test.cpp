#include <trustedvote/node.hpp>

#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

namespace tv = trustedvote;

BOOST_AUTO_TEST_SUITE(node_capability)

BOOST_AUTO_TEST_CASE(operator_and)
{
	auto caps = tv::node_capability::seeding;

	BOOST_TEST((caps & tv::node_capability::seeding) == tv::node_capability::seeding);
}

BOOST_AUTO_TEST_CASE(operator_or)
{
	auto caps = tv::node_capability() | tv::node_capability::seeding;

	BOOST_TEST(caps == tv::node_capability::seeding);
}

BOOST_AUTO_TEST_CASE(operator_or_assigment)
{
	auto caps = tv::node_capability();

	caps |= tv::node_capability::seeding;

	BOOST_TEST(caps == tv::node_capability::seeding);

	// test if operator return a reference
	(caps |= tv::node_capability::seeding) = tv::node_capability();

	BOOST_TEST(caps == tv::node_capability());
}

BOOST_AUTO_TEST_CASE(has_seeding)
{
	tv::node_capability caps;

	caps = tv::node_capability();

	BOOST_TEST(tv::has_seeding(caps) == false);

	caps = tv::node_capability::seeding;

	BOOST_TEST(tv::has_seeding(caps) == true);
}

BOOST_AUTO_TEST_CASE(to_string)
{
	tv::node_capability caps;

	caps = tv::node_capability();

	BOOST_TEST(std::to_string(caps) == "");

	caps = tv::node_capability::seeding;

	BOOST_TEST(std::to_string(caps) == "seeding");
}

BOOST_AUTO_TEST_CASE(from_chars)
{
	std::string s;
	tv::node_capability v;
	std::from_chars_result r;

	// empty
	s = "";
	v = tv::node_capability::seeding;
	r = std::from_chars(s.c_str(), s.c_str() + s.size(), v);

	BOOST_TEST(r.ptr == s.c_str() + s.size());
	BOOST_TEST((r.ec == std::errc()));
	BOOST_TEST(v == tv::node_capability());

	// single value
	s = "seeding";
	v = tv::node_capability();
	r = std::from_chars(s.c_str(), s.c_str() + s.size(), v);

	BOOST_TEST(r.ptr == s.c_str() + s.size());
	BOOST_TEST((r.ec == std::errc()));
	BOOST_TEST(v == tv::node_capability::seeding);

	// duplicate value
	s = "seeding|seeding";
	v = tv::node_capability();
	r = std::from_chars(s.c_str(), s.c_str() + s.size(), v);

	BOOST_TEST(r.ptr == s.c_str());
	BOOST_TEST((r.ec == std::errc::invalid_argument));
	BOOST_TEST(v == tv::node_capability()); // v should not modified

	// invalid
	s = "seeding|foo";
	v = tv::node_capability();
	r = std::from_chars(s.c_str(), s.c_str() + s.size(), v);

	BOOST_TEST(r.ptr == s.c_str());
	BOOST_TEST((r.ec == std::errc::invalid_argument));
	BOOST_TEST(v == tv::node_capability()); // v should not modified
}

BOOST_AUTO_TEST_CASE(stream_input)
{
	auto caps = tv::node_capability::seeding;
	std::stringstream stream;

	stream << "caps: " << caps << ".";

	BOOST_TEST(stream.str() == "caps: seeding.");
}

BOOST_AUTO_TEST_SUITE_END()
