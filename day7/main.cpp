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

bool part2Solving = false;

int main()
{
    //part1();
    part2Solving = true;
    part2();
}

enum OPERATOR{PLUS, TIMES, CONCATENATION};

class CalibrationEquation
{
public:
    long testValue;
    std::vector<long> numbers;
    bool possible=false;
};

std::vector<CalibrationEquation> calibrationEquations;

std::vector<OPERATOR> getInitialOperators(CalibrationEquation calibrationEquation)
{
    std::vector<OPERATOR> result;
    for(int i=0;i<calibrationEquation.numbers.size()-1;i++)
    {
        result.push_back(OPERATOR::PLUS);
    }

    return result;
}

void getNextOperatorCombination(std::vector<OPERATOR>& operatorCombination)
{
    for (int i = 0; operatorCombination.size()>0; i++)
    {
        if (operatorCombination[i] == OPERATOR::PLUS)
        {
            operatorCombination[i] = OPERATOR::TIMES;
            return;
        }
        if (part2Solving && operatorCombination[i] == OPERATOR::TIMES)
        {
            operatorCombination[i] = OPERATOR::CONCATENATION;
            return;
        }

        operatorCombination[i] = OPERATOR::PLUS;
    }
}

bool lastOperatorCombination(std::vector<OPERATOR>& operatorCombination)
{
    for (int i = 0; i < operatorCombination.size(); i++)
    {
        if (operatorCombination[i] == OPERATOR::PLUS || (part2Solving && operatorCombination[i] == OPERATOR::TIMES))
        {
            return false;
        }
    }

    return true;
}

bool calculateTestValue(CalibrationEquation calibrationEquation, std::vector<OPERATOR> operatorCombination)
{
    long value=calibrationEquation.numbers[0];
    for (int i=1; i<calibrationEquation.numbers.size(); i++)
    {
        if (operatorCombination[i-1] == OPERATOR::PLUS)
        {
            value+=calibrationEquation.numbers[i];
        }
        if (operatorCombination[i-1] == OPERATOR::TIMES)
        {
            value*=calibrationEquation.numbers[i];
        }
        if (part2Solving && operatorCombination[i-1] == OPERATOR::CONCATENATION)
        {
            value = std::stol(std::to_string(value) + std::to_string(calibrationEquation.numbers[i]));
        }
    }

    return value == calibrationEquation.testValue;
}

void checkPossibleCombinations(CalibrationEquation& calibrationEquation)
{
    auto operatorCombination = getInitialOperators(calibrationEquation);
    bool lastCombination=false;
    while (!lastCombination)
    {
        if (calculateTestValue(calibrationEquation, operatorCombination))
        {
            calibrationEquation.possible=true;
            return;
        }

        if (!lastOperatorCombination(operatorCombination))
        {
            getNextOperatorCombination(operatorCombination);
        }
        else
        {
            lastCombination=true;
        }
    }
}

void part1()
{
    std::ifstream file("day7/real_input.txt");

    std::string line;

    while (std::getline(file, line))
    {
        CalibrationEquation cal;
        cal.testValue = std::stol(line.substr(0,line.find(':')));

        int number;
        std::istringstream line_stream(line.substr(line.find(':')+1));
        while (line_stream >> number)
        {
            cal.numbers.push_back(number);
        }

        calibrationEquations.push_back(cal);
    }

    long result = 0;
    for (int i=0; i<calibrationEquations.size(); i++)
    {
        checkPossibleCombinations(calibrationEquations[i]);
        if (calibrationEquations[i].possible)
        {
            result += calibrationEquations[i].testValue;
        }
    }

    std::cout << result << std::endl;
}

void part2()
{
    std::ifstream file("day7/real_input.txt");

    std::string line;

    while (std::getline(file, line))
    {
        CalibrationEquation cal;
        cal.testValue = std::stol(line.substr(0,line.find(':')));

        int number;
        std::istringstream line_stream(line.substr(line.find(':')+1));
        while (line_stream >> number)
        {
            cal.numbers.push_back(number);
        }

        calibrationEquations.push_back(cal);
    }

    long result = 0;
    for (int i=0; i<calibrationEquations.size(); i++)
    {
        checkPossibleCombinations(calibrationEquations[i]);
        if (calibrationEquations[i].possible)
        {
            result += calibrationEquations[i].testValue;
        }
    }

    std::cout << result << std::endl;
}