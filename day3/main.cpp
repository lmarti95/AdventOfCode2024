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

std::string mul = "mul(";
std::string doString = "do()";
std::string dontString = "don't()";

long totalSum = 0;
bool enabled = true;

bool check(std::string line, int i, std::string checkString)
{
    for (int j = 0; j < checkString.size(); j++)
    {
        if (i+j >= line.size())
        {
            return false;
        }

        if (std::string{line[i+j]}.compare(std::string{checkString[j]}) != 0)
        {
            return false;
        }
    }

    return true;
}

void calculateLine(std::string line, bool secondPart=false)
{
    for (int i = 0; i < line.size(); i++)
    {
        if (secondPart)
        {
            if (check(line, i, doString))
            {
                enabled=true;
            }
            if (check(line, i, dontString))
            {
                enabled=false;
            }
        }
        bool validSoFar = true;
        for (int j = 0; j < mul.size(); j++)
        {
            if (i+j >= line.size())
            {
                return;
            }

            if (std::string{line[i+j]}.compare(std::string{mul[j]}) != 0)
            {
                validSoFar = false;
                break;
            }
        }

        if (validSoFar)
        {
            bool foundComma = false;
            int counter = 0;
            int firstNumber = 0;
            for (int j = 0; j < 3; j++)
            {
                if (i+mul.length()+j >= line.size())
                {
                    return;
                }
                if (!isdigit(line[i+mul.length()+j]))
                {
                    if (line[i+mul.length()+j] == ',')
                    {
                        foundComma = true;
                        break;
                    }
                }
                else
                {
                    firstNumber = firstNumber*10 + line[i+mul.length()+j] - '0';
                }
                counter++;
            }

            if (counter == 0 || i+mul.length()+counter+1 >= line.size()|| firstNumber == 0)
            {
                continue;
            }

            if (!foundComma && line[i+mul.length()+counter] != ',')
            {
                continue;
            }

            bool foundClosingParenthesis = false;
            int secondNumber = 0;
            int counter2 = 0;
            for (int j = 0; j < 3; j++)
            {
                if (i+mul.length()+counter+1+j >= line.size())
                {
                    return;
                }

                if (!isdigit(line[i+mul.length()+counter+j+1]))
                {
                    if (line[i+mul.length()+counter+j+1] == ')')
                    {
                        foundClosingParenthesis = true;
                        break;
                    }
                }
                else
                {
                    secondNumber = secondNumber*10 + line[i+mul.length()+counter+1+j] - '0';
                }
                counter2++;
            }

            if (foundClosingParenthesis)
            {
                if (enabled)
                {
                    totalSum = totalSum + firstNumber*secondNumber;
                }
                continue;
            }

            if (i+mul.length()+counter+counter2+1 < line.size() && line[i+mul.length()+counter+counter2+1] == ')')
            {
                if (enabled)
                {
                    totalSum = totalSum + firstNumber*secondNumber;
                }
            }
        }
    }
}

void part1()
{
    std::ifstream file("day3/real_input.txt");

    std::string line;
    while (std::getline(file, line))
    {
        calculateLine(line);
    }

    std::cout << totalSum << std::endl;
}

void part2()
{
    totalSum = 0;
    std::ifstream file("day3/real_input.txt");

    std::string line;
    while (std::getline(file, line))
    {
        calculateLine(line, true);
    }

    std::cout << totalSum << std::endl;
}