#pragma once
#include <unordered_map>
#include <vector>

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
