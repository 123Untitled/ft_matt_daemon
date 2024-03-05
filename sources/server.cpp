#include "server.hpp"
#include "address.hpp"
#include "is_running.hpp"
#include "write.hpp"
#include "tintin_reporter.hpp"

#include <iostream>





// -- public lifecycle --------------------------------------------------------

/* port constructor */
ft::server::server(void)
: _socket{AF_INET, SOCK_STREAM}, _dispatch{} {

	// set non-blocking mode
	_socket.non_blocking();

	// set reuse address
	_socket.reuse_address();

	// setup address
	ft::address addr{in_addr{INADDR_ANY}, 4242};

	// bind address to socket
	_socket.bind(addr);

	// listen for connections (default SOMAXCONN)
	_socket.listen();

	// add server to epoll dispatcher
	ft::add<EPOLLIN | EPOLLET>(*this, _dispatch);


	ft::tintin_reporter::log("server initialized");
}


// -- public methods ----------------------------------------------------------

/* run */
auto ft::server::run(void) -> void {

	while (is::running::state()) {

		// run dispatcher
		_dispatch.wait();
	}
}

/* notify */
auto ft::server::notify(const uint32_t events) -> void {


	// check for read
	if (events & EPOLLIN) {

		try {
			// accept connection
			auto socket = _socket.accept();

			// set non-blocking mode
			socket.non_blocking();

			auto client = _clients.emplace(static_cast<int>(socket),
										   std::move(socket));

			if (not client.second) {
				throw ft::exception{"client emplace failed"};
			}

			// add client to epoll dispatcher
			ft::add<EPOLLIN | EPOLLET>(client.first->second, _dispatch);


			ft::tintin_reporter::log("client connected");

		}
		catch (const ft::exception& e) {
			ft::tintin_reporter::error(e.what());
		}

	}

}


// -- public accessors --------------------------------------------------------

/* socket */
auto ft::server::socket(void) const noexcept -> int {
	return _socket;
}


