/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:39:45 by artblin           #+#    #+#             */
/*   Updated: 2024/05/27 20:05:39 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_DISPATCH_HPP
#define FT_DISPATCH_HPP

#include "unique_descriptor.hpp"
#include "matt_daemon/diagnostics/exception.hpp"
#include "matt_daemon/is_running.hpp"

#include "matt_daemon/tintin_reporter.hpp"

#include <sys/epoll.h>

#include "matt_daemon/io_event.hpp"
#include <vector>
#include <memory>


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	// -- D I S P A T C H -----------------------------------------------------

	class dispatch final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::dispatch;


			// -- public lifecycle --------------------------------------------

			/* deleted copy constructor */
			dispatch(const self&) = delete;

			/* deleted move constructor */
			dispatch(self&&) = delete;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment */
			auto operator=(self&&) -> self& = delete;


			// -- public static methods ---------------------------------------

			/* add */
			static auto add(std::unique_ptr<ft::io_event>&& ev) -> void {

				auto& instance = self::shared();

				// check clients count
				if (instance._clients.size() == 3U)
					throw ft::exception("too many clients");

				// add client
				instance._clients.emplace_back(std::move(ev));

				auto& client = instance._clients.back();

				// create event
				struct epoll_event event {
					.events = EPOLLIN,
					.data { .ptr = reinterpret_cast<void*>(client.get()) }
				};

				// add event
				if (::epoll_ctl(self::shared()._epoll, EPOLL_CTL_ADD, client->socket(), &event) != 0)
					throw ERRNO_EXCEPT;
			}

			/* del */
			static auto del(ft::io_event& ev) -> void {

				// remove event
				if (::epoll_ctl(self::shared()._epoll, EPOLL_CTL_DEL, ev.socket(), nullptr) != 0)
					throw ERRNO_EXCEPT;

				auto& instance = self::shared();

				// remove client
				for (auto it = instance._clients.begin(); it != instance._clients.end(); ++it) {
					const auto& client = *it;
					if (client->socket() == ev.socket()) {
						instance._clients.erase(it);
						break;
					}
				}

			}



			// -- public methods ----------------------------------------------

			/* run */
			static auto run(void) -> void {

				// start running
				is::running::start();

				ft::tintin_reporter::log("server running");

				while (is::running::state()) {
					try {
						self::shared()._wait();
					}
					catch (const ft::exception& e) {
						ft::tintin_reporter::error(e.what());
					}
				}
			}


		private:

			// -- private enums -----------------------------------------------

			enum : int { TIMEOUT = 500, MAX_EVENTS = 256 };


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			dispatch(void);

			/* destructor */
			~dispatch(void) noexcept = default;


			// -- private static methods --------------------------------------

			/* shared */
			static auto shared(void) -> self& {
				static self instance;
				return instance;
			}


			// -- private methods ---------------------------------------------

			/* wait */
			auto _wait(void) -> void;


			// -- private members ---------------------------------------------

			/* epoll instance */
			ft::unique_descriptor _epoll;

			/* events */
			struct ::epoll_event _events[MAX_EVENTS];

			/* clients */
			std::vector<std::unique_ptr<ft::io_event>> _clients;

			/* sigset */
			const ::sigset_t _mask;

	}; // class dispatch

} // namespace ft

#endif // FT_DISPATCH_HPP

