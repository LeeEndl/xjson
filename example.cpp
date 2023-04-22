#include "xjson.hpp"

int main() {
	xjson::group().write(groups<std::string>{ {
			"group_name",
			{
				{ "key", "value" },
				{ "another_key", "another_value" }
			}
		}/*another group here*/}, "group.txt");
	// group.txt ->  group_name { { key, value } { another_key, value } }
	
	/* reading groups */
	for (auto& it : xjson::group().Int<int>("group_name", "test.txt")) 
		if (it.first == "key") it.second; // -> it.first = key; it.second = value

	
	xjson().write(tmap<std::string>{"key", "value"}, "basic.txt");
	// basic.txt -> { key, value }
	
	/* reading basic key n value (s) */
	for (auto& it : xjson().Int<int>("key", "test.txt")) it.second; // -> it.first = key; it.second = value
	return 0;
}
