#include <trustedvote/node.hpp>

#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>

namespace trustedvote {
	node_capability operator&(node_capability lhs, node_capability rhs)
	{
		auto l = static_cast<typename std::underlying_type_t<node_capability>>(lhs);
		auto r = static_cast<typename std::underlying_type_t<node_capability>>(rhs);

		return static_cast<node_capability>(l & r);
	}

	node_capability operator|(node_capability lhs, node_capability rhs)
	{
		auto l = static_cast<typename std::underlying_type_t<node_capability>>(lhs);
		auto r = static_cast<typename std::underlying_type_t<node_capability>>(rhs);

		return static_cast<node_capability>(l | r);
	}

	node_capability &operator|=(node_capability &lhs, node_capability rhs)
	{
		return lhs = lhs | rhs;
	}

	bool has_seeding(node_capability caps)
	{
		return (caps & node_capability::seeding) == node_capability::seeding;
	}
}

namespace std {
	namespace tv = trustedvote;

	string to_string(tv::node_capability caps)
	{
		stringstream s;

		if (tv::has_seeding(caps)) {
			s << "seeding|";
		}

		auto r = s.str();

		if (!r.empty()) {
			r.resize(r.size() - 1); // remove last pipe
		}

		return r;
	}

	from_chars_result from_chars(char const *first, char const *last, tv::node_capability &value)
	{
		string s(first, last);
		auto caps = tv::node_capability();

		if (s.empty()) {
			goto success;
		}

		for (size_t i = 0, next = 0; i != string::npos; next = i + 1) {
			i = s.find('|', next);
			auto v = (i == string::npos) ? s.substr(next) : s.substr(next, i - next);

			if (v == "seeding") {
				if (tv::has_seeding(caps)) {
					goto invalid;
				}
				caps |= tv::node_capability::seeding;
			} else {
				goto invalid;
			}
		}

	success:
		value = caps;
		return from_chars_result{.ptr = last, .ec = std::errc()};

	invalid:
		return from_chars_result{.ptr = first, .ec = std::errc::invalid_argument};;
	}
}
