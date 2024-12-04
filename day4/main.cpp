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

std::string xmas = "XMAS";
std::string samx = "SAMX";

std::string sam = "SAM";
std::string mas = "MAS";

enum Direction { RIGHT, DOWN, ANGLE_DOWN_LEFT, ANGLE_DOWN_RIGHT};

std::vector<std::string> input;

int foundWords = 0;

std::map<std::pair<int, int>, int> positions;

bool calculateIAndJ(int &i, int& j, Direction direction, bool part2 = false)
{

    switch (direction)
    {
    case RIGHT:
        {
            j+=1;
            if (input[i].length() <= j)
            {
                return false;
            }
            return true;
        }
    case DOWN:
        {
            i+=1;
            if (input.size() <= i)
            {
                return false;
            }
            return true;
        }
    case ANGLE_DOWN_LEFT:
        {
            i+=1;
            j-=1;
            if (j == -1 || input.size() <= i)
            {
                return false;
            }
            return true;
        }
    case ANGLE_DOWN_RIGHT:
        {
            i+=1;
            j+=1;
            if (input[i].size() <= j || input.size() <= i)
            {
                return false;
            }
            return true;
        }
        default:
            return false;
    }
}

void checkLines(std::string word, Direction direction, bool part2 = false)
{
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            int iCopy = i;
            int jCopy = j;
            bool found = true;
            int aCopyI =-1;
            int aCopyJ =-1;
            for (int k = 0; k < word.length(); k++)
            {
                if (word[k] != input[iCopy][jCopy])
                {
                    found = false;
                    break;
                }

                if (part2 && k == 1)
                {
                    aCopyI = iCopy;
                    aCopyJ = jCopy;
                }

                if (!calculateIAndJ(iCopy, jCopy, direction) && k != word.length() - 1)
                {
                    found = false;
                    break;
                }
            }

            if (found)
            {
                foundWords++;
                if (part2)
                {
                    if (positions.find({aCopyI, aCopyJ}) == positions.end())
                    {
                        positions.emplace(std::make_pair(aCopyI, aCopyJ), 1);
                    }
                    else
                    {
                        auto it = positions.find({aCopyI, aCopyJ});
                        it->second += 1;
                    }
                }
            }
        }
    }
}

void part1()
{
    std::ifstream file("day4/real_input.txt");

    std::string line;
    while (std::getline(file, line))
    {
        input.push_back(line);
    }

    std::vector<Direction> directions = {RIGHT, DOWN, ANGLE_DOWN_LEFT, ANGLE_DOWN_RIGHT};

    for (auto direction : directions)
    {
        checkLines(xmas, direction);
        checkLines(samx, direction);
    }

    std::cout << foundWords << std::endl;
}

void part2()
{
    std::vector<Direction> directions = {ANGLE_DOWN_LEFT, ANGLE_DOWN_RIGHT};
    for (auto direction : directions)
    {
        checkLines(mas, direction, true);
        checkLines(sam, direction, true);
    }

    int count = 0;
    for (auto it = positions.begin(); it != positions.end(); it++)
    {
        if (it->second > 1)
        {
                count++;
        }
    }

    std::cout << count << std::endl;
}