#pragma once
#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <csignal>
#include "matt_daemon/is_running.hpp"
#include "matt_daemon/diagnostics/exception.hpp"



// -- _  N A M E S P A C E ----------------------------------------------------

namespace _ {


	// -- S I G N A L ---------------------------------------------------------

	class signal final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = _::signal;


			// -- public static methods ---------------------------------------

			/* setup */
			static inline auto setup(void) -> void {
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
				::signal(SIGINT, self::handler);
				::signal(SIGTERM, self::handler);
				::signal(SIGQUIT, self::handler);

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

				::write(STDOUT_FILENO, "signal received\n", 16);

				switch (signum) {
					case SIGINT:
						::is::running::stop();
						break;
					case SIGTERM:
						::is::running::stop();
						break;
					case SIGQUIT:
						::is::running::stop();
						break;
					default:
						break;
				}
			}


	}; // class signal

} // namespace _

#endif // SIGNAL_HPP
