/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_file.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:38:11 by artblin           #+#    #+#             */
/*   Updated: 2024/05/10 19:31:07 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matt_daemon/server/unique_file.hpp"
#include "matt_daemon/diagnostics/exception.hpp"


// -- public methods ----------------------------------------------------------

/* open function constructor */
ft::unique_file::unique_file(const char* path, const int flags, const ::mode_t mode)
: self::unique_descriptor{::open(path, flags, mode)} {

	// check file
	if (_descriptor == INVALID_DESCRIPTOR)
		throw ERRNO_EXCEPT;
}

/* write */
auto ft::unique_file::write(const void* buf, const ::size_t count) const noexcept -> ::ssize_t {
	return ::write(_descriptor, buf, count);
}
