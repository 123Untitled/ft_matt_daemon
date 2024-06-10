#pragma once
#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <csignal>
#include "matt_daemon/is_running.hpp"
#include "matt_daemon/diagnostics/exception.hpp"
#include "matt_daemon/tintin_reporter.hpp"



// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	// -- S I G N A L ---------------------------------------------------------

	class signal final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::signal;


			// -- public static methods ---------------------------------------

			/* setup */
			static auto setup(void) -> void {
				static_cast<void>(self::shared());
			}

			/* sigset */
			template <int... S>
			static auto set(void) -> ::sigset_t {
				::sigset_t set;

				if (::sigemptyset(&set) != 0)
					throw ft::exception{"sigemptyset failed"};

				(self::add_set<S>(set), ...);

				return set;
			}


		private:

			// -- private lifecycle -------------------------------------------

			/* default constructor */
			signal(void) {
				// setup signal handler
				if (::signal(SIGINT, self::handler) == SIG_ERR
				|| ::signal(SIGTERM, self::handler) == SIG_ERR
				|| ::signal(SIGQUIT, self::handler) == SIG_ERR
				|| ::signal(SIGABRT, self::handler) == SIG_ERR
				|| ::signal(SIGHUP,  self::handler) == SIG_ERR) {
					throw ft::exception{"signal failed"};
				}
			}

			/* deleted copy constructor */
			signal(const self&) = delete;

			/* deleted move constructor */
			signal(self&&) = delete;

			/* destructor */
			~signal(void) = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- private static methods --------------------------------------

			/* shared */
			static auto shared(void) -> self& {
				static self instance;
				return instance;
			}

			/* add set */
			template <int S>
			static auto add_set(::sigset_t& set) -> void {
				if (::sigaddset(&set, S) != 0)
					throw ft::exception{"sigaddset failed"};
			}

			/* handler */
			static auto handler(const int signum) -> void {

				switch (signum) {
					case SIGINT:
						ft::tintin_reporter::log("signal: SIGINT");
						::is::running::stop();
						break;
					case SIGTERM:
						ft::tintin_reporter::log("signal: SIGTERM");
						::is::running::stop();
						break;
					case SIGQUIT:
						ft::tintin_reporter::log("signal: SIGQUIT");
						::is::running::stop();
						break;
					case SIGKILL:
						ft::tintin_reporter::log("signal: SIGKILL");
						::is::running::stop();
						break;
					case SIGABRT:
						ft::tintin_reporter::log("signal: SIGABRT");
						::is::running::stop();
						break;
					case SIGHUP:
						ft::tintin_reporter::log("signal: SIGHUP");
						::is::running::stop();
						break;
					default:
						break;
				}
			}


	}; // class signal

} // namespace _

#endif // SIGNAL_HPP
