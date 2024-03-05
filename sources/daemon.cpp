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


auto ft::close_descriptors(void) -> void {
	if (::close( STDIN_FILENO) != 0
	 || ::close(STDOUT_FILENO) != 0
	 || ::close(STDERR_FILENO) != 0)
		throw ERRNO_EXCEPT;
}


/* fork */
auto ft::fork(void) -> ::pid_t {

	::pid_t pid = ::fork();

	if (pid < 0)
		throw ERRNO_EXCEPT;

	return pid;
}

/* new session */
auto ft::new_session(void) -> ::pid_t {

	::pid_t sid = ::setsid();

	if (sid == -1)
		throw ERRNO_EXCEPT;

	return sid;
}

/* change directory */
auto ft::change_directory(const char* path) -> void {

	if (::chdir(path) != 0)
		throw ERRNO_EXCEPT;
}


/* daemon */
auto ft::launch_daemon(void) -> void {

	// fork process
	auto pid = ft::fork();

	// return in parent process
	if (pid > 0) return;

	// create new session
	ft::new_session();

	//::umask(0);

	// change working directory
	ft::change_directory("/");

	// close descriptors
	close_descriptors();

	// redirect standard file descriptors
	//ft::unique_file stds[3] = {
	//	{"/dev/null", O_RDONLY},
	//	{"/dev/null", O_WRONLY},
	//	{"/dev/null", O_WRONLY}
	//};


	// check if server is already running
	ft::unique_file file{"/home/untitled/data/ft_matt_daemon/matt_daemon.lock", O_CREAT | O_RDWR, 0666};

	// lock file
	ft::flock_guard lock{file};

	_::signal::setup();

	// create server
	ft::server server;

	// start running
	is::running::start();

	// run server
	server.run();

}
