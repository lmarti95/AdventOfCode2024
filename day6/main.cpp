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

enum Direction{UP, DOWN, LEFT, RIGHT};

class Guard
{
public:
    int locationI;
    int locationJ;
    Direction direction=Direction::UP;
    bool exited = false;


};

std::vector<std::vector<int>> map;

void markGuardVisited(Guard g)
{
    map[g.locationI][g.locationJ] = 2;
}

void step(Guard& g, bool part2=false)
{
    if (g.direction == Direction::UP)
    {
        if (g.locationI == 0)
        {
            g.exited = true;
            return;
        }
        if (map[g.locationI-1][g.locationJ] == 1)
        {
            g.direction = Direction::RIGHT;
            return;
        }

        g.locationI--;
        if (!part2)
        {
            markGuardVisited(g);
        }
        return;
    }

    if (g.direction == Direction::RIGHT)
    {
        if (g.locationJ == map[g.locationI].size()-1)
        {
            g.exited = true;
            return;
        }
        if (map[g.locationI][g.locationJ+1] == 1)
        {
            g.direction = Direction::DOWN;
            return;
        }

        g.locationJ++;
        if (!part2)
        {
            markGuardVisited(g);
        }
        return;
    }

    if (g.direction == Direction::DOWN)
    {
        if (g.locationI == map.size()-1)
        {
            g.exited = true;
            return;
        }
        if (map[g.locationI+1][g.locationJ] == 1)
        {
            g.direction = Direction::LEFT;
            return;
        }

        g.locationI++;
        if (!part2)
        {
            markGuardVisited(g);
        }
    }

    if (g.direction == Direction::LEFT)
    {
        if (g.locationJ == 0)
        {
            g.exited = true;
            return;
        }
        if (map[g.locationI][g.locationJ-1] == 1)
        {
            g.direction = Direction::UP;
            return;
        }

        g.locationJ--;
        if (!part2)
        {
            markGuardVisited(g);
        }
    }
}

void getVisitedCount()
{
    int visitedCount = 0;
    for (auto i = 0; i < map.size(); i++)
    {
        for (auto j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == 2)
            {
                visitedCount++;
            }
        }
    }

    std::cout << visitedCount << std::endl;
}

void part1()
{
    std::ifstream file("day6/real_input.txt");

    std::string line;
    Guard g;
    while (std::getline(file, line))
    {
        std::vector<int> row;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '.')
            {
                row.push_back(0);
            }
            if (line[i] == '#')
            {
                row.push_back(1);
            }
            if (line[i] == '^')
            {
                row.push_back(2);
                g.locationI = map.size();
                g.locationJ = i;
            }
        }

        map.push_back(row);
    }

    while (!g.exited)
    {
        step(g);
    }

    getVisitedCount();
}

void part2()
{
    std::ifstream file("day6/real_input.txt");

    std::string line;
    Guard g;
    while (std::getline(file, line))
    {
        std::vector<int> row;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '.')
            {
                row.push_back(0);
            }
            if (line[i] == '#')
            {
                row.push_back(1);
            }
            if (line[i] == '^')
            {
                row.push_back(2);
                g.locationI = map.size();
                g.locationJ = i;
            }
        }

        map.push_back(row);
    }

    int loopObstructions = 0;

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == 0)
            {
                map[i][j] = 1;
                Guard g2 = g;
                for (int k = 0; k < 100000; k++)
                {
                    step(g2, true);
                    if (g2.exited)
                    {
                        break;
                    }
                }
                if (!g2.exited)
                {
                    loopObstructions++;
                }
                map[i][j] = 0;
            }
        }
    }

    std::cout << loopObstructions << std::endl;
}