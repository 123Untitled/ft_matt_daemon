/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_event.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:12:06 by artblin           #+#    #+#             */
/*   Updated: 2024/05/27 19:17:55 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_IO_EVENT_HPP
#define FT_IO_EVENT_HPP


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	// -- I O  E V E N T ------------------------------------------------------

	class io_event {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::io_event;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr io_event(void) noexcept = default;

			/* deleted copy constructor */
			io_event(const self&) = delete;

			/* move constructor */
			constexpr io_event(self&&) noexcept = default;

			/* destructor */
			virtual ~io_event(void) = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) noexcept -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public interface --------------------------------------------

			/* send */
			virtual auto send(void) -> void = 0;

			/* receive */
			virtual auto receive(void) -> void = 0;

			/* socket */
			virtual auto socket(void) const noexcept -> int = 0;

	}; // class io_event

} // namespace ft

#endif // FT_IO_EVENT_HPP
