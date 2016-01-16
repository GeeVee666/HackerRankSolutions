#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

unsigned row_count{}, column_count{};
unsigned p_row_count{}, p_column_count{};

bool check_for_pattern_in_matrix(const std::vector<std::string>& sc, const std::vector<std::string>& pt)
{
    // convert 2D array to 1D
    std::vector<char> source{};
    for(const auto& s : sc) for(const auto& c : s) source.push_back(c);
    std::vector<char> pattern{};
    for(const auto& s : pt) for(const auto& c : s) pattern.push_back(c);
    std::vector<unsigned> positions{};
    for(auto i = 0; i < source.size(); i++)
    {
        if(source[i] == pattern[0])
            positions.push_back(i);
    }
    // remove if it causes impossible/clashing subscripts
    positions.erase(std::remove_if(positions.begin(), positions.end(), [](unsigned position){return position/column_count > row_count - p_row_count;}), positions.end());
    positions.erase(std::remove_if(positions.begin(), positions.end(), [](unsigned position){return position % column_count + p_column_count - 1 > column_count -1;}), positions.end());
    if(positions.empty())
        return false;
    bool breakc{false};
    for(const auto& position: positions)
    {
        auto pos = position;
        for(unsigned i = 0, j = pos; i < pattern.size(); i++)
        {
            auto oldj = j;
            if((i+1)%p_column_count == 0)
                j += column_count - (p_column_count-1);
            else
                j++;
            if(source[oldj] == pattern[i])
                breakc = false;
            else
            {
                breakc = true;
                break;
            }
        }
        if(breakc)
            continue;
        else
            return true;
    }
    return false;
}

int main()
{
    unsigned test_nums{};
    std::cin >> test_nums;
    for(auto i = 0; i < test_nums; i++)
    {
        
        std::cin >> row_count >> column_count;
        std::vector<std::string> source(row_count);
        for(auto& str : source) std::cin >> str;
        std::cin >> p_row_count >> p_column_count;
        std::vector<std::string> pattern(p_row_count);
        for(auto& str : pattern) std::cin >> str;
        if(check_for_pattern_in_matrix(source, pattern))
        {
            std::cout << "YES" << std::endl;    
        }
        else
            std::cout << "NO" << std::endl;
    }
    return 0;
}
