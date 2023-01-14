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
	
	const auto &name = generateSingleName(inputs);
	if (headerOnly) {
		printVariableWithValue(outputHeaderFile, name);
	} else {
		printExternVariable(outputHeaderFile, name);
		
		std::ofstream outputCFile{output + ".c", std::ios_base::trunc};
		printVariableWithValue(outputCFile, name);
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
		printVariableWithValue(generateSingleName(inputs));
		printFooter();
	}
}

void generateFromFileToStdout(
	const std::vector<std::string> &inputs,
	const std::string &guard,
	bool charsOnly
) {
	if (!charsOnly) {
		printHeader(guard);
	}
	
	for (const auto &input: inputs) {
		std::ifstream inputFile{input, std::ios_base::binary};
		
		if (charsOnly) {
			printHexValues(inputFile);
			std::cout << "\n";
		} else {
			printVariableWithValue(inputFile, input);
			std::cout << "\n";
		}
		
		inputFile.close();
	}
	
	if (!charsOnly) {
		printFooter();
	}
}

#endif //MBED_MBED_HPP
