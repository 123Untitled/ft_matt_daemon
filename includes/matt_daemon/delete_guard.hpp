/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_guard.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:55:12 by artblin           #+#    #+#             */
/*   Updated: 2024/06/10 19:07:02 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_DELETE_GUARD_HPP
#define FT_DELETE_GUARD_HPP

#include <unistd.h>
#include "matt_daemon/tintin_reporter.hpp"


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	// -- D E L E T E  G U A R D ------------------------------------------------

	class delete_guard final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::delete_guard;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			delete_guard(void) = delete;

			/* path constructor */
			explicit delete_guard(const char* path) noexcept
			: _path{path} {
			}

			/* deleted copy constructor */
			delete_guard(const self&) = delete;

			/* deleted move constructor */
			delete_guard(self&&) = delete;

			/* destructor */
			~delete_guard(void) noexcept {

				if (_path == nullptr)
					return;

				if (::unlink(_path) != 0)
					ft::tintin_reporter::log("delete_guard: unlink failed");
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


		private:

			// -- private members ---------------------------------------------

			/* path */
			const char* _path;

	}; // class delete_guard

} // namespace ft

#endif // FT_DELETE_GUARD_HPP
