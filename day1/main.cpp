#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <utility>
#include <vector>

void part1();
void part2();

int main()
{
    part1();
    part2();
}

void part1()
{
    std::vector<int> firtColumn;
    std::vector<int> secondColumn;
    std::ifstream file("day1/real_input.txt");

    std::string line;
    while (std::getline(file, line))
    {
        int first = std::stoi(line.substr(0, line.find(" ")));
        int second = std::stoi(line.substr(line.find(" ") + 1));

        firtColumn.push_back(first);
        secondColumn.push_back(second);
    }

    std::sort(firtColumn.begin(), firtColumn.end());
    std::sort(secondColumn.begin(), secondColumn.end());

    int difference = 0;
    for (int i = 0; i < firtColumn.size(); i++)
    {
        difference += std::abs(firtColumn[i] - secondColumn[i]);
    }

    std::cout << difference << std::endl;
}

void part2()
{
    std::ifstream file("day1/real_input.txt");

    std::map<int, std::pair<int, int> > list;

    std::string line;
    while (std::getline(file, line))
    {
        int first = std::stoi(line.substr(0, line.find(" ")));
        int second = std::stoi(line.substr(line.find(" ") + 1));

        if (list.find(first) == list.end())
        {
            list.insert(std::pair<int, std::pair<int, int>>(first, std::make_pair(1, 0)));
        }
        else
        {
            list[first].first++;
        }

        if (list.find(second) == list.end())
        {
            list.insert(std::pair<int, std::pair<int, int>>(second, std::make_pair(0, 1)));
        }
        else
        {
            list[second].second++;
        }
    }

    long sum = 0;

    for (auto it = list.begin(); it != list.end(); it++)
    {
        sum += it->first * it->second.first * it->second.second;
    }

    std::cout << sum << std::endl;
}