/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:13:47 by artblin           #+#    #+#             */
/*   Updated: 2024/06/24 16:13:07 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_EXCEPTION_HPP
#define FT_EXCEPTION_HPP

#include <errno.h>
#include <string.h>
#include <string>


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
			: exception{where != nullptr ? where : "unknown"}, _what{} {


				_what.reserve(256);
				_what.append(exception::what());
				_what.append(": ");
				_what.append(strerror(errno));

			}


			/* what */
			auto what(void) const noexcept -> const char* override {
				return _what.data();
			}


		private:

			/* what */
			std::string _what;

	}; // class errno_exception

} // namespace ft


#endif // FT_EXCEPTION_HPP
