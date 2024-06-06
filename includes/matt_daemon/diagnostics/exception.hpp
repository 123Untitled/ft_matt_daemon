/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:13:47 by artblin           #+#    #+#             */
/*   Updated: 2024/05/27 14:12:03 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_EXCEPTION_HPP
#define FT_EXCEPTION_HPP

#include <errno.h>
#include <string.h>

// -- F T  N A M E S P A C E  -------------------------------------------------

namespace ft {


	// -- E X C E P T I O N ----------------------------------------------------

	class exception {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::exception;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr exception(void) noexcept
			: _what{"unknown exception"} {
			}

			/* what constructor */
			constexpr explicit exception(const char* what) noexcept
			: _what{what} {
			}

			/* copy constructor */
			constexpr exception(const self&) noexcept = default;

			/* move constructor */
			constexpr exception(self&&) noexcept = default;

			/* destructor */
			virtual ~exception(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* deleted move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public virtual methods --------------------------------------

			/* what */
			virtual auto what(void) const noexcept -> const char* {
				return _what;
			}


		private:

			// -- private members ---------------------------------------------

			/* what */
			const char* _what;

	}; // class exception



	// -- E R R N O  E X C E P T I O N ----------------------------------------

	class errno_exception : public ft::exception {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::errno_exception;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr errno_exception(const char* where) noexcept
			: _what{} {

				unsigned int i = 0;

				if (where == nullptr)
					where = "unknown";

				while (where[i] != '\0') {
					_what[i] = where[i];
					++i;
				}

				_what[i    ] = ':';
				_what[i + 1] = ' ';

				i += 2;

				const char* desc = ::strerrordesc_np(errno);
				const char* code = ::strerrorname_np(errno);

				if (desc == nullptr)
					desc = "unknown error";

				for (unsigned int j = 0; desc[j] != '\0'; ++j, ++i)
					_what[i] = desc[j];

				_what[i    ] = ' ';
				_what[i + 1] = '(';

				i += 2;

				if (code == nullptr)
					code = "unknown code";

				for (unsigned int j = 0; code[j] != '\0'; ++j, ++i)
					_what[i] = code[j];

				_what[i    ] = ')';
				_what[i + 1] = '\0';

			}


			/* what */
			auto what(void) const noexcept -> const char* override {
				return _what;
			}


		private:

			/* what */
			char _what[1024];

	}; // class errno_exception

} // namespace ft


#define ERRNO_EXCEPT ft::errno_exception{__PRETTY_FUNCTION__}

#endif // FT_EXCEPTION_HPP
