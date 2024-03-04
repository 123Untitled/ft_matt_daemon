#pragma once
#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <csignal>
#include "is_running.hpp"


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



		private:

			// -- private lifecycle -------------------------------------------

			/* default constructor */
			inline signal(void) {

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
			static inline auto shared(void) -> self& {
				static self instance;
				return instance;
			}

			/* handler */
			static inline auto handler(const int signum) -> void {

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
