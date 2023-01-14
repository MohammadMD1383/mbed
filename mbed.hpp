#include <fstream>
#include <iomanip>
#include <iostream>
#include <termcolor/termcolor.hpp>

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
	throw "Not Implemented";
}

void generateFromStdinToFile(
	const std::vector<std::string> &inputs,
	const std::string &output,
	const std::string &guard,
	bool headerOnly
) {
	std::ofstream outputHeaderFile{output + ".h", std::ios_base::trunc};
	printHeader(outputHeaderFile, guard);
	
	if (headerOnly) {
		printVariableWithValue(outputHeaderFile, inputs);
	} else {
		printExternVariable(outputHeaderFile, inputs);
		
		std::ofstream outputCFile{output + ".c", std::ios_base::trunc};
		printVariableWithValue(outputCFile, inputs);
		outputCFile.close();
	}
	
	printFooter(outputHeaderFile);
	outputHeaderFile.close();
}

void generateFromStdinToStdout(
	const std::vector<std::string> &inputs,
	const std::string &guard,
	bool charsOnly
) {
	if (charsOnly) {
		printHexValues();
	} else {
		printHeader(guard);
		printVariableWithValue(inputs);
		printFooter();
	}
}

void generateFromFileToStdout(
	const std::vector<std::string> &inputs,
	const std::string &guard,
	bool charsOnly
) {

}

#endif //MBED_MBED_HPP
