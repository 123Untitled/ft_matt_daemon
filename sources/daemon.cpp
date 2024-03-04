/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:03:45 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 22:45:15 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daemon.hpp"
#include "exception.hpp"
#include "server.hpp"
#include "signal.hpp"
#include "unique_file.hpp"
#include "flock_guard.hpp"
#include "write.hpp"

#include <unistd.h>
#include <sys/stat.h>

#include <cstring>
#include <sys/file.h>
#include <sys/types.h>


static auto close_descriptors(void) -> void {
	if (::close( STDIN_FILENO) != 0
	 || ::close(STDOUT_FILENO) != 0
	 || ::close(STDERR_FILENO) != 0)
		throw ft::exception{"close failed"};
}


/* daemon */
auto ft::launch_daemon(void) -> void {


	// fork process
	::pid_t pid = ::fork();

	// check error
	if (pid < 0)
		throw ft::exception{"fork failed"};

	// return in parent process
	if (pid > 0) return;


	// check if server is already running
	ft::unique_file file{"matt_daemon.lock", O_CREAT | O_RDWR, 0666};

	{
		// lock file
		ft::flock_guard lock{file};

		_::signal::setup();

		// create server
		ft::server server;

		// start running
		is::running::start();


		// create new session
		if (::setsid() < 0)
			throw ft::exception{"setsid failed"};

		//::umask(0);

		// change working directory
		if (::chdir("/") != 0)
			throw ft::exception{"chdir failed"};

		// close descriptors
		close_descriptors();

		ft::unique_file stds[3] = {
			{"/dev/null", O_RDONLY},
			{"/dev/null", O_WRONLY},
			{"/dev/null", O_WRONLY}
		};

		// run server
		server.run();

	}

}
