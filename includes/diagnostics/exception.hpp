/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:13:47 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 20:14:31 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_EXCEPTION_HPP
#define FT_EXCEPTION_HPP


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
			inline constexpr exception(void) noexcept
			: _what{} {
			}

			/* what constructor */
			inline constexpr explicit exception(const char* what) noexcept
			: _what{what} {
			}

			/* deleted copy constructor */
			exception(const self&) = delete;

			/* deleted move constructor */
			exception(self&&) = delete;

			/* destructor */
			virtual ~exception(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- public virtual methods --------------------------------------

			/* what */
			virtual inline auto what(void) const noexcept -> const char* {
				return _what != nullptr ? _what : "unknown exception";
			}


		private:

			// -- private members ---------------------------------------------

			/* what */
			const char* _what;

	}; // class exception

} // namespace ft

#endif // FT_EXCEPTION_HPP
