#include "args.hpp"

#include <iostream>

#include <cxxopts.hpp>

Arguments parseArguments(int argc, const char** argv) {
	Arguments args;

	cxxopts::Options options("ro-client-lua-parser", "Parse iteminfo.lua files for rAthena");
	// clang-format off
	options.add_options()
		("b,base-directory", "Base directory", cxxopts::value<std::string>())
		("i,iteminfo", "Iteminfo filename", cxxopts::value<std::string>())
		("h,help", "Print help")
	;
	// clang-format on

	auto result = options.parse(argc, argv);

	if (result.count("help")) {
		std::cout << options.help() << std::endl;
		exit(0);
	}

	if (result.count("base-directory")) {
		args.base_directory_ = result["base-directory"].as<std::string>();
	} else {
		args.base_directory_ = ".";
	}

	if (result.count("iteminfo")) {
		args.iteminfo_filename_ = result["iteminfo"].as<std::string>();
	} else {
		args.iteminfo_filename_ = "iteminfo.lua";
	}

	return args;
}
