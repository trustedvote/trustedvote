#ifndef TRUSTEDVOTE_NODE_HPP
#define TRUSTEDVOTE_NODE_HPP

#include <charconv>
#include <cinttypes>
#include <ostream>
#include <string>
#include <type_traits>

namespace trustedvote {

	enum class node_capability : std::uint32_t {
		seeding	= UINT32_C(0x00000001)
	};

	node_capability operator&(node_capability lhs, node_capability rhs);
	node_capability operator|(node_capability lhs, node_capability rhs);
	node_capability &operator|=(node_capability &lhs, node_capability rhs);

	bool has_seeding(node_capability caps);

}

namespace std {

	string to_string(trustedvote::node_capability caps);
	from_chars_result from_chars(char const *first, char const *last, trustedvote::node_capability &value);

	template<typename Char, typename Traits>
	basic_ostream<Char, Traits> &operator<<(basic_ostream<Char, Traits> &os, trustedvote::node_capability caps)
	{
		return os << to_string(caps);
	}

}

#endif // TRUSTEDVOTE_NODE_HPP
