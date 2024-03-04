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
#include <fcntl.h>


// -- public lifecycle --------------------------------------------------------

/* socket function constructor */
ft::unique_socket::unique_socket(const int domain,
								 const int type,
								 const int protocol)
: self::unique_descriptor{::socket(domain, type, protocol)} {

	// check socket
	if (not _descriptor)
		throw ft::exception{"socket failed"};
}


// -- public methods ----------------------------------------------------------

/* shutdown */
auto ft::unique_socket::shutdown(const int how) const -> void {
	if (::shutdown(_descriptor, how) != 0)
		throw ft::exception{"shutdown failed"};
}

/* bind */
auto ft::unique_socket::bind(const ft::address& addr) const -> void {

	const int state = ::bind(_descriptor, &addr.as_sockaddr(), addr.size());

	if (state != 0)
		throw ft::exception{"bind failed"};
}

/* accept */
auto ft::unique_socket::accept(void) const -> self {

	const int socket = ::accept(_descriptor, nullptr, nullptr);

	if (socket == -1)
		throw ft::exception{"accept failed"};

	return self{socket};
}

/* accept with address */
auto ft::unique_socket::accept(ft::address& addr) const -> self {

	const int socket = ::accept(_descriptor, &addr.as_sockaddr(), &addr.size());

	if (socket == -1)
		throw ft::exception{"accept failed"};

	return self{socket};
}

/* non-blocking */
auto ft::unique_socket::non_blocking(void) const -> void {

	int state = ::fcntl(_descriptor, F_SETFL, O_NONBLOCK);

	if (state == -1)
		throw ft::exception{"non_blocking failed"};
}

/* blocking */
auto ft::unique_socket::blocking(void) const -> void {

	int state = ::fcntl(_descriptor, F_SETFL, 0);

	if (state == -1)
		throw ft::exception{"blocking failed"};
}

/* listen */
auto ft::unique_socket::listen(void) const -> void {

	const int state = ::listen(_descriptor, SOMAXCONN);

	if (state != 0)
		throw ft::exception{"listen failed"};
}

/* listen with backlog */
auto ft::unique_socket::listen(const int backlog) const -> void {

	const int state = ::listen(_descriptor, backlog);

	if (state != 0)
		throw ft::exception{"listen failed"};
}


// -- private lifecycle -------------------------------------------------------

/* int constructor */
ft::unique_socket::unique_socket(const int descriptor) noexcept
: self::unique_descriptor{descriptor} {
}
