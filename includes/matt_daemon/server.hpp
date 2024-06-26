/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:43:00 by artblin           #+#    #+#             */
/*   Updated: 2024/05/27 19:18:37 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_SERVER_HPP
#define FT_SERVER_HPP

#include "client.hpp"

#include "matt_daemon/notifiable.hpp"
#include "matt_daemon/io_event.hpp"
#include "matt_daemon/server/unique_socket.hpp"
#include "matt_daemon/server/dispatch.hpp"

#include <unordered_map>


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	// -- S E R V E R ---------------------------------------------------------

	class server final : public ft::io_event {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::server;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			server(void);

			/* deleted copy constructor */
			server(const self&) = delete;

			/* move constructor */
			server(self&&) noexcept = default;

			/* destructor */
			~server(void) noexcept = default;


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

	}; // class server

} // namespace _

#endif // SERVER_HPP
