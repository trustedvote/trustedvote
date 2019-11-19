#ifndef TRUSTEDVOTE_BINARY_MESSAGE_SERIALIZER_HPP
#define TRUSTEDVOTE_BINARY_MESSAGE_SERIALIZER_HPP

#include "message_serializer.hpp"

namespace trustedvote {
	class binary_message_serializer : public message_serializer {
	public:
		void serialize(std::ostream &output, message::request_connection const &msg) override;

	public:
		void deserialize(std::istream &input, message::request_connection &res) override;
	};
}

#endif // TRUSTEDVOTE_BINARY_MESSAGE_SERIALIZER_HPP
