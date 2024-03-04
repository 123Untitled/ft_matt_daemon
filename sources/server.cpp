#include "server.hpp"
#include "address.hpp"
#include "is_running.hpp"
#include "write.hpp"

#include <iostream>





// -- public lifecycle --------------------------------------------------------

/* port constructor */
ft::server::server(void)
: _socket{AF_INET, SOCK_STREAM}, _dispatch{} {

	// set non-blocking mode
	_socket.non_blocking();

	// setup address
	ft::address addr{in_addr{INADDR_ANY}, 4242};

	// bind address to socket
	_socket.bind(addr);

	// listen for connections (default SOMAXCONN)
	_socket.listen();

	// add server to epoll dispatcher
	ft::add<EPOLLIN | EPOLLET | EPOLLHUP | EPOLLRDHUP | EPOLLERR>(*this, _dispatch);

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

	// check for error
	if (events & EPOLLERR) {
		ft::write("epoll error\n");
	}

	// check for hangup
	if (events & EPOLLHUP) {
		ft::write("epoll hangup\n");
	}

	// check for read hangup
	if (events & EPOLLRDHUP) {
		ft::write("epoll read hangup\n");
	}

	// check for read
	if (events & EPOLLIN) {
		ft::write("epoll read\n");

		try {
			// accept connection
			auto new_socket = _socket.accept();

			// set non-blocking mode
			new_socket.non_blocking();


			ft::client client{std::move(new_socket)};

			//_clients.emplace_back(
			//			std::move(new_socket));
			//, _ssl_context);

			// add client to epoll dispatcher
			ft::add<EPOLLIN | EPOLLET | EPOLLHUP | EPOLLRDHUP | EPOLLERR>(client, _dispatch);

		}
		catch (const ft::exception& e) {
			std::cerr << e.what() << std::endl;
		}

	}
}


// -- public accessors --------------------------------------------------------

/* socket */
auto ft::server::socket(void) const noexcept -> int {
	return _socket;
}


