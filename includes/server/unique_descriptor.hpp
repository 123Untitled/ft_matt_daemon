/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_descriptor.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:49:10 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 21:21:53 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_UNIQUE_DESCRIPTOR_HPP
#define FT_UNIQUE_DESCRIPTOR_HPP


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	// -- U N I Q U E  D E S C R I P T O R ------------------------------------

	class unique_descriptor {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::unique_descriptor;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			unique_descriptor(void) noexcept;

			/* descriptor constructor */
			explicit unique_descriptor(const int) noexcept;

			/* deleted copy constructor */
			unique_descriptor(const self&) = delete;

			/* move constructor */
			unique_descriptor(self&&) noexcept;

			/* destructor */
			~unique_descriptor(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment */
			auto operator=(const self&) -> self& = delete;

			/* move assignment */
			auto operator=(self&&) noexcept -> self&;

			/* int assignment operator */
			inline auto operator=(const int) noexcept -> self&;


			// -- public conversion operators ---------------------------------

			/* int conversion operator */
			operator int(void) const noexcept;

			/* bool conversion operator */
			explicit operator bool(void) const noexcept;


			// -- public operators --------------------------------------------

			/* not operator */
			auto operator!(void) const noexcept -> bool;


			// -- public modifiers --------------------------------------------

			/* close */
			auto close(void) noexcept -> int;


		protected:

			// -- private enums -----------------------------------------------

			/* invalid descriptor */
			enum : int { INVALID_DESCRIPTOR = -1 };


			// -- private members ---------------------------------------------

			/* file descriptor */
			int _descriptor;

	}; // class unique_descriptor

} // namespace ft

#endif // FT_UNIQUE_DESCRIPTOR_HPP
