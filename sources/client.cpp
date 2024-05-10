/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:53:47 by artblin           #+#    #+#             */
/*   Updated: 2024/05/10 19:27:06 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matt_daemon/client.hpp"
#include "matt_daemon/write.hpp"

#include <utility>
#include <sys/epoll.h>


// -- public lifecycle --------------------------------------------------------

/* socket constructor and ssl connection constructor */
ft::client::client(ft::unique_socket&& socket) noexcept
: _socket{std::move(socket)} {
	ft::write("client constructor succeeded\n");
}


// -- public methods ----------------------------------------------------------

/* notify */
auto ft::client::notify(const ::uint32_t events) -> void {

	if (events & EPOLLIN) {
		ft::write("client epollin\n");
		//
		//static bool accepted = false;
		//
		//bool state = false;
		//
		//if (accepted == false) {
		//	// ssl accept
		//	try {
		//		::write(STDOUT_FILENO, "trying to accept\n", 18);
		//		state = _connection.accept();
		//	}
		//	catch (const _::exception& e) {
		//		std::cout << e.what() << std::endl;
		//	}
		//
		//	if (state == false)
		//		return;
		//
		//	accepted = true;
		//}
		//
		//::write(STDOUT_FILENO, "starting to read\n", 17);
		//
		//
		//// read from socket
		//
		//while (true) {
		//	char buffer[1024];
		//	//auto bytes = recv(_socket, buffer, sizeof(buffer), 0);
		//	auto bytes = _connection.read<1024>(buffer);
		//
		//	if (bytes == -1) {
		//		if (errno == EAGAIN || errno == EWOULDBLOCK)
		//			break;
		//		else {
		//			std::cout << "recv failed" << std::endl;
		//			break;
		//		}
		//	}
		//	else if (bytes == 0) {
		//		std::cout << "client disconnected" << std::endl;
		//		break;
		//	}
		//	else {
		//		std::cout << "received " << bytes << " bytes" << std::endl;
		//
		//		write(STDOUT_FILENO, buffer, bytes);
		//	}
		//}
		//
		//::write(STDOUT_FILENO, "writing anwser\n", 15);
		//_connection.write<1024>("HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n");

	}
	else
		ft::write("other event\n");

}


// -- public accessors --------------------------------------------------------

/* socket */
auto ft::client::socket(void) const noexcept -> int {
	return _socket;
}


