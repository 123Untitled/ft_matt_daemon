/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:03:45 by artblin           #+#    #+#             */
/*   Updated: 2024/06/15 18:49:14 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matt_daemon/daemon.hpp"
#include "matt_daemon/diagnostics/exception.hpp"
#include "matt_daemon/server.hpp"
#include "matt_daemon/signal/signal.hpp"
#include "matt_daemon/server/unique_file.hpp"
#include "matt_daemon/flock_guard.hpp"
#include "matt_daemon/delete_guard.hpp"

#include <unistd.h>
#include <sys/stat.h>

#include <cstring>
#include <sys/file.h>
#include <sys/types.h>

#include <iostream>


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

/* is root */
auto ft::is_root(void) -> bool {
	return ::geteuid() == 0;
}


/* daemon */
auto ft::launch_daemon(void) -> void {

	// check we have root privileges
	if (not ft::is_root()) {
		std::cerr << "daemon must be run as root" << std::endl;
		return;
	}

	const char* const dirs[] {
		"/var/log/matt_daemon",
		"/var/lock"
	};

	for (const char* dir : dirs) {
		// check if directory exists
		struct stat st;
		if (::stat(dir, &st) == -1) {
			if (::mkdir(dir, 0755) == -1) {
				std::cerr << "mkdir failed: " << dir << std::endl;
				return; }
		}
	}


	// fork process
	const auto pid = ft::fork();

	// return in parent process
	if (pid > 0) return;

	// create new session
	static_cast<void>(ft::new_session());


	// second fork
	if (ft::fork() > 0) return;

	// set file mode creation mask
	umask(0);


	// change working directory
	ft::change_directory("/");

	// close descriptors
	close_descriptors();


	const char* path = "/var/lock/matt_daemon.lock";

	// check if server is already running
	ft::unique_file file{
		path,
		O_CREAT | O_RDWR, 0700
	};

	// delete lock file on exit
	ft::delete_guard guard{path};

	// lock file
	ft::flock_guard lock{file};

	// setup signals
	ft::signal::setup();

	// create server
	std::unique_ptr<ft::io_event> server = std::make_unique<ft::server>();

	//ft::server server;
	ft::dispatch::add(std::move(server));

	// run server
	ft::dispatch::run();
}
