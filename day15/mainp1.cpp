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

class Object {
public:
    int coordI;
    int coordJ;
    bool isBox;
};

class Wall : public Object {
};

class Box : public Object {
};

class Robot : public Object {
};

enum Direction {UP, DOWN, LEFT, RIGHT};

Robot r;
std::vector<Wall> walls;
std::vector<Box> boxes;
std::vector<std::string> instructions;

void createFromCharacter(char c, int i, int j)
{
    switch (c)
    {
    case '#':
        Wall w;
        w.coordI = i;
        w.coordJ = j;
        w.isBox = false;
        walls.push_back(w);
        break;
    case 'O':
        Box b;
        b.coordI = i;
        b.coordJ = j;
        b.isBox = true;
        boxes.push_back(b);
        break;
    case '.':
        return;
    case '@':
        r.coordI = i;
        r.coordJ = j;
        r.isBox = false;
        break;
    default:
        return;
    }
}

Direction characterToDirection(char c)
{
    switch (c)
    {
    case '^':
        return Direction::UP;
    case 'v':
        return Direction::DOWN;
    case '<':
        return Direction::LEFT;
    case '>':
        return Direction::RIGHT;
    }
}

std::pair<int,int> getDirectionCoordinates(Object object, Direction direction)
{
    if (direction == Direction::UP)
    {
        return std::make_pair(object.coordI - 1, object.coordJ);
    }
    if (direction == Direction::DOWN)
    {
        return std::make_pair(object.coordI + 1, object.coordJ);
    }
    if (direction == Direction::LEFT)
    {
        return std::make_pair(object.coordI, object.coordJ - 1);
    }
    if (direction == Direction::RIGHT)
    {
        return std::make_pair(object.coordI, object.coordJ + 1);
    }
}

Object* getWall(int i, int j)
{
    for (int k = 0; k < walls.size(); k++)
    {
        if (walls[k].coordI == i && walls[k].coordJ == j)
        {
            return &walls[k];
        }
    }

    return nullptr;
}

Object* getBox(int i, int j)
{
    for (int k = 0; k < boxes.size(); k++)
    {
        if (boxes[k].coordI == i && boxes[k].coordJ == j)
        {
            return &boxes[k];
        }
    }

    return nullptr;
}

Object* getObject(Object object, Direction direction)
{
    std::pair<int, int> newCords = getDirectionCoordinates(object, direction);

    Object* wall = getWall(newCords.first, newCords.second);
    if (wall != nullptr)
    {
        return wall;
    }

    return getBox(newCords.first, newCords.second);;
}

bool checkMovePossible(Object object, Direction direction) 
{
    Object* nextObject = getObject(object, direction);

    if (nextObject == nullptr)
    {
        return true;
    }

    if (!nextObject->isBox)
    {
        return false;
    }


    return checkMovePossible(*nextObject, direction);
}

void makeMove(Object* object, Direction direction)
{
    Object* nextObject = getObject(*object, direction);

    std::pair<int, int> newCords = getDirectionCoordinates(*object, direction);

    object->coordI = newCords.first;
    object->coordJ = newCords.second;

    if (nextObject == nullptr)
    {
        return;
    }

    return makeMove(nextObject, direction);

}

void getGPSCords()
{
    long count = 0;
    for (int i = 0; i < boxes.size();i++)
    {
        count += boxes[i].coordI * 100 + boxes[i].coordJ;
    }

    std::cout << count << std::endl;
}

void print()
{
    for (int i = 0; i < walls[walls.size() - 1].coordI + 1;i++)
    {
        for (int j = 0; j < walls[walls.size() - 1].coordJ + 1;j++)
        {
            Object* o = getWall(i, j);
            if (o  != nullptr)
            {
                std::cout << '#';
                continue;
            }

            o = getBox(i, j);
            if (o != nullptr)
            {
                std::cout << 'O';
                continue;
            }

            if (r.coordI == i && r.coordJ == j)
            {
                std::cout << '@';
                continue;
            }

            std::cout << '.';

        }
        std::cout << std::endl;
    }
}

void part1()
{
    std::ifstream file("real_input.txt");

    std::string line;
    bool firstPart = true;
    int lineCount = 0;
    while (std::getline(file, line))
    {
        if (firstPart)
        {
            if (line.length() == 0)
            {
                firstPart = false;
                continue;
            }
            for (int i = 0; i < line.length();i++)
            {
                createFromCharacter(line[i], lineCount, i);
            }
            lineCount++;
        }
        else
        {
            instructions.push_back(line);
        }
    }

    //print();

    for (int i = 0; i < instructions.size(); i++)
    {
        for (int j = 0; j < instructions[i].length(); j++)
        {
            if (checkMovePossible(r, characterToDirection(instructions[i][j])))
            {
                makeMove(&r, characterToDirection(instructions[i][j]));
            }

            //print();
        }
    }

    getGPSCords();
}

void part2()
{

}