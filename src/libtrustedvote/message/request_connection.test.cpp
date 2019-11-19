#include <trustedvote/message/request_connection.hpp>

#include <boost/test/unit_test.hpp>

namespace tv = trustedvote;

namespace {
	struct comparison_fixture {
		tv::message::request_connection a, b;
	};
}

BOOST_FIXTURE_TEST_SUITE(message_request_connection, comparison_fixture)

BOOST_AUTO_TEST_CASE(equality)
{
	a.protocol_version = 5;
	b.protocol_version = 5;

	BOOST_CHECK_EQUAL(a, b);
}

BOOST_AUTO_TEST_CASE(inequality)
{
	a.protocol_version = 5;
	b.protocol_version = 6;

	BOOST_CHECK_NE(a, b);
}

BOOST_AUTO_TEST_SUITE_END()
