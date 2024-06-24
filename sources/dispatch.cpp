/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:12:59 by artblin           #+#    #+#             */
/*   Updated: 2024/06/24 16:14:25 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matt_daemon/server/dispatch.hpp"
#include "matt_daemon/signal/signal.hpp"


// -- private lifecycle -------------------------------------------------------

/* default constructor */
ft::dispatch::dispatch(void)
:	_epoll{::epoll_create1(0)},
	_events{},
	_clients{},
	_mask{ft::signal::set<SIGINT, SIGTERM, SIGQUIT, SIGKILL, SIGABRT, SIGHUP>()} {

	if (not _epoll)
		throw ft::errno_exception{"dispatch constructor"};
}


// -- public methods ----------------------------------------------------------

/* wait */
auto ft::dispatch::_wait(void) -> void {

	/* wait for events */
	const int result = ::epoll_pwait(_epoll, _events, MAX_EVENTS, TIMEOUT, &_mask);

	// check for error
	if (result < 0)
		throw ft::errno_exception{"dispatch epoll_pwait"};

	// loop over events
	for (int i = 0; i < result; ++i) {

		// get event type
		const auto type = _events[i].events;

		if (type & EPOLLERR or type & EPOLLHUP) {
			continue;
		}

		if (type & EPOLLIN) {
			// notify observer
			reinterpret_cast<ft::io_event*>
				(_events[i].data.ptr)->receive();
		}

		if (type & EPOLLOUT) {
			// notify observer
			reinterpret_cast<ft::io_event*>
				(_events[i].data.ptr)->send();
		}
	}
}
