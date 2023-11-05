#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>
#include <sol/sol.hpp>

#include "args.hpp"
#include "codec.hpp"

using json = nlohmann::json;

int parseItemInfo(std::string filename) {
	std::cout << "Parsing item info from " << filename << "\n";

	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::package);

	lua.script_file(filename);

	json j;
	j["iteminfo"] = json::object();

	// pcall(AddItem, ItemID, DESC.unidentifiedDisplayName, DESC.unidentifiedResourceName,
	// DESC.identifiedDisplayName, DESC.identifiedResourceName, DESC.slotCount, DESC.ClassNum)
	lua["AddItem"] = [&j](uint32_t itemid, std::string unid_name, std::string unid_resc,
						  std::string id_name, std::string id_resc, uint32_t slot_count,
						  uint32_t class_num) {
		// std::cout << "AddItem(" << itemid << ", " << unid_name << ", " << unid_resc << ", "
		// 		  << id_name << ", " << id_resc << ", " << slot_count << ", " << class_num <<
		// ")\n";

		json::object_t item;

		j["iteminfo"][std::to_string(itemid)] = {{"id", itemid},
												 {"unid_name", decode1252(unid_name)},
												 {"unid_resc", decode1252(unid_resc)},
												 {"id_name", decode1252(id_name)},
												 {"id_resc", decode1252(id_resc)},
												 {"slot_count", slot_count},
												 {"class_num", class_num},
												 {"unid_desc", json::array()},
												 {"id_desc", json::array()}};

		return std::tuple<bool, std::string>(true, "");
	};

	lua["AddItemUnidentifiedDesc"] = [&j](uint32_t itemid, std::string description) {
		try {
			j["iteminfo"][std::to_string(itemid)]["unid_desc"].push_back(decode1252(description));
		} catch (std::exception& e) {
			std::cout << itemid << "" << description << "\n";
			std::cout << e.what() << "\n";
		}
		return std::tuple<bool, std::string>(true, "");
	};

	lua["AddItemIdentifiedDesc"] = [&j](uint32_t itemid, std::string description) {
		try {
			j["iteminfo"][std::to_string(itemid)]["id_desc"].push_back(decode1252(description));
		} catch (std::exception& e) {
			std::cout << description << "\n";
			std::cout << e.what() << "\n";
		}

		return std::tuple<bool, std::string>(true, "");
	};

	lua["AddItemIsCostume"] = [](uint32_t itemid, bool is_costume) {
		return std::tuple<bool, std::string>(true, "");
	};

	lua["AddItemEffectInfo"] = [](uint32_t itemid, uint32_t effect_id) {
		return std::tuple<bool, std::string>(true, "");
	};

	auto result = lua.script("main()");

	if (!result.valid()) {
		sol::error err = result;
		std::cout << err.what();
	}

	std::ofstream("iteminfo.json") << j.dump(2);

	return 0;
}

int main(int argc, const char** argv) {
	auto args = parseArguments(argc, argv);

	return parseItemInfo(args.iteminfo_filename_);
}
