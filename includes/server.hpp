/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:43:00 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 21:53:35 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_SERVER_HPP
#define FT_SERVER_HPP

#include "client.hpp"

#include "notifiable.hpp"
#include "unique_socket.hpp"
#include "dispatch.hpp"


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	// -- S E R V E R ---------------------------------------------------------

	class server final : public ft::notifiable {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::server;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			server(void);

			/* deleted copy constructor */
			server(const self&) = delete;

			/* deleted move constructor */
			server(self&&) = delete;

			/* destructor */
			~server(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment */
			auto operator=(self&&) -> self& = delete;


			// -- public methods ----------------------------------------------

			/* run */
			auto run(void) -> void;

			/* notify */
			auto notify(const ::uint32_t) -> void override;


			// -- public accessors --------------------------------------------

			/* socket */
			auto socket(void) const noexcept -> int override;


		private:

			// -- private members ---------------------------------------------

			/* socket */
			ft::unique_socket _socket;

			/* dispatcher */
			ft::dispatch _dispatch;

			/* clients */
			char _clients[sizeof(ft::client) * 3];

	}; // class server

} // namespace _

#endif // SERVER_HPP
