#ifndef TRUSTEDVOTED_LOCAL_NODE_HPP
#define TRUSTEDVOTED_LOCAL_NODE_HPP

#include <trustedvote/node.hpp>
#include <trustedvote/local_node.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/system/error_code.hpp>

class local_node final : public trustedvote::local_node {
public:
	local_node(trustedvote::node_capability caps, boost::asio::io_context &asio);
	local_node(local_node &&other);

	boost::asio::ip::tcp::endpoint endpoint() const { return server.local_endpoint(); }

	void start(boost::asio::ip::tcp::endpoint const &addr);
	void stop();

private:
	void accept_connection(boost::system::error_code const &e, boost::asio::ip::tcp::socket s);

	boost::asio::ip::tcp::acceptor server;
};

#endif // TRUSTEDVOTED_LOCAL_NODE_HPP
