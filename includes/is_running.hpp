#ifndef IS_RUNNING_HPP
#define IS_RUNNING_HPP


class signal;

// -- I S  N A M E S P A C E --------------------------------------------------

namespace is {

	/* is: namespace for global variables
	 * running: global running flag
	 * need to be friend of all classes that need to know if the server is running
	 * (atomic access to the flag)
	 */

	// -- R U N N I N G -------------------------------------------------------

	class running final {


		// -- friends ---------------------------------------------------------

		/* signal as friend */
		friend class ::signal;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = is::running;


			// -- public static methods ---------------------------------------

			/* state */
			static inline auto state(void) noexcept -> bool {
				return __atomic_load_n(&self::shared()._running, __ATOMIC_SEQ_CST);
			}

			/* toggle */
			static inline auto toggle(void) noexcept -> void {
				__atomic_store_n(&self::shared()._running,
								not self::shared()._running, __ATOMIC_SEQ_CST);
			}

			/* start */
			static inline auto start(void) noexcept -> void {
				__atomic_store_n(&self::shared()._running, true, __ATOMIC_SEQ_CST);
			}

			/* stop */
			static inline auto stop(void) noexcept -> void {
				__atomic_store_n(&self::shared()._running, false, __ATOMIC_SEQ_CST);
			}


		private:

			// -- private lifecycle -------------------------------------------

			/* default constructor */
			inline constexpr running(void) noexcept
			: _running{false} {}

			/* deleted copy constructor */
			running(const self&) = delete;

			/* deleted move constructor */
			running(self&&) = delete;

			/* destructor */
			~running(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- private static methods --------------------------------------

			/* shared */
			static inline auto shared(void) noexcept -> self& {
				static self instance;
				return instance;
			}


			// -- private members ---------------------------------------------

			/* is running flag */
			bool _running;

	}; // class is_running

} // namespace is


#include <unistd.h>
#include <signal.h>

class signal final {

	public:

		signal(void) noexcept {


		}


	private:


		/* default */
		template <int... S>
		inline auto set_default(void) -> void {
			((::signal(S, SIG_DFL) == SIG_ERR ? throw : 0), ...);
		}

		/* ignore */
		template <int... S>
		inline auto set_ignore(void) -> void {
			((::signal(S, SIG_IGN) == SIG_ERR ? throw : 0), ...);
		}

		/* handler */
		template <int... S>
		inline auto set_handler(void) -> void {
			((::signal(S, &signal::handler) == SIG_ERR ? throw : 0), ...);
		}


		// -- private signal handlers -----------------------------------------

		/* handler */
		static auto handler(int sig) noexcept -> void {
			// ...
		}


		void setup(void) {

			set_default<SIGSEGV,
						SIGILL,
						SIGFPE,
						SIGABRT,
						SIGBUS,
						SIGTRAP,
						SIGSYS,
						SIGXCPU,
						SIGXFSZ>();

			set_handler<SIGINT,
						SIGHUP,
						SIGQUIT,
						SIGTERM>();

			set_ignore<SIGPIPE,
						SIGALRM,
						SIGCHLD,
						SIGCONT,
						SIGSTOP,
						SIGTSTP,
						SIGTTIN,
						SIGTTOU,
						SIGURG,
						SIGVTALRM,
						SIGPROF,
						SIGWINCH,
						SIGIO>();


		}







};





#endif // IS_RUNNING_HPP









/*
SIGHUP If a process is being run from terminal and that terminal suddenly goes
away then the process receives this signal. “HUP” is short for “hang up”
and refers to hanging up the telephone in the days of telephone modems.

SIGINT The process was “interrupted”. This happens when you press Control+C on
the controlling terminal.

SIGQUIT

SIGILL Illegal instruction. The program contained some machine code the CPU
can't understand.

SIGTRAP This signal is used mainly from within debuggers and program tracers.

SIGABRT The program called the abort() function. This is an emergency stop.

SIGBUS An attempt was made to access memory incorrectly. This can be caused by
alignment errors in memory access etc.

SIGFPE A floating point exception happened in the program.

SIGKILL The process was explicitly killed by somebody wielding the kill
program.

SIGUSR1 Left for the programmers to do whatever they want.

SIGSEGV An attempt was made to access memory not allocated to the process. This
is often caused by reading off the end of arrays etc.

SIGUSR2 Left for the programmers to do whatever they want.

SIGPIPE If a process is producing output that is being fed into another process that
consume it via a pipe (“producer | consumer”) and the consumer
dies then the producer is sent this signal.

SIGALRM A process can request a “wake up call” from the operating system at some
time in the future by calling the alarm() function. When that time comes
round the wake up call consists of this signal.

SIGTERM The process was explicitly killed by somebody wielding the kill
program.

SIGCHLD The process had previously created one or more child processes with the
fork() function. One or more of these processes has since died.

SIGCONT (To be read in conjunction with SIGSTOP.)
If a process has been paused by sending it SIGSTOP then sending

SIGCONT to the process wakes it up again (“continues” it).

SIGSTOP (To be read in conjunction with SIGCONT.)
If a process is sent SIGSTOP it is paused by the operating system. All its
No. Short name What it means
state is preserved ready for it to be restarted (by SIGCONT) but it doesn't
get any more CPU cycles until then.

SIGTSTP Essentially the same as SIGSTOP. This is the signal sent when the user hits
Control+Z on the terminal. (SIGTSTP is short for “terminal stop”) The
only difference between SIGTSTP and SIGSTOP is that pausing is
only the default action for SIGTSTP but is the required action for

SIGSTOP. The process can opt to handle SIGTSTP differently but gets no
choice regarding SIGSTOP.

SIGTTIN The operating system sends this signal to a backgrounded process when it
tries to read input from its terminal. The typical response is to pause (as per
SIGSTOP and SIFTSTP) and wait for the SIGCONT that arrives when the
process is brought back to the foreground.

SIGTTOU The operating system sends this signal to a backgrounded process when it
tries to write output to its terminal. The typical response is as per
SIGTTIN.

SIGURG The operating system sends this signal to a process using a network
connection when “urgent” out of band data is sent to it.

SIGXCPU The operating system sends this signal to a process that has exceeded its
CPU limit. You can cancel any CPU limit with the shell command
“ulimit -t unlimited” prior to running make though it is more
likely that something has gone wrong if you reach the CPU limit in make.

SIGXFSZ The operating system sends this signal to a process that has tried to create a
file above the file size limit. You can cancel any file size limit with the
shell command “ulimit -f unlimited” prior to running make though it is
more likely that something has gone wrong if you reach the file size limit
in make.

SIGVTALRM This is very similar to SIGALRM, but while SIGALRM is sent after a
certain amount of real time has passed, SIGVTALRM is sent after a certain
amount of time has been spent running the process.

SIGPROF This is also very similar to SIGALRM and SIGVTALRM, but while
SIGALRM is sent after a certain amount of real time has passed, SIGPROF
is sent after a certain amount of time has been spent running the process
and running system code on behalf of the process.

SIGWINCH (Mostly unused these days.) A process used to be sent this signal when one
of its windows was resized.

SIGIO (Also known as SIGPOLL.) A process can arrange to have this signal sent
to it when there is some input ready for it to process or an output channel
has become ready for writing.

SIGPWR A signal sent to processes by a power management service to indicate that
power has switched to a short term emergency power supply. The process
(especially long-running daemons) may care to shut down cleanlt before
the emergency power fails.

SIGSYS Unused
*/
