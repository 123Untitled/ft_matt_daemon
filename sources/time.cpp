#include "time.hpp"
#include "exception.hpp"

#include <time.h>


/* time */
auto ft::time(void) -> const char* {

	static char buffer[] {
		'[',
		'D', 'D',
		'/',
		'M', 'M',
		'/',
		'Y', 'Y', 'Y', 'Y',
		'-',
		'H', 'H',
		':',
		'M', 'M',
		':',
		'S', 'S',
		']',
		'\0'
	};


	/* time */
	const ::time_t now = ::time(nullptr);

	/* time info */
	const ::tm* const time = ::localtime(&now);


	if (time == nullptr)
		throw ft::exception{"time: failed to get time info"};

	int value;

	/* day [1 - 2] */
	value = time->tm_mday;
	buffer[ 1] = static_cast<char>(value / 10) + '0';
	buffer[ 2] = static_cast<char>(value % 10) + '0';

	/* month [4 - 5] */
	value = time->tm_mon + 1;
	buffer[ 4] = static_cast<char>(value / 10) + '0';
	buffer[ 5] = static_cast<char>(value % 10) + '0';

	/* year [7 - 10] */
	value = time->tm_year + 1900;
	buffer[ 7] = static_cast<char> (value / 1000) + '0';
	buffer[ 8] = static_cast<char>((value /  100) % 10) + '0';
	buffer[ 9] = static_cast<char>((value /   10) % 10) + '0';
	buffer[10] = static_cast<char> (value %   10) + '0';

	/* hour [12 - 13] */
	value = time->tm_hour;
	buffer[12] = static_cast<char>(value / 10) + '0';
	buffer[13] = static_cast<char>(value % 10) + '0';

	/* minute [15 - 16] */
	value = time->tm_min;
	buffer[15] = static_cast<char>(value / 10) + '0';
	buffer[16] = static_cast<char>(value % 10) + '0';

	/* second [18 - 19] */
	value = time->tm_sec;
	buffer[18] = static_cast<char>(value / 10) + '0';
	buffer[19] = static_cast<char>(value % 10) + '0';


	return buffer;
}
