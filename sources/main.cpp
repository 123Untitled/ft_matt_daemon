/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:55:53 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 22:44:09 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"
#include "write.hpp"
#include "daemon.hpp"
#include "exception.hpp"


int main(void) {

	//if (ft::user::is_root() == false) {
	//	ft::write<STDERR_FILENO>("You must be root to execute this program\n");
	//	return -1;
	//}

	try {
		ft::launch_daemon();
	}
	catch (const ft::exception& e) {
		::write(STDERR_FILENO, e.what(), __builtin_strlen(e.what()));
		::write(STDERR_FILENO, "\n", 1);
		return -1;
	}


	return 0;
}
