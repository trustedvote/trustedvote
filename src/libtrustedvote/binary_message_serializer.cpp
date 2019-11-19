#include <trustedvote/binary_message_serializer.hpp>

#include <algorithm>
#include <cinttypes>
#include <cstddef>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

#include <arpa/inet.h>

namespace {
	namespace tv = trustedvote;

	void serialize(std::ostream &o, std::uint16_t v)
	{
		v = htons(v);

		o.write(reinterpret_cast<char *>(&v), sizeof(v));
		if (o.bad()) {
			throw std::ios_base::failure("Failed to write output stream");
		}
	}

	void serialize(std::ostream &o, std::uint32_t v)
	{
		v = htonl(v);

		o.write(reinterpret_cast<char *>(&v), sizeof(v));
		if (o.bad()) {
			throw std::ios_base::failure("Failed to write output stream");
		}
	}

	void serialize(std::ostream &o, char unsigned const *v, std::size_t l)
	{
		o.write(reinterpret_cast<char const *>(v), l);
		if (o.bad()) {
			throw std::ios_base::failure("Failed to write output stream");
		}
	}

	void serialize(std::ostream &o, std::string const &v)
	{
		if (v.size() > std::numeric_limits<std::uint16_t>::max()) {
			throw std::invalid_argument("Value too large");
		}

		serialize(o, static_cast<std::uint16_t>(v.size()));
		serialize(o, reinterpret_cast<char unsigned const *>(v.data()), v.size());
	}

	void serialize(std::ostream &o, std::istream &i)
	{
		// get input size
		i.seekg(0, std::ios_base::end);
		if (i.bad()) {
			throw std::ios_base::failure("Failed to seek input stream");
		}

		auto l = i.tellg();
		if (l < 0) {
			throw std::ios_base::failure("Failed to determine stream size");
		}

		if (l > static_cast<signed>(std::numeric_limits<std::uint16_t>::max())) {
			throw std::invalid_argument("Input stream too large");
		}

		// copy input to output
		i.seekg(0);
		if (i.bad()) {
			throw std::ios_base::failure("Failed to seek input stream");
		}

		serialize(o, static_cast<std::uint16_t>(l));

		while (l > 0) {
			char buf[1024];

			i.read(buf, std::min(l, static_cast<decltype(l)>(sizeof(buf))));
			if (i.fail()) {
				throw std::ios_base::failure("Failed to read input stream");
			}

			o.write(buf, i.gcount());
			if (o.bad()) {
				throw std::ios_base::failure("Failed to write output stream");
			}

			l -= i.gcount();
		}
	}

	void deserialize(std::istream &i, std::uint16_t &v)
	{
		i.read(reinterpret_cast<char *>(&v), sizeof(v));
		if (i.fail()) {
			throw std::ios_base::failure("Failed to read input stream");
		}

		v = ntohs(v);
	}

	void deserialize(std::istream &i, std::uint32_t &v)
	{
		i.read(reinterpret_cast<char *>(&v), sizeof(v));
		if (i.fail()) {
			throw std::ios_base::failure("Failed to read input stream");
		}

		v = ntohl(v);
	}

	void deserialize(std::istream &i, char unsigned *v, std::size_t l)
	{
		i.read(reinterpret_cast<char *>(v), l);
		if (i.fail()) {
			throw std::ios_base::failure("Failed to read input stream");
		}
	}

	void deserialize(std::istream &i, std::string &v)
	{
		std::uint16_t l;
		deserialize(i, l);

		v.resize(l);
		deserialize(i, reinterpret_cast<char unsigned *>(v.data()), l);
	}

	void deserialize(std::istream &i, std::ostream &o)
	{
		std::uint16_t l;
		deserialize(i, l);

		while (l > 0) {
			char buf[1024];

			i.read(buf, std::min(l, static_cast<std::uint16_t>(sizeof(buf))));
			if (i.fail()) {
				throw std::ios_base::failure("Failed to read input stream");
			}

			o.write(buf, i.gcount());
			if (o.bad()) {
				throw std::ios_base::failure("Failed to write output stream");
			}

			l -= i.gcount();
		}
	}
}

namespace trustedvote {
	void binary_message_serializer::serialize(std::ostream &output, message::request_connection const &msg)
	{
		std::stringstream b;

		::serialize(b, msg.protocol_version);

		::serialize(output, b);
	}

	void binary_message_serializer::deserialize(std::istream &input, message::request_connection &res)
	{
		std::stringstream b;
		::deserialize(input, b);

		::deserialize(b, res.protocol_version);
	}
}
