#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <sstream>
#include <utility>
#include <vector>

void part1();
void part2();

int main()
{
    part1();
    part2();
}

enum Direction
{
    Undefined,
    Declining,
    Rising
};

Direction currentDirection = Undefined;

int maxDistance = 3;

bool directionCheck(int first, int second)
{
    if (first == second)
    {
        return false;
    }

    if (currentDirection == Undefined)
    {
        if (first > second)
        {
            currentDirection = Declining;
        }
        else
        {
            currentDirection = Rising;
        }
    }
    else
    {
        if (currentDirection == Rising && first > second)
        {
            return false;
        }

        if (currentDirection == Declining && first < second)
        {
            return false;
        }
    }

    return true;
}

bool checkTwoNumbers(int first, int second)
{

    if (!directionCheck(first, second))
    {
        return false;
    }

    if (std::abs(first - second) > maxDistance)
    {
        return false;
    }

    return true;
}

bool problemDampener(std::vector<int> line)
{
    for (int i = 0; i < line.size(); i++)
    {
        std::vector tempLine = line;

        tempLine.erase(tempLine.begin()+i);
        bool currentLineSafe = true;
        currentDirection = Undefined;
        for (int j = 1; j < tempLine.size(); j++)
        {
            if (!checkTwoNumbers(tempLine[j-1], tempLine[j]))
            {
                currentLineSafe = false;
            }
        }

        if (currentLineSafe)
        {
            return true;
        }
    }

}

void part1()
{
    std::vector<std::vector<int>> lines;
    std::ifstream file("day2/real_input.txt");

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<int> currentLine;
        int number;
        std::istringstream line_stream(line);
        while (line_stream >> number)
        {
            currentLine.push_back(number);
        }

        lines.push_back(currentLine);
    }

    int safeLines =0;

    for (int i=0; i<lines.size(); i++)
    {
        bool currentLineSafe = true;
        currentDirection = Undefined;
        for (int j=1; j<lines[i].size(); j++)
        {
            if (!checkTwoNumbers(lines[i][j-1], lines[i][j]))
            {
                currentLineSafe = false;
            }
        }

        if (currentLineSafe)
        {
            safeLines++;
        }
    }

    std::cout << safeLines << std::endl;
}

void part2()
{
    std::vector<std::vector<int>> lines;
    std::ifstream file("day2/real_input.txt");

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<int> currentLine;
        int number;
        std::istringstream line_stream(line);
        while (line_stream >> number)
        {
            currentLine.push_back(number);
        }

        lines.push_back(currentLine);
    }

    int safeLines =0;

    for (int i=0; i<lines.size(); i++)
    {
        bool currentLineSafe = true;
        currentDirection = Undefined;
        for (int j=1; j<lines[i].size(); j++)
        {
            if (!checkTwoNumbers(lines[i][j-1], lines[i][j]))
            {
                currentLineSafe = false;
            }
        }

        if (currentLineSafe)
        {
            safeLines++;
        }
        else
        {
            if (problemDampener(lines[i]))
            {
                safeLines++;
            }
        }
    }



    std::cout << safeLines << std::endl;
}