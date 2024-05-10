/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifiable.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:01:12 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 21:55:57 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_NOTIFIABLE_HPP
#define FT_NOTIFIABLE_HPP

#include <cstdint>


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	// -- N O T I F I A B L E ---------------------------------------------------

	class notifiable {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::notifiable;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			notifiable(void) noexcept = default;

			/* copy constructor */
			notifiable(const self&) noexcept = default;

			/* move constructor */
			notifiable(self&&) noexcept = default;

			/* destructor */
			virtual ~notifiable(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public interface --------------------------------------------

			/* notify */
			virtual auto notify(const ::uint32_t) -> void = 0;

			/* socket */
			virtual auto socket(void) const noexcept -> int = 0;

	}; // class notifiable

} // namespace ft

#endif // FT_NOTIFIABLE_HPP
