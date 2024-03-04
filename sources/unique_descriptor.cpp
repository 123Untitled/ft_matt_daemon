/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_descriptor.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:49:07 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 21:21:51 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unique_descriptor.hpp"
#include <unistd.h>


// -- public lifecycle --------------------------------------------------------

/* default constructor */
ft::unique_descriptor::unique_descriptor(void) noexcept
: _descriptor{INVALID_DESCRIPTOR} {
}

/* descriptor constructor */
ft::unique_descriptor::unique_descriptor(const int descriptor) noexcept
: _descriptor{descriptor} {
}

/* move constructor */
ft::unique_descriptor::unique_descriptor(self&& other) noexcept
: _descriptor{other._descriptor} {
	other._descriptor = INVALID_DESCRIPTOR;
}

/* destructor */
ft::unique_descriptor::~unique_descriptor(void) noexcept {
	if (_descriptor == INVALID_DESCRIPTOR)
		return;
	::close(_descriptor);
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto ft::unique_descriptor::operator=(self&& other) noexcept -> self& {
	if (this == &other)
		return *this;
	if (_descriptor != INVALID_DESCRIPTOR)
		::close(_descriptor);
	_descriptor       = other._descriptor;
	other._descriptor = INVALID_DESCRIPTOR;
	return *this;
}

/* int assignment operator */
auto ft::unique_descriptor::operator=(const int descriptor) noexcept -> self& {
	if (_descriptor != INVALID_DESCRIPTOR)
		::close(_descriptor);
	_descriptor = descriptor;
	return *this;
}


// -- public conversion operators ---------------------------------------------

/* int conversion operator */
ft::unique_descriptor::operator int(void) const noexcept {
	return _descriptor;
}

/* bool conversion operator */
ft::unique_descriptor::operator bool(void) const noexcept {
	return _descriptor != INVALID_DESCRIPTOR;
}


// -- public operators --------------------------------------------------------

/* not operator */
auto ft::unique_descriptor::operator!(void) const noexcept -> bool {
	return _descriptor == INVALID_DESCRIPTOR;
}


// -- public modifiers --------------------------------------------------------

/* close */
auto ft::unique_descriptor::close(void) noexcept -> int {
	if (_descriptor == INVALID_DESCRIPTOR)
		return 0;
	int state = ::close(_descriptor);
	_descriptor = INVALID_DESCRIPTOR;
	return state;
}
