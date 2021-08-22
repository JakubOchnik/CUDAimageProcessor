#pragma once
#include <unordered_map>
#include <vector>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/trim.hpp >

namespace Utils
{
	template<typename mapType>
	std::vector<typename mapType::key_type> keys(const mapType& inputMap)
	{
		std::vector<typename mapType::key_type> keysVec;
		keysVec.reserve(inputMap.size());
		for (const auto& kvp : inputMap)
		{
			keysVec.emplace_back(kvp.first);
		}
		return keysVec;
	}

	template<typename mapType>
	std::vector<typename mapType::mapped_type> values(const mapType& m)
	{
		std::vector<typename mapType::mapped_type> keysVec;
		keysVec.reserve(m.size());
		for (const auto& kvp : m)
		{
			keysVec.emplace_back(kvp.second);
		}
		return keysVec;
	}
}

namespace TextUtils
{
	inline std::vector<std::string> tokenize(std::string line, const char* separator = " ")
	{
		using namespace boost;
		if (line.empty())
			return std::vector<std::string>();
		trim(line);
		if (line.empty())
			return std::vector<std::string>();

		std::vector<std::string> output;

		const char_separator sep(separator);
		boost::tokenizer tokens(line, sep);
		for (const auto& t : tokens)
		{
			output.emplace_back(t);
		}
		return output;
	}

	inline std::pair<std::string, std::vector<std::string>> processArgs(std::string input)
	{
		using namespace std;
		using namespace boost;
		if (input.empty())
		{
			throw std::exception("Invalid command");
		}
		trim(input);
		if (input.empty())
		{
			throw std::exception("Invalid command");
		}
		std::string command = input.substr(0, input.find(' '));
		std::string args;
		if (input.size() > command.size())
		{
			args = input.substr(input.find(' '));
		}
		std::vector<std::string> processedArgs = tokenize(args, " ");
		return std::make_pair(command, processedArgs);
	}
}