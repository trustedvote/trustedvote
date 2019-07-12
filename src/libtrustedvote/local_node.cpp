#include <trustedvote/local_node.hpp>

namespace trustedvote {

	local_node::local_node(node_capability caps) : caps(caps)
	{
	}

	local_node::local_node(local_node &&other) : caps(other.caps)
	{
	}

	local_node::~local_node()
	{
	}

}
