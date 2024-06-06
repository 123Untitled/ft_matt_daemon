/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_ptr.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:13:47 by artblin           #+#    #+#             */
/*   Updated: 2024/06/06 22:04:12 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_UNIQUE_PTR_HPP
#define FT_UNIQUE_PTR_HPP


// -- F T  N A M E S P A C E  -------------------------------------------------

namespace ft {


	// -- U N I Q U E  P T R --------------------------------------------------

	template <typename ___type>
	class unique_ptr final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::unique_ptr<___type>;


		private:

			// -- private data ------------------------------------------------



	}; // class unique_ptr


	// -- non-member functions ------------------------------------------------

	/* make unique */
	template <typename ___type, typename... ___params>
	auto make_unique(___params&&... ___args) -> unique_ptr<___type> {
		return {};
	}


} // namespace ft

#endif // FT_UNIQUE_PTR_HPP
