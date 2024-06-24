/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:53:47 by artblin           #+#    #+#             */
/*   Updated: 2024/06/24 16:15:15 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matt_daemon/client.hpp"
#include "matt_daemon/write.hpp"
#include "matt_daemon/tintin_reporter.hpp"
#include "matt_daemon/server/dispatch.hpp"

#include <utility>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>


// -- public lifecycle --------------------------------------------------------

/* socket constructor and ssl connection constructor */
ft::client::client(ft::unique_socket&& socket) noexcept
: _socket{std::move(socket)} {
	ft::write("client constructor succeeded\n");
}


// -- public methods ----------------------------------------------------------

/* send */
auto ft::client::send(void) -> void {
}

/* receive */
auto ft::client::receive(void) -> void {


	std::string str;

	while (true) {

		char buffer[1024];
		auto bytes = ::recv(_socket, buffer, sizeof(buffer), 0);

		if (bytes < 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;
			else {
				throw ft::errno_exception{"client recv"};
			}
		}
		else if (bytes == 0) {
			// disconnect
			ft::tintin_reporter::log("client disconnected");
			ft::dispatch::del(*this);
			return;
		}
		else {
			str.append(buffer, static_cast<std::size_t>(bytes));
		}
	}

	if (str.empty())
		return;

	if (str == "quit") {
		ft::tintin_reporter::log("quit command received");
		is::running::stop();
		return;
	}

	ft::tintin_reporter::log(str.data());
}


// -- public accessors --------------------------------------------------------

/* socket */
auto ft::client::socket(void) const noexcept -> int {
	return _socket;
}


