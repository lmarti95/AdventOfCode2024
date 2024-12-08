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
    //part1();
    part2();
}

class Antenna
{
public:
    int coordI;
    int coordJ;
};

std::map<char, std::vector<Antenna>> antennas;
std::vector<std::vector<int>> layout;

std::pair<int, int> getDiff(Antenna a1, Antenna a2)
{
    return std::make_pair(a1.coordI-a2.coordI, a1.coordJ-a2.coordJ);
}

bool checkBoundaries(Antenna a1, std::pair<int,int> diff)
{
    if (a1.coordI+diff.first < 0 || a1.coordI+diff.first >= layout[a1.coordI].size())
    {
        return false;
    }
    if (a1.coordJ+diff.second < 0 || a1.coordJ+diff.second >= layout[a1.coordI].size())
    {
        return false;
    }
    return true;
}

void calculateInterference(Antenna a1, Antenna a2)
{
    auto diff = getDiff(a1, a2);
    if (checkBoundaries(a1, diff))
    {
        layout[a1.coordI+diff.first][a1.coordJ+diff.second] = 1;
    }

    diff = getDiff(a2, a1);
    if (checkBoundaries(a2, diff))
    {
        layout[a2.coordI+diff.first][a2.coordJ+diff.second] = 1;
    }
}

void calculateInterferencePart2(Antenna a1, Antenna a2)
{
    auto diff = getDiff(a1, a2);
    Antenna a1Copy = a1;
    while (checkBoundaries(a1Copy, diff))
    {
        layout[a1Copy.coordI+diff.first][a1Copy.coordJ+diff.second] = 1;
        a1Copy.coordI = a1Copy.coordI + diff.first;
        a1Copy.coordJ = a1Copy.coordJ + diff.second;
    }

    diff = getDiff(a2, a1);
    Antenna a2Copy = a2;
    while (checkBoundaries(a2Copy, diff))
    {
        layout[a2Copy.coordI+diff.first][a2Copy.coordJ+diff.second] = 1;
        a2Copy.coordI = a2Copy.coordI + diff.first;
        a2Copy.coordJ = a2Copy.coordJ + diff.second;
    }
}

void part1()
{
    std::ifstream file("day8/real_input.txt");

    std::string line;

    while (std::getline(file, line))
    {
        std::vector<int> layoutLine;
        for (int i =0 ; i < line.size(); i++)
        {
            layoutLine.push_back(0);
            if (line[i] != '.')
            {
                if (antennas.find(line[i]) == antennas.end())
                {
                    antennas[line[i]] = std::vector<Antenna>();
                }

                Antenna antenna;
                antenna.coordI = layout.size();
                antenna.coordJ = i;
                antennas[line[i]].push_back(antenna);
            }
        }

        layout.push_back(layoutLine);
    }

    for (auto it = antennas.begin(); it != antennas.end(); it++)
    {
        for (int i =0 ; i < it->second.size(); i++)
        {
            for (int j =i+1 ; j < it->second.size(); j++)
            {
                calculateInterference(it->second[i], it->second[j]);
            }
        }
    }

    int interferenceLocations = 0;
    for (int i =0 ; i < layout.size(); i++)
    {
        for (int j =0 ; j < layout[i].size(); j++)
        {
            if (layout[i][j] == 1)
            {
                interferenceLocations++;
            }
        }
    }

    std::cout << interferenceLocations << std::endl;
}

void part2()
{
    std::ifstream file("day8/real_input.txt");

    std::string line;


    while (std::getline(file, line))
    {
        std::vector<int> layoutLine;
        for (int i =0 ; i < line.size(); i++)
        {
            layoutLine.push_back(0);
            if (line[i] != '.')
            {
                if (antennas.find(line[i]) == antennas.end())
                {
                    antennas[line[i]] = std::vector<Antenna>();
                }

                Antenna antenna;
                antenna.coordI = layout.size();
                antenna.coordJ = i;
                antennas[line[i]].push_back(antenna);
            }
        }

        layout.push_back(layoutLine);
    }

    for (auto it = antennas.begin(); it != antennas.end(); it++)
    {
        for (int i =0 ; i < it->second.size(); i++)
        {
            for (int j =i+1 ; j < it->second.size(); j++)
            {
                calculateInterferencePart2(it->second[i], it->second[j]);
            }
        }
    }

    for (auto it = antennas.begin(); it != antennas.end(); it++)
    {
        for (int i =0 ; i < it->second.size(); i++)
        {
            layout[it->second[i].coordI][it->second[i].coordJ] = 1;
        }
    }

    int interferenceLocations = 0;
    for (int i =0 ; i < layout.size(); i++)
    {
        for (int j =0 ; j < layout[i].size(); j++)
        {
            if (layout[i][j] == 1)
            {
                interferenceLocations++;
            }
        }
    }

    std::cout << interferenceLocations << std::endl;
}