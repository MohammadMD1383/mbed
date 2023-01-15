#include <iostream>
#include <termcolor/termcolor.hpp>
#include <boost/program_options.hpp>
#include <boost/exception/diagnostic_information.hpp>

#ifdef WINDOWS
																														
#include <conio.h>
#include <fcntl.h>

#endif

#include "mbed.hpp"
#include "resource/mbed_examples.h"

using namespace std;
using namespace termcolor;
using namespace boost::filesystem;
using namespace boost::program_options;

using boost::current_exception_diagnostic_information;

int main(int argc, char *argv[]) {
	ios_base::sync_with_stdio(false);

#ifdef WINDOWS
	_setmode(_fileno(stdin), O_BINARY);
#else
	freopen(nullptr, "rb", stdin);
#endif
	
	options_description description{
		""
		"+--------------------------------------------+" "\n"
		"|               --<* MBed *>--               |" "\n"
		"| lets you embed any file in a c/c++ program |" "\n"
		"|       using a generated header file.       |" "\n"
		"+--------------------------------------------+" "\n\n"
		"Options"
	};
	
	description.add_options()
		("input,i", value<vector<string>>()->multitoken()->default_value({}, ""), "file(s) to generate embeddable data for")
		("output,o", value<string>(), "output name for '.c' and '.h' files")
		("header-guard,g", value<string>()->default_value(""), "name of the header guard for the generated '.h' file")
		("header-only,H", "produce only a header file (without a '.c' source file")
		("stdin,s", "read data from stdin and output to stdout if the <output> arg is not specified")
		("stdout,S", "output generated data to stdout even if the <output> arg is present")
		("chars-only,c", "output only generated characters instead of a 'c' file content")
		("help,h", "print this help message")
		("examples,e", "print examples")
		("version,v", "print version info");
	
	positional_options_description positional{};
	positional.add("output", 1);
	positional.add("input", -1);
	
	variables_map vmap{};
	store(
		command_line_parser{argc, argv}
			.options(description)
			.positional(positional)
			.run(),
		vmap
	);
	
	if (vmap.contains("help")) {
		cout << description << endl;
		return 0;
	}
	
	if (vmap.contains("examples")) {
		cout << examples << endl;
		return 0;
	}
	
	if (vmap.contains("version")) {
		cout << "MBed v" MBED_VERSION " by MMD" << endl;
		return 0;
	}
	
	try {
		notify(vmap);
		
		const auto inputFromStdin = vmap.contains("stdin") || !vmap.contains("input");
		const auto outputToStdout = vmap.contains("stdout") || !vmap.contains("output");
		const auto &guard = vmap["header-guard"].as<string>();
		const auto &inputs = vmap["input"].as<vector<string>>();
		
		if (outputToStdout) {
			const auto charsOnly = vmap.contains("chars-only");
			
			if (inputFromStdin) {
				generateFromStdinToStdout(
					inputs,
					guard,
					charsOnly
				);
			} else {
				generateFromFileToStdout(
					inputs,
					guard,
					charsOnly
				);
			}
		} else {
			const auto &output = vmap["output"].as<string>();
			const auto headerOnly = vmap.contains("header-only");
			
			if (inputFromStdin) {
				generateFromStdinToFile(
					inputs,
					output,
					guard,
					headerOnly
				);
			} else {
				generateFromFileToFile(
					inputs,
					output,
					guard,
					headerOnly
				);
			}
		}
	} catch (...) {
		cerr << endl << red
		     << "[ERROR]"
		     << endl
		     << current_exception_diagnostic_information()
		     << reset << endl;
		
		return 1;
	}
	
	return 0;
}
