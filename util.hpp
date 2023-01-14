#include <deque>
#include <sstream>
#include <iomanip>
#include <iostream>

#ifndef MBED_UTIL_HPP
#define MBED_UTIL_HPP

std::string hexFor(const unsigned char c) {
	std::stringstream str{};
	str << std::hex << std::uppercase << std::setfill('0') << std::right;
	str << "'\\x" << std::setw(2) << +c << "'";
	return str.str();
}

void printHexValues(std::istream &is, std::ostream &os) {
	char c;
	while (true) {
		is.get(c);
		
		if (is.peek() != -1) {
			os << hexFor(c) << ',';
			continue;
		}
		
		os << hexFor(c);
		break;
	}
}

void printHexValues(std::istream &is) {
	printHexValues(is, std::cout);
}

void printHexValues(std::ostream &os) {
	printHexValues(std::cin, os);
}

void printHexValues() {
	printHexValues(std::cin, std::cout);
}

void printVariable(
	std::ostream &os,
	const std::vector<std::string> &inputs
) {
	auto name = !inputs.empty() ? inputs[0] : "mbed";
	os << "const char " << name << "[]";
}

void printVariable(const std::vector<std::string> &inputs) {
	printVariable(std::cout, inputs);
}

void printExternVariable(std::ostream &os, const std::vector<std::string> &inputs) {
	os << "extern ";
	printVariable(os, inputs);
	os << ";";
}

void printVariableWithValue(std::ostream &os, const std::vector<std::string> &inputs) {
	printVariable(os, inputs);
	os << "={";
	printHexValues(os);
	os << "};";
}

void printVariableWithValue(const std::vector<std::string> &inputs) {
	printVariableWithValue(std::cout, inputs);
}

void printHeader(
	std::ostream &os,
	const std::string &guard
) {
	os << "#ifndef MBED_" << guard << "_H""\n"
	   << "#define MBED_" << guard << "_H""\n";
}

void printHeader(const std::string &guard) {
	printHeader(std::cout, guard);
}

void printFooter(std::ostream &os) {
	os << "\n"
	      "#endif";
}

void printFooter() {
	printFooter(std::cout);
}

#endif //MBED_UTIL_HPP
