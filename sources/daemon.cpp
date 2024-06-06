/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:03:45 by artblin           #+#    #+#             */
/*   Updated: 2024/05/27 20:38:03 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matt_daemon/daemon.hpp"
#include "matt_daemon/diagnostics/exception.hpp"
#include "matt_daemon/server.hpp"
#include "matt_daemon/signal/signal.hpp"
#include "matt_daemon/server/unique_file.hpp"
#include "matt_daemon/flock_guard.hpp"
#include "matt_daemon/write.hpp"

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
auto ft::is_root(void) -> void {

	if (::geteuid() != 0)
		throw ft::exception{"You must be root to execute this program"};
}


/* daemon */
auto ft::launch_daemon(void) -> void {

	// check we have root privileges
	//ft::is_root();

	// fork process
	const auto pid = ft::fork();

	// return in parent process
	if (pid > 0) return;

	// create new session
	(void)ft::new_session();

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
	ft::unique_file file{
		"/mnt/nfs/homes/artblin/Desktop/ft_matt_daemon/matt.lock",
		O_CREAT | O_RDWR, 0666
	};

	// lock file
	ft::flock_guard lock{file};

	ft::signal::setup();

	// create server
	std::unique_ptr<ft::io_event> server = std::make_unique<ft::server>();

	//ft::server server;
	ft::dispatch::add(std::move(server));

	// run server
	ft::dispatch::run();
}
