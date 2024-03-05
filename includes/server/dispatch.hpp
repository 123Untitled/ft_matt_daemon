/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:39:45 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 21:16:39 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_DISPATCH_HPP
#define FT_DISPATCH_HPP

#include "unique_descriptor.hpp"
#include "exception.hpp"

#include <concepts>
#include <sys/epoll.h>

#include "notifiable.hpp"

// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	/* is event */
	template <::uint32_t E>
	concept is_event = (E & ~(EPOLLIN
							| EPOLLOUT
							| EPOLLRDHUP
							| EPOLLPRI
							| EPOLLERR
							| EPOLLHUP
							| EPOLLET
							| EPOLLONESHOT)) == 0;

    // EPOLLIN EPOLLPRI EPOLLOUT EPOLLRDNORM EPOLLRDBAND
    // EPOLLWRNORM EPOLLWRBAND EPOLLMSG EPOLLERR EPOLLHUP
    // EPOLLRDHUP EPOLLEXCLUSIVE EPOLLWAKEUP EPOLLONESHOT
    // EPOLLET


	// -- D I S P A T C H -----------------------------------------------------

	class dispatch final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::dispatch;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			dispatch(void);

			/* deleted copy constructor */
			dispatch(const self&) = delete;

			/* deleted move constructor */
			dispatch(self&&) = delete;

			/* destructor */
			~dispatch(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment */
			auto operator=(self&&) -> self& = delete;


			// -- public methods ----------------------------------------------

			/* wait */
			auto wait(void) -> void;


		private:

			// -- private enums -----------------------------------------------

			enum : int { TIMEOUT = 500, MAX_EVENTS = 256 };


			// -- private methods ---------------------------------------------

			/* epoll instance */
			ft::unique_descriptor _epoll;

			/* events */
			struct ::epoll_event _events[MAX_EVENTS];

			/* sigset */
			const ::sigset_t _mask;


		// -- friends ---------------------------------------------------------

		/* add as friend */
		template <::uint32_t>
		friend auto add(ft::notifiable&, const self&) -> void;

		/* mod as friend */
		template <::uint32_t>
		friend auto mod(ft::notifiable&, const self&) -> void;

		/* del as friend */
		friend auto del(ft::notifiable&, const self&) -> void;

	}; // class dispatch



	/* add */
	template <::uint32_t E>
	auto add(ft::notifiable& observer, const ft::dispatch& dispatcher) -> void {

		static_assert(ft::is_event<E>, "requires valid epoll event");

		// create event
		struct epoll_event event {
			.events = E,
			.data { .ptr = reinterpret_cast<void*>(&observer) }
		};

		// add event
		if (::epoll_ctl(dispatcher._epoll, EPOLL_CTL_ADD, observer.socket(), &event) != 0)
			throw ERRNO_EXCEPT;
	}

	/* mod */
	template <::uint32_t E>
	auto mod(ft::notifiable& observer, const ft::dispatch& dispatcher) -> void {

		static_assert(ft::is_event<E>, "requires valid epoll event");

		// create event
		struct epoll_event event {
			.events = E,
			.data { .ptr = reinterpret_cast<void*>(&observer) }
		};

		// modify event
		if (::epoll_ctl(dispatcher._epoll, EPOLL_CTL_MOD, observer.socket(), &event) != 0)
			throw ERRNO_EXCEPT;
	}

	/* del */
	auto del(ft::notifiable&, const ft::dispatch&) -> void;


} // namespace ft

#endif // FT_DISPATCH_HPP

