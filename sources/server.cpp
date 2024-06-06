#include "matt_daemon/server.hpp"
#include "matt_daemon/server/address.hpp"
#include "matt_daemon/is_running.hpp"
#include "matt_daemon/tintin_reporter.hpp"

#include <memory>



// -- public lifecycle --------------------------------------------------------

/* port constructor */
ft::server::server(void)
: _socket{AF_INET, SOCK_STREAM} {

	// set non-blocking mode
	_socket.non_blocking();

	// set reuse address
	_socket.reuse_address();

	// setup address
	ft::address addr{in_addr{INADDR_ANY}, 4342};

	// bind address to socket
	_socket.bind(addr);

	// listen for connections (default SOMAXCONN)
	_socket.listen();

	// log server initialized
	ft::tintin_reporter::log("server initialized");
}


// -- public methods ----------------------------------------------------------


/* send */
auto ft::server::send(void) -> void {
}

/* receive */
auto ft::server::receive(void) -> void {

	// log connection
	ft::tintin_reporter::log("server accepting connection");

	// accept connection
	auto socket = _socket.accept();

	// set non-blocking mode
	socket.non_blocking();

	// create client
	std::unique_ptr<ft::io_event> client
		= std::make_unique<ft::client>(std::move(socket));

	// add client to epoll dispatcher
	ft::dispatch::add(std::move(client));

	// log connection
	ft::tintin_reporter::log("client connected");
}


// -- public accessors --------------------------------------------------------

/* socket */
auto ft::server::socket(void) const noexcept -> int {
	return _socket;
}
