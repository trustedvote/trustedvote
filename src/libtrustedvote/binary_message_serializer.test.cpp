#include <trustedvote/binary_message_serializer.hpp>

#include <boost/test/unit_test.hpp>

#include <sstream>

namespace tv = trustedvote;

namespace {
	struct serializer_fixture {
		tv::binary_message_serializer s;
		std::stringstream b;
	};
}

BOOST_FIXTURE_TEST_SUITE(binary_message_serializer, serializer_fixture)

BOOST_AUTO_TEST_CASE(request_connection)
{
	tv::message::request_connection i, o;

	i.protocol_version = 9;

	s.serialize(b, i);
	s.deserialize(b, o);

	BOOST_CHECK_EQUAL(o, i);
}

BOOST_AUTO_TEST_SUITE_END()
