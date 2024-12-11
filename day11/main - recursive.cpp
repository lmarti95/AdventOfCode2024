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

class Stone
{
public:
    long value;
    bool splitted = false;
    Stone* left = nullptr;
    Stone* right = nullptr;
};

std::vector<Stone*> stones;
long stoneCount = 0;

void deleteStoneRecursive(Stone* stone)
{
    if (stone->left != nullptr)
    {
        deleteStoneRecursive(stone->left);
    }
    if (stone->right != nullptr)
    {
        deleteStoneRecursive(stone->right);
    }

    delete stone;
}

void deleteStones()
{
    for (auto it = stones.begin(); it != stones.end(); it++)
    {
        deleteStoneRecursive(*it);
    }
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

void split(Stone* stone)
{
    auto splitValues = getSplitValues(stone->value);

    stone->splitted = true;
    stone->left = new Stone;
    stone->right = new Stone;
    stone->left->value = splitValues.first;
    stone->right->value = splitValues.second;
}

void blink(Stone* stone)
{
    if (stone->splitted)
    {
        blink(stone->left);
        blink(stone->right);
    }
    else
    {
        if (checkForSplit(stone->value))
        {
            split(stone);
        }
        else
        {
            stone->value = getValue(stone->value);
        }
    }
}

void countStones(Stone* stone)
{
    if (stone->splitted)
    {
        countStones(stone->left);
        countStones(stone->right);
    }
    else
    {
        stoneCount++;
    }
}

void part1()
{
    std::ifstream file("day11/real_input.txt");

    std::string line;
    while (std::getline(file, line))
    {
        int number;
        std::istringstream line_stream(line);
        while (line_stream >> number)
        {
            Stone* stone = new Stone;
            stone->value = number;
            stones.push_back(stone);
        }
    }

    auto values = getSplitValues(2000);

    for (int i = 0; i < 25; i++)
    {
        for (int j =0; j < stones.size(); j++)
        {
            blink(stones[j]);
        }
    }

    for (int i =0; i < stones.size(); i++)
    {
        countStones(stones[i]);
    }

    std::cout << stoneCount << std::endl;

    deleteStones();
}

void part2()
{
}