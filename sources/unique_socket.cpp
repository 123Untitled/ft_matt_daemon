/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_socket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:24:13 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 22:46:32 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unique_socket.hpp"
#include "exception.hpp"
#include "address.hpp"

#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>



// -- public lifecycle --------------------------------------------------------

/* socket function constructor */
ft::unique_socket::unique_socket(const int domain,
								 const int type,
								 const int protocol)
: self::unique_descriptor{::socket(domain, type, protocol)} {

	// check socket
	if (_descriptor == INVALID_DESCRIPTOR)
		throw ERRNO_EXCEPT;
}


// -- public methods ----------------------------------------------------------

/* shutdown */
auto ft::unique_socket::shutdown(const int how) const -> void {

	if (::shutdown(_descriptor, how) != 0)
		throw ERRNO_EXCEPT;
}

/* bind */
auto ft::unique_socket::bind(const ft::address& addr) const -> void {

	if (::bind(_descriptor, &addr.as_sockaddr(), addr.size()) != 0)
		throw ERRNO_EXCEPT;
}

/* accept */
auto ft::unique_socket::accept(void) const -> self {

	const int socket = ::accept(_descriptor, nullptr, nullptr);

	if (socket == -1)
		throw ERRNO_EXCEPT;

	return self{socket};
}

/* accept with address */
auto ft::unique_socket::accept(ft::address& addr) const -> self {

	const int socket = ::accept(_descriptor, &addr.as_sockaddr(), &addr.size());

	if (socket == -1)
		throw ERRNO_EXCEPT;

	return self{socket};
}

/* non-blocking */
auto ft::unique_socket::non_blocking(void) const -> void {

	if (::fcntl(_descriptor, F_SETFL, O_NONBLOCK) == -1)
		throw ERRNO_EXCEPT;
}

/* blocking */
auto ft::unique_socket::blocking(void) const -> void {

	if (::fcntl(_descriptor, F_SETFL, 0) == -1)
		throw ERRNO_EXCEPT;
}

/* listen */
auto ft::unique_socket::listen(void) const -> void {

	if (::listen(_descriptor, SOMAXCONN) != 0)
		throw ERRNO_EXCEPT;
}

/* listen with backlog */
auto ft::unique_socket::listen(const int backlog) const -> void {

	if (::listen(_descriptor, backlog) != 0)
		throw ERRNO_EXCEPT;
}

/* reuse address */
auto ft::unique_socket::reuse_address(void) const -> void {

	int opt = 1;

	if (::setsockopt(_descriptor, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw ERRNO_EXCEPT;
}


// -- private lifecycle -------------------------------------------------------

/* int constructor */
ft::unique_socket::unique_socket(const int descriptor) noexcept
: self::unique_descriptor{descriptor} {
}
