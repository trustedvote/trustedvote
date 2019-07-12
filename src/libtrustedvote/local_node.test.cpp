#include <trustedvote/local_node.hpp>

#include <boost/test/unit_test.hpp>

#include <utility>

namespace tv = trustedvote;

namespace {
	class test_local_node : public tv::local_node {
	public:
		test_local_node(tv::node_capability caps) : tv::local_node(caps)
		{
		}
	};
}

BOOST_AUTO_TEST_SUITE(local_node)

BOOST_AUTO_TEST_CASE(ctor_with_caps)
{
	test_local_node node(tv::node_capability::seeding);

	BOOST_TEST(node.capabilities() == tv::node_capability::seeding);
}

BOOST_AUTO_TEST_CASE(move_ctor)
{
	test_local_node node1(tv::node_capability::seeding);
	test_local_node node2(std::move(node1));

	BOOST_TEST(node1.capabilities() == tv::node_capability::seeding); // should not reset
	BOOST_TEST(node2.capabilities() == tv::node_capability::seeding);
}

BOOST_AUTO_TEST_SUITE_END()
