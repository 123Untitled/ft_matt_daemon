/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:12:59 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 21:16:03 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dispatch.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
ft::dispatch::dispatch(void)
: _epoll{::epoll_create1(0)}, _events{} {

	if (not _epoll)
		throw ft::exception{"epoll_create1"};
}


// -- public methods ----------------------------------------------------------

/* wait */
auto ft::dispatch::wait(void) -> void {

	/* wait for events */
	const int result = ::epoll_wait(_epoll, _events, MAX_EVENTS, TIMEOUT);

	// check for error
	if (result < 0)
		throw ft::exception{"epoll_wait failed"};

	// loop over events
	for (int i = 0; i < result; ++i) {
		// notify observer
		reinterpret_cast<ft::notifiable*>
			(_events[i].data.ptr)->notify(_events[i].events);
	}
}


// -- friends -----------------------------------------------------------------

/* del */
auto ft::del(ft::notifiable& observer, const ft::dispatch& dispatcher) -> void {

	// remove event
	const int state = ::epoll_ctl(dispatcher._epoll, // epoll instance
								  EPOLL_CTL_DEL,     // delete operation
								  observer.socket(), // get socket fd
								  nullptr);          // no need event struct (maybe not good practice !)

	if (state != 0)
		throw ft::exception{"epoll del failed"};

}
