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

class Formula
{
public:
    long long A;
    long long B;
    long long sum;
};

class TwoUnknowFormulas {
public:
    Formula first;
    Formula second;
    bool possible = false;
    long long solvedA = -1;
    long long solvedB = -1;
};

std::vector<TwoUnknowFormulas> formulas;

long long getFirstNumFromLine(std::string line)
{
    return std::stoll(line.substr(12, line.substr(12).find(" ") - 1));
}

long long getSecondNumFromLine(std::string line)
{
    return std::stoll(line.substr(line.find(",") + 3));
}

long long getXFromLine(std::string line)
{
    return std::stoll(line.substr(line.find("X")+2, line.length()-line.find(",")));
}

long long getYFromLine(std::string line)
{
    std::string temp = line.substr(line.find("Y") + 2);
    return std::stoll(line.substr(line.find("Y") + 2));
}

void solveB(TwoUnknowFormulas& fs)
{
    long long leftSide = fs.first.A * fs.second.sum - fs.second.A * fs.first.sum;
    long long rightSide = fs.first.A * fs.second.B - fs.second.A * fs.first.B;

    if (leftSide < 0)
    {
        leftSide *= -1;
        rightSide *= -1;
    }

    fs.solvedB = leftSide / rightSide;
}

void solveA(TwoUnknowFormulas& fs)
{
    fs.solvedA = (fs.first.sum - fs.first.B * fs.solvedB) / fs.first.A;
}

void setPossible(TwoUnknowFormulas& fs)
{
    bool firstFormula = fs.first.sum == fs.first.A * fs.solvedA + fs.first.B * fs.solvedB;
    bool secondFormula = fs.second.sum == fs.second.A * fs.solvedA + fs.second.B * fs.solvedB;

    fs.possible = firstFormula && secondFormula;
}

void part1()
{
    std::ifstream file("real_input.txt");

    std::string line;
    long counter = 0;
    Formula f1;
    Formula f2;
    while (std::getline(file, line))
    {
        if (counter % 4 == 0)
        {
            f1.A = getFirstNumFromLine(line);
            f2.A = getSecondNumFromLine(line);
        }

        if (counter % 4 == 1)
        {
            f1.B = getFirstNumFromLine(line);
            f2.B = getSecondNumFromLine(line);
        }

        if (counter % 4 == 2)
        {
            f1.sum = getXFromLine(line);
            f2.sum = getYFromLine(line);
        }

        if (counter % 4 == 3)
        {
            TwoUnknowFormulas fs;
            fs.first = f1;
            fs.second = f2;
            formulas.push_back(fs);
        }

        counter++;
    }

    TwoUnknowFormulas fs;
    fs.first = f1;
    fs.second = f2;
    formulas.push_back(fs);

    long tokenCounter = 0;

    for (int i = 0; i < formulas.size();i++)
    {
        solveB(formulas[i]);
        solveA(formulas[i]);
        setPossible(formulas[i]);
        if (formulas[i].possible) {
            tokenCounter += formulas[i].solvedA * 3 + formulas[i].solvedB * 1;
        }
    }

    std::cout << tokenCounter << std::endl;
}

void part2()
{
    long long tokenCounter = 0;
    for (int i = 0; i < formulas.size();i++)
    {
        formulas[i].first.sum += 10000000000000;
        formulas[i].second.sum += 10000000000000;
        solveB(formulas[i]);
        solveA(formulas[i]);
        setPossible(formulas[i]);
        if (formulas[i].possible) {
            tokenCounter += formulas[i].solvedA * 3 + formulas[i].solvedB * 1;
        }
    }

    std::cout << tokenCounter << std::endl;
}