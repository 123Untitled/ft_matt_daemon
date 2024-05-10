/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flock_guard.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:37:46 by artblin           #+#    #+#             */
/*   Updated: 2024/05/10 19:30:42 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matt_daemon/flock_guard.hpp"
#include "matt_daemon/server/unique_file.hpp"
#include "matt_daemon/diagnostics/exception.hpp"

#include <sys/file.h>


// -- public lifecycle --------------------------------------------------------

/* unique_file constructor */
ft::flock_guard::flock_guard(const ft::unique_file& file)
: _file{file} {

	if (::flock(_file, LOCK_EX | LOCK_NB) == -1)
		throw ERRNO_EXCEPT;
}

/* destructor */
ft::flock_guard::~flock_guard(void) noexcept {
	::flock(_file, LOCK_UN);
}
