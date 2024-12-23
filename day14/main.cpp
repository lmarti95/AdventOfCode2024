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

#include <chrono>
#include <thread>

void part1();
void part2();

int main()
{
    part1();
    part2();
}

class Robot
{
public:
    int currentX;
    int currentY;
    int velocityX;
    int velocityY;
};

std::vector<Robot> robots;
int width = 101;
int tall = 103;

Robot createRobotFromLine(std::string line)
{
    Robot r;
    r.currentX = std::stoi(line.substr(2, line.find(",") - 2));
    r.currentY = std::stoi(line.substr(line.find(",") + 1, line.substr(line.find(",") + 1).find(" ")));

    std::string secondPart = line.substr(line.find("v=") + 2);
    r.velocityX = std::stoi(secondPart.substr(0, secondPart.find(",")));
    r.velocityY = std::stoi(secondPart.substr(secondPart.find(",") + 1));

    return r;
}

void moveRobotToNewLocation(Robot& robot)
{
    bool xDirectionPoisitive = robot.velocityX == std::abs(robot.velocityX);
    bool yDirectionPoisitive = robot.velocityY == std::abs(robot.velocityY);

    for (int i = 0; i < std::abs(robot.velocityX); i++)
    {
        int move = xDirectionPoisitive ? 1 : -1;
        int wouldBeLocation = robot.currentX + move;
        if (xDirectionPoisitive)
        {
            if (wouldBeLocation == width)
            {
                robot.currentX = 0;
            }
            else
            {
                robot.currentX = wouldBeLocation;
            }
        }
        else
        {
            if (wouldBeLocation == -1)
            {
                robot.currentX = width - 1;
            }
            else
            {
                robot.currentX = wouldBeLocation;
            }
        }
    }

    for (int i = 0; i < std::abs(robot.velocityY); i++)
    {
        int move = yDirectionPoisitive ? 1 : -1;
        int wouldBeLocation = robot.currentY + move;
        if (yDirectionPoisitive)
        {
            if (wouldBeLocation == tall)
            {
                robot.currentY = 0;
            }
            else
            {
                robot.currentY = wouldBeLocation;
            }
        }
        else
        {
            if (wouldBeLocation == -1)
            {
                robot.currentY = tall - 1;
            }
            else
            {
                robot.currentY = wouldBeLocation;
            }
        }
    }
}

void draw()
{
    for (int i = 0; i < tall; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            for (auto robot : robots)
            {
                if (robot.currentX == j && robot.currentY == i)
                {
                    count++;
                }
            }
            if (count > 0)
            {
                std::cout << "*";
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}

long quadrantCounter()
{
    long qd1 = 0;
    long qd2 = 0;
    long qd3 = 0;
    long qd4 = 0;

    for (int i = 0; i < tall/2; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            for (auto robot : robots)
            {
                if (robot.currentX == j && robot.currentY == i)
                {
                    qd1++;
                }
            }
        }

        for (int j = width/2+1; j < width; j++)
        {
            for (auto robot : robots)
            {
                if (robot.currentX == j && robot.currentY == i)
                {
                    qd2++;
                }
            }
        }
    }

    for (int i = tall / 2 + 1; i < tall; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            for (auto robot : robots)
            {
                if (robot.currentX == j && robot.currentY == i)
                {
                    qd3++;
                }
            }
        }

        for (int j = width / 2 + 1; j < width; j++)
        {
            for (auto robot : robots)
            {
                if (robot.currentX == j && robot.currentY == i)
                {
                    qd4++;
                }
            }
        }
    }

    return qd1 * qd2 * qd3 * qd4;
}

bool quadrantCheck()
{
    long qd1 = 0;
    long qd2 = 0;
    long qd3 = 0;
    long qd4 = 0;

    for (int i = 0; i < tall / 2; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            for (auto robot : robots)
            {
                if (robot.currentX == j && robot.currentY == i)
                {
                    qd1++;
                }
            }
        }

        for (int j = width / 2 + 1; j < width; j++)
        {
            for (auto robot : robots)
            {
                if (robot.currentX == j && robot.currentY == i)
                {
                    qd2++;
                }
            }
        }
    }

    for (int i = tall / 2 + 1; i < tall; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            for (auto robot : robots)
            {
                if (robot.currentX == j && robot.currentY == i)
                {
                    qd3++;
                }
            }
        }

        for (int j = width / 2 + 1; j < width; j++)
        {
            for (auto robot : robots)
            {
                if (robot.currentX == j && robot.currentY == i)
                {
                    qd4++;
                }
            }
        }
    }

    return qd1 == qd2 && qd3 == qd4;
}

bool isThereRobot(int x, int y)
{
    for (auto robot : robots)
    {
        if (robot.currentX == x && robot.currentY == y)
        {
            return true;
        }
    }

    return false;
}

bool christmasTreeCheckTopDown()
{
    for (int offset = 0; offset < 55; offset++)
    {
        int skip = 50;
        for (int i = 0; i < 51; i++)
        {
            for (int j = skip; j < width - skip; j++)
            {
                if (!isThereRobot(j, i + offset))
                {
                    return false;
                }
            }
            skip--;
        }
    }

    return true;
}

bool christmasTreeCheckBottomUp()
{
    for (int offset = 0; offset < 55; offset++)
    {
        int skip = 50;
        for (int i = 51; i > 0; i--)
        {
            for (int j = skip; j < width - skip; j++)
            {
                if (!isThereRobot(j, i + offset))
                {
                    return false;
                }
            }
            skip--;
        }
    }

    return true;
}

bool christmasTreeCheck()
{
    if (christmasTreeCheckTopDown())
    {
        return true;
    }

    if (christmasTreeCheckBottomUp())
    {
        return true;
    }

    return false;
}


void part1()
{
    std::ifstream file("real_input.txt");

    std::string line;
    while (std::getline(file, line))
    {
        robots.push_back(createRobotFromLine(line));
    }

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < robots.size(); j++)
        {
            //moveRobotToNewLocation(robots[j]);
        }
    }

    //quadrantCounter();
}

std::vector<std::pair<int, int>> lowestSecurityOnes;

void addSecurity(int location, int value)
{
    if (lowestSecurityOnes.size() < 10)
    {
        lowestSecurityOnes.push_back(std::make_pair(location, value));
        return;
    }

    int highestValue = lowestSecurityOnes[0].second;
    int locationInsideVector = 0;
    for (int i = 0; i < lowestSecurityOnes.size(); i++)
    {
        if (highestValue < lowestSecurityOnes[i].second)
        {
            highestValue = lowestSecurityOnes[i].second;
            locationInsideVector = i;
        }
    }

    if (value < highestValue)
    {
        lowestSecurityOnes.erase(lowestSecurityOnes.begin() + locationInsideVector);
        lowestSecurityOnes.push_back(std::make_pair(location, value));
    }
}

void part2()
{

    for (int i = 0; i < 103*101; i++)
    {
        for (int k = 0; k < robots.size(); ++k)
        {
            moveRobotToNewLocation(robots[k]);
        }

        /*if (quadrantCheck())
        {
            draw();

            std::cout << std::endl << i * 103 + j << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }*/

        if (i == 4971 || i == 6284 || i == 9213)
        {
            draw();

            std::cout << std::endl << i << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        }

        addSecurity(i, quadrantCounter());
    }

    for (int i = 0; i < lowestSecurityOnes.size(); i++)
    {
        std::cout << lowestSecurityOnes[i].first << " " << lowestSecurityOnes[i].second << std::endl;
    }
    
}