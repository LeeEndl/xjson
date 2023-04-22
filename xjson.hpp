#pragma once
#define OBJECTS 14000
#include <iostream>

#include <string>
#include <vector>
std::vector<std::string> index(std::string str, std::string delimiter) {
	std::vector<std::string> buffer;
	long long strleng = str.length(), delleng = delimiter.length(), i = 0, k = 0;
	if (delleng == 0) return buffer;
	while (i < strleng) {
		int j = 0;
		while (i + j < strleng && j < delleng && str[i + j] == delimiter[j]) j++;
		if (j == delleng) buffer.push_back(str.substr(k, i - k)), i += delleng, k = i;
		else i++;
	}
	buffer.push_back(str.substr(k, i - k));
	return buffer;
}

#include <map>
#include <fstream>
#include <thread>

template<typename t> using tmap = std::map<std::string, t>;
template<typename t> using groups = std::map<std::string, tmap<t>>;

class xjson {
public:
	template<typename t> inline xjson& write(std::map<std::string, t> map, const char* file) {
		std::ofstream write(file);
		for (auto& obj : map) write << "{ " << obj.first + ", " + std::to_string(obj.second) << " } ";
		return *this;
	}
	inline std::map<std::string, std::string> string(const char* file) {
		std::string line = "";
		std::ifstream read(file);
		std::getline(read, line);
		tmap<std::string> map;
		for (int i = 0; i < OBJECTS; i++) {
			if (index(line, ", ")[i].empty() or index(line, ", ")[(size_t)i + 1].empty()) break;
			std::string key = index(line, ", ")[i];
			std::string value = index(line, ", ")[i + 1];
			if (index(line, ", ")[i].find(" {") not_eq -1) map.emplace(key.substr(6, key.size()), value.substr(0, 2));
			else map.emplace(key.substr(2, key.size()), value.substr(0, 2));
		}
		return map;
	}
	template<typename t> inline std::map<std::string, t> Int(const char* file) {
		std::string line = "";
		std::ifstream read(file);
		std::getline(read, line);
		tmap<t> map;
		for (int i = 0; i < OBJECTS; i++) {
			if (index(line, ", ")[i].empty() or index(line, ", ")[i + 1].empty()) break;
			std::string key = index(line, ", ")[i];
			std::string value = index(line, ", ")[i + 1];
			if (index(line, ", ")[i].find(" {") not_eq -1) map.emplace(key.substr(6, key.size()), stoull(value.substr(0, 2)));
			else map.emplace(key.substr(2, key.size()), stoull(value.substr(0, 2)));
		}
		return map;
	}
	class group {
	public:
		template<typename t> inline group& write(std::map<std::string, std::map<std::string, t>> map, const char* file) {
			std::ofstream write(file);
			for (auto& labels : map) {
				write << labels.first << " { ";
				for (auto& it : labels.second) write << " { " << it.first + ", " + std::to_string(it.second) << " }";
				write << "  } \n";
			}
			return *this;
		}
		template<typename t> inline std::map<std::string, t> string(std::string label, const char* file) {
			std::string line = "";
			std::ifstream read(file);
			while (std::getline(read, line)) if (line.find(label + " {") not_eq -1) {
				line.resize(line.size() - 3);
				line = line.substr(label.size() + 4, line.size());
				tmap<t> map;
				for (int i = 0; i < OBJECTS; i++) {
					if (index(line, ", ")[i].empty() or index(line, ", ")[i + 1].empty()) break;
					std::string key = index(line, ", ")[i];
					std::string value = index(line, ", ")[i + 1];
					std::string nkey = index(value, " }")[1];
					if (index(line, ", ")[i].find(" {") not_eq -1) map.emplace(key.substr(6, key.size()), value.substr(0, value.size() - nkey.size() - 2));
					else map.emplace(key.substr(2, key.size()), value.substr(0, value.size() - nkey.size() - 2));
				}
				return map;
			}
		}
		template<typename t> inline std::map<std::string, t> Int(std::string label, const char* file) {
			std::string line = "";
			std::ifstream read(file);
			while (std::getline(read, line)) if (line.find(label + " {") not_eq -1) {
				line.resize(line.size() - 3);
				line = line.substr(label.size() + 4, line.size());
				tmap<t> map;
				for (int i = 0; i < OBJECTS; i++) {
					if (index(line, ", ")[i].empty() or index(line, ", ")[i + 1].empty()) break;
					std::string key = index(line, ", ")[i];
					std::string value = index(line, ", ")[i + 1];
					if (index(line, ", ")[i].find(" {") not_eq -1) map.emplace(key.substr(6, key.size()), stoull(value.substr(0, value.size() - 3)));
					else map.emplace(key.substr(2, key.size()), stoull(value.substr(0, value.size() - 3)));
				}
				return map;
			}
		}
	};
};