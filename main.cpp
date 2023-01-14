#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <termcolor/termcolor.hpp>
#include <boost/program_options.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include "mbed.hpp"

using namespace std;
using namespace boost;
using namespace termcolor;
using namespace boost::filesystem;
using namespace boost::program_options;

int main(int argc, char *argv[]) {
	options_description description{
		""
		"+--------------------------------------------+"
		"|               --<* MBed *>--               |" "\n"
		"| lets you embed any file in a c/c++ program |"
		"|       using a generated header file.       |" "\n"
		"+--------------------------------------------+"
	};
	
	description.add_options()
		("input,i", value<vector<string>>(), "file(s) to generate embeddable data for")
		("output,o", value<string>(), "output name for '.c' and '.h' files")
		("header-only,H", "produce only a header file (without a '.c' source file")
		("stdin,s", "read data from stdin and output to stdout if the <output> arg is not specified")
		("stdout,S", "output generated data to stdout even if the <output> arg is present")
		("chars-only,c", "output only generated characters instead of a 'c' file content")
		("watch,w", "watch input file(s) for changes and reproduce the header")
		("help,h", "print this help message")
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
	
	if (vmap.contains("version")) {
		cout << "MBed v" MBED_VERSION " by MMD" << endl;
		return 0;
	}
	
	try {
		notify(vmap);
	} catch (...) {
		cerr << red <<
		     "error: " << current_exception_diagnostic_information()
		     << endl;
		
		return 1;
	}
	
	// if () {
	//
	// }
	
	return 0;
}
