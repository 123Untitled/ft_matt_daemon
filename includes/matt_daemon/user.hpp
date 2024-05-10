/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:56:49 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 20:17:11 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_USER_HPP
#define FT_USER_HPP


// -- F T  N A M E S P A C E  -------------------------------------------------

namespace ft {


	// -- U S E R -------------------------------------------------------------

	class user final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::user;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			user(void) = delete;

			/* destructor */
			~user(void) noexcept = default;


			// -- public static methods ---------------------------------------

			/* is root */
			static auto is_root(void) noexcept -> bool;

	}; // class user

} // namespace ft

#endif // FT_USER_HPP
