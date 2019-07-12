#ifndef TRUSTEDVOTE_LOCAL_NODE_HPP
#define TRUSTEDVOTE_LOCAL_NODE_HPP

#include "node.hpp"

namespace trustedvote {

	class local_node {
	public:
		local_node(local_node const &) = delete;
		virtual ~local_node();

		local_node &operator=(local_node const &) = delete;

		node_capability capabilities() const noexcept { return caps; }

	protected:
		local_node(node_capability caps);
		local_node(local_node &&other);

	private:
		node_capability caps;
	};

}

#endif // TRUSTEDVOTE_LOCAL_NODE_HPP
