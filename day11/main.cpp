#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

void part1();
void part2();

int main()
{
    part1();
    part2();
}

long getValue(long value)
{
    if (value == 0)
    {
        return 1;
    }
    else
    {
        return value*2024;
    }
}

bool checkForSplit(long value)
{
    std::string temp = std::to_string(value);

    if (temp.length() % 2 == 0)
    {
        return true;
    }

    return false;
}

std::pair<long, long> getSplitValues(long value)
{
    std::string temp = std::to_string(value);

    std::string temp2 = temp.substr(0, temp.length() / 2);
    std::string temp3 = temp.substr( temp.length() / 2);

    return std::make_pair(std::stoll(temp2), std::stoll(temp3));
}

std::vector<std::vector<long>> cache;

std::vector<long> calculateStoneCount(int value)
{
    std::vector<long>* stones = new std::vector<long>();
    std::vector<long>* stones2 = new std::vector<long>();
    std::vector<long> result;
    stones->push_back(value);
    for (int i = 0; i < 35; i++)
    {
        std::vector<long>* current;
        std::vector<long>* toBePushed;
        if (i%2 == 0)
        {
            current = stones;
            toBePushed = stones2;
        }
        else
        {
            current = stones2;
            toBePushed = stones;
        }

        toBePushed->clear();

        for (int j = 0; j < current->size(); j++)
        {
            if (checkForSplit(current->at(j)))
            {
                auto splits = getSplitValues(current->at(j));
                toBePushed->push_back(splits.first);
                toBePushed->push_back(splits.second);
            }
            else
            {
                toBePushed->push_back(getValue(current->at(j)));
            }
        }

        result.push_back(toBePushed->size());
    }

    delete stones;
    delete stones2;

    return result;
}

void calculateCache()
{
    std::cout << "Doing Cache" << std::endl;
    for (int i = 0; i < 100; i++)
    {
        auto result = calculateStoneCount(i);
        cache.push_back(result);
    }

    std::cout << "Finished Cache" << std::endl;
}

void part1()
{
    std::ifstream file("day11/real_input.txt");

    std::vector<long>* stones = new std::vector<long>;

    std::string line;
    while (std::getline(file, line))
    {
        int number;
        std::istringstream line_stream(line);
        while (line_stream >> number)
        {
            stones->push_back(number);
        }
    }

    calculateCache();
    long long count = 0;

    std::vector<long>* stones2 = new std::vector<long>();
    int loopLength = 75;
    for (int i = 0; i < loopLength; i++)
    {
        std::vector<long>* current;
        std::vector<long>* toBePushed;
        if (i%2 == 0)
        {
            current = stones;
            toBePushed = stones2;
        }
        else
        {
            current = stones2;
            toBePushed = stones;
        }

        std::cout << "loop: " << i << " " << current->size()/1000000 << "M" << std::endl;

        toBePushed->clear();

        for (int j = 0; j < current->size(); j++)
        {
            if (checkForSplit(current->at(j)))
            {
                auto splits = getSplitValues(current->at(j));
                if (splits.first < 100 && i > 40 && i < 70)
                {
                    count += cache[splits.first][loopLength-i-2];
                }
                else
                {
                    toBePushed->push_back(splits.first);
                }

                if (splits.second < 100 && i > 40 && i < 70)
                {
                    count += cache[splits.second][loopLength-i-2];
                }
                else
                {
                    toBePushed->push_back(splits.second);
                }
            }
            else
            {
                long value = getValue(current->at(j));

                if (value < 100 && i > 40 && i < 70)
                {
                    count += cache[value][loopLength-i-2];
                }
                else
                {
                    toBePushed->push_back(value);
                }
            }
        }
    }

    count += stones2->size();

    std::cout << count << std::endl;

    delete stones;
    delete stones2;
}

void part2()
{
}