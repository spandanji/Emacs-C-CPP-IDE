#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>

//System compiler include paths:

std::vector<std::string> system_include_paths = {"/usr/include/c++/9.1.0/",
										 "/usr/include/c++/9.1.0/x86_64-pc-linux-gnu/"};
/*

There are 3 types of flags:
	1) Normal flags those which has the value directly appended to them like the -I include flags
	2) Newline flags which has a space after it like -c and -o
	3) Empty flags like -g

NOTE: Please don't use -c and -o flags with the clang-complete plugin because I found that it doesn't
		handle those

*/
enum class FlagProp
{
	NORMAL, NEWLINE, EMPTY,
};

/*

Flag configurations, each are sorted in ascending order of their priority

*/

struct FlagConfig
{
	std::string flag;
	int priority;
	std::set<std::string> value;
	FlagConfig(const std::string& flag, const int& priority, const std::set<std::string>& value) : flag(flag), priority(priority), value(value) {}
};

// Comparator for sorting the flags in the map

struct compare
{
	using mytype = std::pair<std::string, int>;
	bool operator()(const mytype& a, const mytype& b)
	{
		if(a.first != b.first)
			return a.second <= b.second;
		return false;
	}
};

using json = nlohmann::json;

int main(int argc, char **argv)
{

	std::unordered_map<std::string, std::pair<FlagProp, int>> flags;
	
	// Add the flags you want to add here:
	
	flags["-I"] = {FlagProp::NORMAL, 1};
	flags["-isystem"] = {FlagProp::NEWLINE, 2};
	flags["-O"] = {FlagProp::NORMAL, 3};
	flags["-g"] = {FlagProp::EMPTY, 3};
	flags["-D"] = {FlagProp::NORMAL, 4};
	flags["-std"] = {FlagProp::NORMAL, 4};
	flags["-f"] = {FlagProp::NORMAL, 4};
	flags["-W"] = {FlagProp::NORMAL, 4};

	std::map<std::pair<std::string, int>, std::set<std::string>, compare> config;
	
	for(const auto& path : system_include_paths)
		config[{"-I", flags["-I"].second}].insert("-I" + path);

	std::ifstream in(argv[1]);
	json data; in >> data;
	for(const auto& i : data)
	{
		std::stringstream sstr((std::string)i["command"]);
		for(std::string str; sstr >> str;)
			for(const auto& flag : flags)
				if(flag.first == std::string(str.begin(), str.begin() + flag.first.length()))
				{

					// Flag handling is done here

					if(flag.second.first == FlagProp::NORMAL)
					{
						config[{flag.first, flag.second.second}].insert(str);
					}
					else if(flag.second.first == FlagProp::NEWLINE)
					{
						sstr >> str;
						config[{flag.first, flag.second.second}].insert(flag.first + "\n" + str);
					}
					else if(flag.second.first == FlagProp::EMPTY)
					{
						config[{flag.first, flag.second.second}].insert(flag.first);
					}
				}
	}
	for(const auto& i : config)
	{
		for(const auto& j : i.second)
			std::cout << j << '\n';
	}
}