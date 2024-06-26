/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:50:43 by artblin           #+#    #+#             */
/*   Updated: 2024/05/27 15:24:27 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_CLIENT_HPP
#define FT_CLIENT_HPP

#include "matt_daemon/io_event.hpp"
#include "matt_daemon/server/unique_socket.hpp"

#include <cstdint>


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	// -- C L I E N T ---------------------------------------------------------

	class client final : public ft::io_event {

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

			/* send */
			auto send(void) -> void override;

			/* receive */
			auto receive(void) -> void override;


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
