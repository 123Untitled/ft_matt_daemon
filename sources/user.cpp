/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:12:41 by artblin           #+#    #+#             */
/*   Updated: 2024/05/10 19:30:51 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matt_daemon/user.hpp"

#include <unistd.h>


// -- public static methods ---------------------------------------------------

/* is root */
auto ft::user::is_root(void) noexcept -> bool {
	static auto id = ::geteuid();
	return id == 0;
}
