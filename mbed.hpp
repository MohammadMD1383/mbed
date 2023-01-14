#include <fstream>
#include <iomanip>
#include <iostream>

#include "util.hpp"

#ifndef MBED_MBED_HPP
#define MBED_MBED_HPP

void generateFromFileToFile(
	const std::vector<std::string> &inputs,
	const std::string &output,
	const std::string &guard,
	bool headerOnly,
	bool watch
) {

}

void generateFromStdinToFile(
	const std::vector<std::string> &inputs,
	const std::string &output,
	const std::string &guard,
	bool headerOnly
) {

}

void generateFromStdinToStdout(
	const std::vector<std::string> &inputs,
	const std::string &guard,
	bool charsOnly
) {
	auto data = readStdin();
	auto last = data.back();
	data.pop_back();
	
	if (!charsOnly) {
		auto name = !inputs.empty() ? inputs[0] : "mbed";
		std::cout
			<< "#ifndef MBED_" << guard << "_H""\n"
			<< "#define MBED_" << guard << "_H""\n"
			<< "const unsigned char " << name << "[]={";
	}
	
	for (const auto &c: data) {
		std::cout << hexFor(c) << "',";
	}
	std::cout << hexFor(last) << "'";
	
	if (!charsOnly) {
		std::cout <<
		          "};" "\n"
		          "#endif";
	}
}

void generateFromFileToStdout(
	const std::vector<std::string> &inputs,
	const std::string &guard,
	bool charsOnly
) {

}

#endif //MBED_MBED_HPP
