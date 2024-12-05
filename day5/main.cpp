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

std::map<int, std::vector<int>> rules;
std::vector<std::vector<int>> bookPages;
std::vector<int> invalidPages;

long sum = 0;

int getMiddle(std::vector<int> pages)
{
    return pages[pages.size() / 2];
}

void swap(int i, int j, int k)
{
    int temp = bookPages[i][j];
    bookPages[i][j] = bookPages[i][k];
    bookPages[i][k] = temp;
}

void checkLines(bool part2=false)
{
    for (int i = 0; i < bookPages.size(); i++)
    {
        bool validPage = true;
        for (int j = bookPages[i].size() - 1; j >= 0; j--)
        {
            for (int k = 0; k < j; k++)
            {
                if (std::find(rules[bookPages[i][j]].begin(),rules[bookPages[i][j]].end(), bookPages[i][k]) != rules[bookPages[i][j]].end())
                {
                    validPage = false;
                    if (part2)
                    {
                        invalidPages.push_back(i);
                    }
                    break;
                }
            }
            if (!validPage)
            {
                break;
            }
        }

        if (validPage)
        {
            sum+=getMiddle(bookPages[i]);
        }
    }
}

void fixInvalidPages()
{
    for (int l = 0; l < invalidPages.size(); l++)
    {
        bool validPage = false;
        int i = invalidPages[l];
        while (!validPage)
        {
            validPage = true;
            for (int j = bookPages[i].size() - 1; j >= 0; j--)
            {
                for (int k = 0; k < j; k++)
                {
                    if (std::find(rules[bookPages[i][j]].begin(),rules[bookPages[i][j]].end(), bookPages[i][k]) != rules[bookPages[i][j]].end())
                    {
                        validPage = false;
                        swap(i, j, k);
                        break;
                    }
                }
                if (!validPage)
                {
                    break;
                }
            }
        }
    }
}

void part1()
{
    std::ifstream file("day5/real_input.txt");

    std::string line;
    while (std::getline(file, line))
    {
        if (line.find('|') != std::string::npos)
        {
            int first = std::stoi(line.substr(0, line.find('|')));
            int second = std::stoi(line.substr(line.find('|') + 1));

            if (rules.find(first) == rules.end())
            {
                rules.insert(std::pair<int, std::vector<int>>(first, std::vector<int>()));
                rules[first].push_back(second);
            }
            else
            {
                rules[first].push_back(second);
            }
        }
        else
        {
            std::vector<int> pages;

            std::stringstream ss(line);

            int i;

            while (ss >> i)
            {
                pages.push_back(i);

                if (ss.peek() == ',')
                    ss.ignore();
            }

            if (pages.size() > 0)
            {
                bookPages.push_back(pages);
            }
        }
    }
    checkLines();

    std::cout << sum << std::endl;
}

void part2()
{
    checkLines(true);
    fixInvalidPages();
    sum = 0;
    for (int i = 0; i < invalidPages.size(); i++)
    {
        sum += getMiddle(bookPages[invalidPages[i]]);
    }

    std::cout << sum << std::endl;
}