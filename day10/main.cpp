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

class GraphPoint
{
public:
    int id;
    int i;
    int j;
    int value;
};

std::vector<std::vector<GraphPoint>> graphPoints;

std::vector<GraphPoint> evaluated;
std::vector<GraphPoint> toBeEvaluated;

int nineCount = 0;

std::vector<GraphPoint> getValidNeighbours(GraphPoint gp)
{
    std::vector<GraphPoint> result;
    if (gp.i != 0 && graphPoints[gp.i-1][gp.j].value-1==gp.value)
    {
        result.push_back(graphPoints[gp.i-1][gp.j]);
    }
    if (gp.i != graphPoints.size()-1 && graphPoints[gp.i+1][gp.j].value-1==gp.value)
    {
        result.push_back(graphPoints[gp.i+1][gp.j]);
    }
    if (gp.j != 0 && graphPoints[gp.i][gp.j-1].value-1==gp.value)
    {
        result.push_back(graphPoints[gp.i][gp.j-1]);
    }
    if (gp.j != graphPoints[gp.j].size()-1 && graphPoints[gp.i][gp.j+1].value-1==gp.value)
    {
        result.push_back(graphPoints[gp.i][gp.j+1]);
    }

    return result;
}

void evaluate(GraphPoint gp, bool part2 = false)
{
    if (gp.value == 9)
    {
        nineCount++;
    }

    auto neighbours = getValidNeighbours(gp);
    for (auto neighbour : neighbours)
    {
        if (std::find_if(evaluated.begin(), evaluated.end(), [neighbour](GraphPoint gp)
        {
            if (gp.id == neighbour.id)
            {
                return true;
            }
            return false;
        }) == evaluated.end())
        {
            if (!part2)
            {
                if (std::find_if(toBeEvaluated.begin(), toBeEvaluated.end(), [neighbour](GraphPoint gp)
                {
                    if (gp.id == neighbour.id)
                    {
                        return true;
                    }
                    return false;
                }) == toBeEvaluated.end())
                {
                    toBeEvaluated.push_back(neighbour);
                }
            }
            else
            {
                toBeEvaluated.push_back(neighbour);
            }
        }
    }

    evaluated.push_back(gp);
}

void part1()
{
    std::ifstream file("day10/real_input.txt");

    std::string line;

    int id=0;
    while (std::getline(file, line))
    {
        std::vector<GraphPoint> graphPointLine;
        for (int i = 0; i < line.size(); i++)
        {
            GraphPoint gp;
            gp.id=id;
            id++;
            gp.i=graphPoints.size();
            gp.j=i;
            gp.value = line[i]-'0';
            graphPointLine.push_back(gp);
        }

        graphPoints.push_back(graphPointLine);
    }

    for (int i = 0; i < graphPoints.size(); i++)
    {
        for (int j = 0; j < graphPoints[i].size(); j++)
        {
            if (graphPoints[i][j].value == 0)
            {
                evaluate(graphPoints[i][j]);
                while (toBeEvaluated.size() > 0)
                {
                    evaluate(toBeEvaluated[0]);
                    toBeEvaluated.erase(toBeEvaluated.begin());
                }

                toBeEvaluated.clear();
                evaluated.clear();
            }
        }
    }

    std::cout << nineCount << std::endl;
}

void part2()
{
    nineCount = 0;
    for (int i = 0; i < graphPoints.size(); i++)
    {
        for (int j = 0; j < graphPoints[i].size(); j++)
        {
            if (graphPoints[i][j].value == 0)
            {
                evaluate(graphPoints[i][j], true);
                while (toBeEvaluated.size() > 0)
                {
                    evaluate(toBeEvaluated[0], true);
                    toBeEvaluated.erase(toBeEvaluated.begin());
                }

                toBeEvaluated.clear();
                evaluated.clear();
            }
        }
    }

    std::cout << nineCount << std::endl;
}