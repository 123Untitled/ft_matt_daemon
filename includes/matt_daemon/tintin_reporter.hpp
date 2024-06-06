#pragma once

#ifndef FT_TINTIN_REPORTER_HPP
#define FT_TINTIN_REPORTER_HPP

#include "matt_daemon/server/unique_file.hpp"
#include "matt_daemon/time.hpp"


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	// -- T I N T I N  R E P O R T E R ----------------------------------------

	class tintin_reporter final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::tintin_reporter;


			// -- public static methods ---------------------------------------

			/* log */
			static auto log(const char* message) -> void {
				const char* time = ft::time();

				ft::unique_file file{
					"/mnt/nfs/homes/artblin/Desktop/ft_matt_daemon/matt_daemon.log",
					O_RDWR | O_CREAT | O_APPEND,
					0600};

				//self& reporter = self::shared();

				file.write(time, __builtin_strlen(time));
				file.write(" ", 1U);
				file.write(message, __builtin_strlen(message));
				file.write("\n", 1U);
			}

			/* info */
			static auto info(const char* message) -> void {
			}

			/* error */
			static auto error(const char* message) -> void {
			}


		private:

			// -- private lifecycle -------------------------------------------

			/* default constructor */
			tintin_reporter(void) {
			//: _file{"/mnt/nfs/homes/artblin/Desktop/ft_matt_daemon/matt_daemon.log", O_RDWR | O_CREAT | O_APPEND, 0600} {
				// /var/log/matt_daemon/matt_daemon.log
			}

			/* deleted copy constructor */
			tintin_reporter(const self&) = delete;

			/* deleted move constructor */
			tintin_reporter(self&&) = delete;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment */
			auto operator=(self&&) -> self& = delete;


			// -- private static methods --------------------------------------

			/* shared */
			static auto shared(void) -> self& {
				static self instance;
				return instance;
			}


			// -- private members ---------------------------------------------

			/* file */
			//ft::unique_file _file;

	}; // class tintin_reporter

} // namespace ft

#endif // FT_TINTIN_REPORTER_HPP
