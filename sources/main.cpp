/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:55:53 by artblin           #+#    #+#             */
/*   Updated: 2024/05/10 19:33:28 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matt_daemon/user.hpp"
#include "matt_daemon/write.hpp"
#include "matt_daemon/daemon.hpp"
#include "matt_daemon/diagnostics/exception.hpp"

#include "matt_daemon/time.hpp"
#include "matt_daemon/tintin_reporter.hpp"

#include <iostream>

int main(void) {

	//if (ft::user::is_root() == false) {
	//	ft::write<STDERR_FILENO>("You must be root to execute this program\n");
	//	return -1;
	//}

	try {
		ft::launch_daemon();
	}
	catch (const ft::exception& e) {

		ft::tintin_reporter::log(e.what());

		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}
