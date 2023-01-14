#include <deque>
#include <sstream>
#include <iomanip>
#include <iostream>

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

std::string hexFor(unsigned char c) {
	std::stringstream str{};
	str << std::hex << std::uppercase << std::setfill('0') << std::right;
	str << "'\\x" << std::setw(2) << +c << "'";
	return str.str();
}

#endif //MBED_UTIL_HPP
