/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_socket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:22:37 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 21:36:58 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_UNIQUE_SOCKET
#define FT_UNIQUE_SOCKET

#include "unique_descriptor.hpp"


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	// -- forward declarations ------------------------------------------------

	/* address */
	class address;


	// -- U N I Q U E  S O C K E T --------------------------------------------

	class unique_socket final : public ft::unique_descriptor {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::unique_socket;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			unique_socket(void) noexcept = default;

			/* socket function constructor */
			unique_socket(const int, const int, const int protocol = 0);

			/* deleted copy constructor */
			unique_socket(const self&) = delete;

			/* move constructor */
			unique_socket(self&&) noexcept = default;

			/* destructor */
			~unique_socket(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			inline auto operator=(self&&) noexcept -> self& = default;


			// -- public methods ----------------------------------------------

			/* shutdown */
			auto shutdown(const int) const -> void;

			/* bind */
			auto bind(const ft::address&) const -> void;

			/* accept */
			auto accept(void) const -> self;

			/* accept with address */
			auto accept(ft::address&) const -> self;

			/* non-blocking */
			auto non_blocking(void) const -> void;

			/* blocking */
			auto blocking(void) const -> void;

			/* listen */
			auto listen(void) const -> void;

			/* listen with backlog */
			auto listen(const int) const -> void;


		private:

			// -- private lifecycle -------------------------------------------

			/* int constructor */
			unique_socket(const int) noexcept;

	}; // class unique_socket

} // namespace ft

#endif // FT_UNIQUE_SOCKET
