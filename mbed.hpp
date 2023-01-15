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
	bool headerOnly
) {
	std::ofstream outputHeaderFile{output + ".h", std::ios_base::trunc};
	printHeader(outputHeaderFile, guard);
	
	if (headerOnly) {
		for (const auto &input: inputs) {
			std::ifstream inputFile{input, std::ios_base::binary};
			printVariableWithValue(inputFile, outputHeaderFile, input);
			inputFile.close();
		}
	} else {
		std::ofstream outputCFile{output + ".c", std::ios_base::trunc};
		
		for (const auto &input: inputs) {
			std::ifstream inputFile{input, std::ios_base::binary};
			printExternVariable(outputHeaderFile, input);
			printVariableWithValue(inputFile, outputCFile, input);
			inputFile.close();
		}
		
		outputCFile.close();
	}
	
	printFooter(outputHeaderFile);
	outputHeaderFile.close();
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
		}
		
		inputFile.close();
	}
	
	if (!charsOnly) {
		printFooter();
	}
}

#endif //MBED_MBED_HPP
