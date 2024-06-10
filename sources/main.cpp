/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:55:53 by artblin           #+#    #+#             */
/*   Updated: 2024/06/10 19:38:27 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matt_daemon/daemon.hpp"
#include "matt_daemon/diagnostics/exception.hpp"
#include "matt_daemon/tintin_reporter.hpp"

#include <cstdlib>

int main(void) {

	try {
		ft::launch_daemon();
	}
	catch (const ft::exception& e) {
		ft::tintin_reporter::log(e.what());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
