#include "xjson.hpp"

int main() {
	xjson::group().write(groups<std::string>{ {
			"group_name",
			{
				{ "key", "value" },
				{ "another_key", "another_value" }
			}
		}/*another group here*/}, "group.txt");

	xjson().write(tmap<std::string>{"key", "value"}, "basic.txt");

	for (auto& it : xjson::group().Int<int>("key", "test.txt")) it.second; // -> the value;
	return 0;
}
