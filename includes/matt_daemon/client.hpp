/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:50:43 by artblin           #+#    #+#             */
/*   Updated: 2024/05/10 19:26:51 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_CLIENT_HPP
#define FT_CLIENT_HPP

#include "matt_daemon/notifiable.hpp"
#include "matt_daemon/server/unique_socket.hpp"

#include <cstdint>


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	// -- C L I E N T ---------------------------------------------------------

	class client final : public ft::notifiable {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::client;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			client(void) = delete;

			/* socket constructor */
			client(ft::unique_socket&&) noexcept;

			/* deleted copy constructor */
			client(const self&) = delete;

			/* move constructor */
			client(self&&) noexcept = default;

			/* destructor */
			~client(void) = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public methods ----------------------------------------------

			/* notify */
			auto notify(const ::uint32_t) -> void override;


			// -- public accessors --------------------------------------------

			/* socket */
			auto socket(void) const noexcept -> int override;


		private:

			// -- private members ---------------------------------------------

			/* socket */
			ft::unique_socket _socket;

	}; // class client


} // namespace _

#endif // CLIENT_HPP
