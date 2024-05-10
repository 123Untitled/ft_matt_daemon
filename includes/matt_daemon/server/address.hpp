/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:28:50 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 21:29:02 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_ADDRESS_HPP
#define FT_ADDRESS_HPP

#include <netinet/in.h>
#include <arpa/inet.h>

#include <string_view>


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	// -- A D D R E S S -------------------------------------------------------

	class address final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::address;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline constexpr address(void) noexcept
			: _addr{}, _size{0} {
			}

			/* ipv4 constructor */
			inline constexpr address(const ::in_addr& ip, const ::in_port_t port) noexcept
			: _addr{}, _size{sizeof(::sockaddr_in)} {
				// interpret as ipv4
				auto& addr = this->as_ipv4();
				// set fields
				addr.sin_family      = AF_INET;
				addr.sin_port        = htons(port);
				addr.sin_addr.s_addr = ip.s_addr;
			}

			/* ipv6 constructor */
			inline constexpr address(const ::in6_addr& ip, const ::in_port_t port) noexcept
			: _addr{}, _size{sizeof(::sockaddr_in6)} {
				// interpret as ipv6
				auto& addr = this->as_ipv6();
				// set fields
				addr.sin6_family = AF_INET6;
				addr.sin6_port   = htons(port);
				addr.sin6_addr   = ip;
			}

			/* copy constructor */
			constexpr address(const self& other) noexcept = default;

			/* move constructor */
			constexpr address(self&& other) noexcept = default;

			/* destructor */
			~address(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self& other) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&& other) noexcept -> self& = default;


			// -- public accessors --------------------------------------------

			/* size */
			inline constexpr auto size(void) noexcept -> ::socklen_t& {
				return _size;
			}

			/* const size */
			inline constexpr auto size(void) const noexcept -> const ::socklen_t& {
				return _size;
			}


			/* is ipv4 */
			inline constexpr auto is_ipv4(void) const noexcept -> bool {
				return _addr.ss_family == AF_INET;
			}

			/* is ipv6 */
			inline constexpr auto is_ipv6(void) const noexcept -> bool {
				return _addr.ss_family == AF_INET6;
			}


			/* as ipv4 */
			inline constexpr auto as_ipv4(void) noexcept -> ::sockaddr_in& {
				return *static_cast<::sockaddr_in*>(static_cast<void*>(&_addr));
			}

			/* const as ipv4 */
			inline constexpr auto as_ipv4(void) const noexcept -> const ::sockaddr_in& {
				return *static_cast<const ::sockaddr_in*>(static_cast<const void*>(&_addr));
			}

			/* as ipv6 */
			inline constexpr auto as_ipv6(void) noexcept -> ::sockaddr_in6& {
				return *static_cast<::sockaddr_in6*>(static_cast<void*>(&_addr));
			}

			/* const as ipv6 */
			inline constexpr auto as_ipv6(void) const noexcept -> const ::sockaddr_in6& {
				return *static_cast<const ::sockaddr_in6*>(static_cast<const void*>(&_addr));
			}

			/* as sockaddr */
			inline constexpr auto as_sockaddr(void) noexcept -> ::sockaddr& {
				return *static_cast<::sockaddr*>(static_cast<void*>(&_addr));
			}

			/* const as sockaddr */
			inline constexpr auto as_sockaddr(void) const noexcept -> const ::sockaddr& {
				return *static_cast<const ::sockaddr*>(static_cast<const void*>(&_addr));
			}



			// -- public modifiers --------------------------------------------

			/* clear */
			inline constexpr auto clear(void) noexcept -> void {
				_addr = {};
				_size = sizeof(::sockaddr_storage);
			}


		private:

			// -- private members ---------------------------------------------

			/* address */
			::sockaddr_storage _addr;

			/* size */
			::socklen_t        _size;


	}; // class address


	inline auto presentation_to_network(const std::string_view& ip, ::in_addr& addr) noexcept -> bool {
		return ::inet_pton(AF_INET, ip.data(), &addr) == 1;
	}

	inline auto presentation_to_network(const std::string_view& ip, ::in6_addr& addr) noexcept -> bool {
		return ::inet_pton(AF_INET6, ip.data(), &addr) == 1;
	}

} // namespace network

#endif // ADDRESS_HPP
