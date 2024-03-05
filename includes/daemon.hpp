/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:04:17 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 22:09:54 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_DAEMON_HPP
#define FT_DAEMON_HPP

#include <unistd.h>

// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	/* launch daemon */
	auto launch_daemon(void) -> void;

	/* fork */
	static auto fork(void) -> ::pid_t;

	/* new session */
	static auto new_session(void) -> ::pid_t;

	/* change directory */
	static auto change_directory(const char*) -> void;

	/* close file descriptors */
	static auto close_descriptors(void) -> void;

} // namespace ft

#endif // FT_DAEMON_HPP
