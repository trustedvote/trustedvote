#ifndef TRUSTEDVOTE_MESSAGE_SERIALIZER_HPP
#define TRUSTEDVOTE_MESSAGE_SERIALIZER_HPP

#include "message/request_connection.hpp"

#include <istream>
#include <ostream>

namespace trustedvote {
	class message_serializer {
	public:
		virtual ~message_serializer();

	public:
		virtual void serialize(std::ostream &output, message::request_connection const &msg) = 0;

	public:
		virtual void deserialize(std::istream &input, message::request_connection &res) = 0;

	protected:
		message_serializer();
	};
};

#endif // TRUSTEDVOTE_MESSAGE_SERIALIZER_HPP
