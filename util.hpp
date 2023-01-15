#include <deque>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <boost/filesystem.hpp>

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
	const std::string &name
) {
	os << "const char " << name << "[]";
}

void printVariable(const std::string &name) {
	printVariable(std::cout, name);
}

void printExternVariable(
	std::ostream &os,
	const std::string &name
) {
	os << "extern ";
	printVariable(os, name);
	os << ";";
}

void printVariableWithValue(
	std::istream &is,
	std::ostream &os,
	const std::string &name
) {
	printVariable(os, name);
	os << "={";
	printHexValues(is, os);
	os << "};";
}

void printVariableWithValue(
	std::istream &is,
	const std::string &name
) {
	printVariableWithValue(is, std::cout, name);
}

void printVariableWithValue(
	std::ostream &os,
	const std::string &name
) {
	printVariableWithValue(std::cin, os, name);
}

void printVariableWithValue(const std::string &name) {
	printVariableWithValue(std::cin, std::cout, name);
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

std::string extractNameFromPath(const boost::filesystem::path &p) {
	auto name = p.stem().string();
	
	std::replace_if(name.begin(), name.end(), [](const auto &c) {
		return !std::isalnum(c);
	}, '_');
	
	if (isdigit(name[0])) {
		name.insert(0, "_");
	}
	
	return name;
}

std::string generateSingleName(const std::vector<std::string> &inputs) {
	return inputs.empty() ? "mbed" : extractNameFromPath(inputs[0]);
}

#endif //MBED_UTIL_HPP
