#include "local_node.hpp"

#include <functional>
#include <utility>

namespace tv = trustedvote;

local_node::local_node(tv::node_capability caps, boost::asio::io_context &asio) :
	tv::local_node(caps),
	server(asio)
{
}

local_node::local_node(local_node &&other) :
	tv::local_node(std::forward<tv::local_node>(other)),
	server(std::move(other.server))
{
}

void local_node::start(boost::asio::ip::tcp::endpoint const &addr)
{
	auto h = std::bind(
		&local_node::accept_connection,
		this,
		std::placeholders::_1,
		std::placeholders::_2
	);

	server.open(addr.protocol());
	server.bind(addr);
	server.listen();
	server.async_accept(std::move(h));
}

void local_node::stop()
{
	server.close();
}

void local_node::accept_connection(boost::system::error_code const &e, boost::asio::ip::tcp::socket s)
{
}
