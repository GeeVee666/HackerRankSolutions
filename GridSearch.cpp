#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

namespace
{
	unsigned row_count{}, column_count{};
	unsigned p_row_count{}, p_column_count{};
}

auto flatten(const std::vector<std::string>& _2D)
{
	std::vector<char> temp{};
	for (const auto& s : _2D) for (const auto& c : s) temp.push_back(c);
	return temp;
}

void cut(std::vector<unsigned>& positions)
{
	positions.erase(std::remove_if(positions.begin(), positions.end(),
		[](unsigned position) {return position / column_count > row_count - p_row_count; }), positions.end());
	positions.erase(std::remove_if(positions.begin(), positions.end(),
		[](unsigned position) {return position % column_count + p_column_count - 1 > column_count - 1; }), positions.end());
}

bool check_for_pattern_in_matrix(const std::vector<std::string>& sc, const std::vector<std::string>& pt)
{
	auto source = flatten(sc);
	auto pattern = flatten(pt);
	std::vector<unsigned> positions{};
	for (auto i = 0; i < source.size(); i++)
	{
		if (source[i] == pattern[0])
			positions.push_back(i);
	}
	// remove if it causes impossible/clashing subscripts
	cut(positions);
	if (positions.empty())
		return false;
	for (const auto& position : positions)
	{
		bool breakc = false;
		for (unsigned i = 0, j = position; i < pattern.size(); i++)
		{
			if (source[j] == pattern[i])
				breakc = false;
			else
			{
				breakc = true;
				break;
			}
			if ((i + 1) % p_column_count == 0)
				j += column_count - (p_column_count - 1);
			else
				j++;
		}
		if (!breakc)
			return true;
	}
	return false;
}

int main()
{
	unsigned test_nums{};
	std::cin >> test_nums;
	for (auto i = 0; i < test_nums; i++)
	{
		std::cin >> row_count >> column_count;
		std::vector<std::string> source(row_count);
		for (auto& str : source) std::cin >> str;
		std::cin >> p_row_count >> p_column_count;
		std::vector<std::string> pattern(p_row_count);
		for (auto& str : pattern) std::cin >> str;
		if (check_for_pattern_in_matrix(source, pattern))
		{
			std::cout << "YES" << std::endl;
		}
		else
			std::cout << "NO" << std::endl;
	}
	return 0;
}
