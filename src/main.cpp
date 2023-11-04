#include <iostream>
#include <sol/sol.hpp>

int parseItemInfo(std::string filename) {
	std::cout << "Parsing item info from " << filename << "\n";

	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::package);

	lua.script_file(filename);
	// pcall(AddItem, ItemID, DESC.unidentifiedDisplayName, DESC.unidentifiedResourceName,
	// DESC.identifiedDisplayName, DESC.identifiedResourceName, DESC.slotCount, DESC.ClassNum)
	lua["AddItem"] = [](uint32_t itemid, std::string unid_name, std::string unid_resc,
						std::string id_name, std::string id_resc, uint32_t slot_count,
						uint32_t class_num) {
		std::cout << "AddItem(" << itemid << ", " << unid_name << ", " << unid_resc << ", "
				  << id_name << ", " << id_resc << ", " << slot_count << ", " << class_num << ")\n";
		return std::tuple<bool, std::string>(true, "");
	};

	lua["AddItemUnidentifiedDesc"] = [](uint32_t itemid, std::string description) {
		return std::tuple<bool, std::string>(true, "");
	};

	lua["AddItemIdentifiedDesc"] = [](uint32_t itemid, std::string description) {
		return std::tuple<bool, std::string>(true, "");
	};

	auto result = lua.script("main()");

	if (!result.valid()) {
		sol::error err = result;
		std::cout << err.what();
	}

	return 0;
}

int main(int argc, const char** argv) {
	std::cout << "Hello, from C++\n";
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::package);
	sol::protected_function_result result = lua.script("print('Hello from Lua')");
	if (!result.valid()) {
		sol::error err = result;
		std::cout << err.what();
	}

	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " <filename>\n";
		return 1;
	}

	return parseItemInfo(argv[1]);
}
