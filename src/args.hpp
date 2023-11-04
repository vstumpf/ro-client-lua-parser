#pragma once

#include <string>

class Arguments {
   public:
	std::string base_directory_;
	std::string iteminfo_filename_;
};

Arguments parseArguments(int argc, const char** argv);
