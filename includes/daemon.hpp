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


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {


	/* launch daemon */
	auto launch_daemon(void) -> void;

} // namespace ft

#endif // FT_DAEMON_HPP
