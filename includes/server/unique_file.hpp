/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_file.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:38:18 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 22:07:19 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_UNIQUE_FILE_HPP
#define FT_UNIQUE_FILE_HPP

#include "unique_descriptor.hpp"
#include "exception.hpp"

#include <fcntl.h>


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	// -- U N I Q U E  F I L E ------------------------------------------------

	class unique_file final : public ft::unique_descriptor {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::unique_file;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			unique_file(void) noexcept = default;

			/* open function constructor */
			template <decltype(sizeof(0)) N, typename... A>
			inline unique_file(const char (&path)[N], const A&... args)
			: self::unique_descriptor{::open(path, args...)} {

				// check socket
				if (_descriptor == INVALID_DESCRIPTOR)
					throw ft::exception{"open failed"};
			}

			/* deleted copy constructor */
			unique_file(const self&) = delete;

			/* move constructor */
			unique_file(self&&) noexcept = default;

			/* destructor */
			~unique_file(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			inline auto operator=(self&&) noexcept -> self& = default;


		private:


	}; // class unique_file

} // namespace ft

#endif // FT_UNIQUE_FILE_HPP
