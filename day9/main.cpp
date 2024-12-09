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

class File
{
public:
    int id;
    bool freeFile;
};

std::vector<File> files;

int getLeftMostFreeFile()
{
    for (int i = 0; i < files.size(); ++i)
    {
        if (files[i].freeFile)
            return i;
    }
    return -1;
}

int getRightMostFile()
{
    for (int i = files.size() - 1; i >= 0; --i)
    {
        if (!files[i].freeFile)
        {
            return i;
        }
    }

    return -1;
}

void swapFiles(int i, int j)
{
    std::swap(files[i], files[j]);
}

int getLeftMostFreeBlock(int size)
{
    for (int i = 0; i < files.size(); ++i)
    {
        bool valid = true;
        for (int j = 0; j < size; ++j)
        {
            if (i+j > files.size() - 1)
            {
                return -1;
            }
            if (!files[i+j].freeFile)
            {
                valid = false;
                break;
            }
        }
        if (valid)
        {
            return i;
        }
    }
    return -1;
}

int swapBlock(int i, int j, int size)
{
    for (int k = 0; k < size; ++k)
    {
        swapFiles(i+k, j+k);
    }
}

int getIdLength(int id)
{
    int length = 0;
    for (int i = 0; i < files.size(); ++i)
    {
        if (files[i].id == id)
        {
            length++;
        }
    }

    return length;
}

int getLeftMostOccurence(int id)
{
    for (int i = 0; i < files.size(); ++i)
    {
        if (files[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

void calculateCheckSum()
{
    long checkSum = 0;
    for (int i = 0; i < files.size(); ++i)
    {

        if (!files[i].freeFile)
        {
            std::cout << files[i].id;
            checkSum+=i*files[i].id;
        }
        else
        {
            std::cout << ".";
        }
    }
    std::cout << std::endl;

    std::cout << checkSum << std::endl;
}

void part1()
{
    std::ifstream file("day9/real_input.txt");

    std::string line;

    while (std::getline(file, line))
    {
        bool freeFile = false;
        int currentId = 0;
        for (int i = 0; i < line.size(); i++)
        {
            int currentNum = std::stoi(line.substr(i, 1));
            for (int j = 0; j < currentNum; j++)
            {
                if (freeFile)
                {
                    File file;
                    file.id = -1;
                    file.freeFile = true;
                    files.push_back(file);
                }
                else
                {
                    File file;
                    file.id = currentId;
                    file.freeFile = false;
                    files.push_back(file);
                }
            }
            if (freeFile)
            {
                freeFile = false;
                currentId++;
            }
            else
            {
                freeFile = true;
            }
        }
    }

    int freeFile = getLeftMostFreeFile();
    int nonFreeFile = getRightMostFile();
    while (freeFile < nonFreeFile)
    {
        swapFiles(freeFile, nonFreeFile);
        freeFile = getLeftMostFreeFile();
        nonFreeFile = getRightMostFile();
    }

    calculateCheckSum();
}

void part2()
{
    std::ifstream file("day9/real_input.txt");

    std::string line;

    int maxId = 0;

    while (std::getline(file, line))
    {
        bool freeFile = false;
        int currentId = 0;
        for (int i = 0; i < line.size(); i++)
        {
            int currentNum = std::stoi(line.substr(i, 1));
            for (int j = 0; j < currentNum; j++)
            {
                if (freeFile)
                {
                    File file;
                    file.id = -1;
                    file.freeFile = true;
                    files.push_back(file);
                }
                else
                {
                    File file;
                    file.id = currentId;
                    file.freeFile = false;
                    files.push_back(file);
                    maxId=currentId;
                }
            }
            if (freeFile)
            {
                freeFile = false;
                currentId++;
            }
            else
            {
                freeFile = true;
            }
        }
    }


    while (maxId >= 0)
    {
        int leftMost = getLeftMostOccurence(maxId);
        int size = getIdLength(maxId);
        int leftMostBlock = getLeftMostFreeBlock(size);

        if (leftMostBlock == -1)
        {
            maxId--;
            continue;
        }

        if (leftMostBlock < leftMost)
        {
            swapBlock(leftMost, leftMostBlock, size);
        }

        maxId--;
    }

    calculateCheckSum();
}