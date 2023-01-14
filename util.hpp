#include <iostream>
#include <deque>

#ifndef MBED_UTIL_HPP
#define MBED_UTIL_HPP

std::deque<unsigned char> readStdin() {
	std::deque<unsigned char> data{};
	
	char tmp;
	while (!std::cin.get(tmp).eof()) {
		data.push_back(tmp);
	}
	
	return data;
}

#endif //MBED_UTIL_HPP
