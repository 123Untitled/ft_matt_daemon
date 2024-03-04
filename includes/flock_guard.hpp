/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flock_guard.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:36:12 by artblin           #+#    #+#             */
/*   Updated: 2024/03/04 22:40:39 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FT_FLOCK_GUARD_HPP
#define FT_FLOCK_GUARD_HPP


// -- F T  N A M E S P A C E --------------------------------------------------

namespace ft {

	// -- forward declarations ------------------------------------------------

	/* unique_file */
	class unique_file;


	// -- F L O C K  G U A R D ------------------------------------------------

	class flock_guard final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = ft::flock_guard;


			// -- public lifecycle --------------------------------------------

			/* unique_file constructor */
			flock_guard(const ft::unique_file&);

			/* deleted copy constructor */
			flock_guard(const self&) = delete;

			/* deleted move constructor */
			flock_guard(self&&) = delete;

			/* destructor */
			~flock_guard(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


		private:

			// -- private members ---------------------------------------------

			/* file */
			const ft::unique_file& _file;

	}; // class flock_guard

} // namespace ft

#endif // FT_FLOCK_GUARD_HPP


// LOCK_SH  Place a shared lock.  More than one process may hold a shared lock for a given file at a given time.
// LOCK_EX  Place an exclusive lock.  Only one process may hold an exclusive lock for a given file at a given time.
// LOCK_UN  Remove an existing lock held by this process.

// flock() may block if an incompatible lock is held by another process.  To make a nonblocking request, include LOCK_NB (by ORing) with any of the above operations.
// A single file may not simultaneously have both shared and exclusive locks.
// Locks created by flock() are associated with an open file description (see open(2)).  This means that duplicate file descriptors (created by, for example, fork(2) or dup(2)) refer to the same lock, and this lock may be modified or released using any of these file descriptors.  Furthermore, the lock is released either by an explicit LOCK_UN operation on any of these duplicate file descriptors, or when all such file descriptors have been closed.
// If a process uses open(2) (or similar) to obtain more than one file descriptor for the same file, these file descriptors are treated independently by flock().  An attempt to lock the file using one of these file descriptors may be denied by a lock that the calling process has already placed via another file descriptor.
// A process may hold only one type of lock (shared or exclusive) on a file.  Subsequent flock() calls on an already locked file will convert an existing lock to the new lock mode.
// Locks created by flock() are preserved across an execve(2).
// A shared or exclusive lock can be placed on a file regardless of the mode in which the file was opened.
