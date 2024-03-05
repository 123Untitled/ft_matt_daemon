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
#include "signal.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
ft::dispatch::dispatch(void)
:	_epoll{::epoll_create1(0)},
	_events{},
	_mask{_::signal::set<SIGINT, SIGTERM, SIGQUIT>()} {

	if (not _epoll)
		throw ERRNO_EXCEPT;
}


// -- public methods ----------------------------------------------------------

/* wait */
auto ft::dispatch::wait(void) -> void {

	/* wait for events */
	const int result = ::epoll_pwait(_epoll, _events, MAX_EVENTS, TIMEOUT, &_mask);

	// check for error
	if (result < 0)
		throw ERRNO_EXCEPT;

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
	if (::epoll_ctl(dispatcher._epoll, EPOLL_CTL_DEL, observer.socket(), nullptr) != 0)
		throw ERRNO_EXCEPT;
}
