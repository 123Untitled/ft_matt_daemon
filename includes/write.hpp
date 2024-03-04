/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:08:33 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 20:09:03 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_WRITE_HPP
#define FT_WRITE_HPP

#include <unistd.h>

// -- F T  N A M E S P A C E  -------------------------------------------------

namespace ft {


	// -- W R I T E -------------------------------------------------------------

	/* write */
	template <int F = STDIN_FILENO, decltype(sizeof(0)) N>
	inline auto write(const char (&msg)[N]) noexcept -> long {
		return ::write(F, msg, N - 1);
	}

} // namespace ft

#endif // FT_WRITE_HPP
