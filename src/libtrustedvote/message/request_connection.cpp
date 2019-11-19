#include <trustedvote/message/request_connection.hpp>

namespace trustedvote::message {
	bool request_connection::operator==(request_connection const &other) const
	{
		return protocol_version == other.protocol_version;
	}

	bool request_connection::operator!=(request_connection const &other) const
	{
		return !(*this == other);
	}
}
