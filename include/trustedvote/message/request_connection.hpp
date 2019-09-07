#ifndef TRUSTEDVOTE_MESSAGE_REQUEST_CONNECTION_HPP
#define TRUSTEDVOTE_MESSAGE_REQUEST_CONNECTION_HPP

#include <cinttypes>
#include <ostream>

namespace trustedvote::message {
	struct request_connection {
		std::uint32_t protocol_version;

		bool operator==(request_connection const &other) const;
		bool operator!=(request_connection const &other) const;
	};
}

namespace std {
	namespace tv = trustedvote;

	template<typename Char, typename Traits>
	basic_ostream<Char, Traits>& operator<<(basic_ostream<Char, Traits>& os, tv::message::request_connection const &m)
	{
		return os << "{protocol_version: " << m.protocol_version << "}";
	}
}

#endif // TRUSTEDVOTE_MESSAGE_REQUEST_CONNECTION_HPP
