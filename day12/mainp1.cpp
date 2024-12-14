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

class Region;

class Plant
{
    public:
    int iCord;
    int jCord;
    std::string name;
    Region* region = nullptr;
};

class Region
{
    public:
    std::string name;
    std::vector<Plant*> plants;
    int fence = 0;
};

std::vector<std::vector<Plant*>> plants;
std::vector<Region*> regions;
std::vector<Plant*> discoverPlantResult;
std::vector<Plant*> exploredPlants;
long price = 0;

std::vector<Plant*> getValidNeighbours(Plant* plant)
{
    std::vector<Plant*> result;

    if (plant->iCord != 0 and plants[plant->iCord-1][plant->jCord]->name.compare(plant->name) == 0)
    {
        result.emplace_back(plants[plant->iCord-1][plant->jCord]);
    }

    if (plant->iCord != plants.size()-1 and plants[plant->iCord+1][plant->jCord]->name.compare(plant->name) == 0)
    {
        result.emplace_back(plants[plant->iCord+1][plant->jCord]);
    }

    if (plant->jCord != 0 and plants[plant->iCord][plant->jCord-1]->name.compare(plant->name) == 0)
    {
        result.emplace_back(plants[plant->iCord][plant->jCord-1]);
    }

    if (plant->jCord != plants[plant->iCord].size()-1 and plants[plant->iCord][plant->jCord+1]->name.compare(plant->name) == 0)
    {
        result.emplace_back(plants[plant->iCord][plant->jCord+1]);
    }

    return result;
}

void getMatchingPlants(Plant* plant)
{
    auto neighbours = getValidNeighbours(plant);
    for (auto neighbourPlant : neighbours)
    {
        if (std::find(exploredPlants.begin(), exploredPlants.end(), neighbourPlant) != exploredPlants.end())
        {
            continue;
        }
        if (std::find(discoverPlantResult.begin(), discoverPlantResult.end(), neighbourPlant) == discoverPlantResult.end())
        {
            exploredPlants.emplace_back(neighbourPlant);
            discoverPlantResult.emplace_back(neighbourPlant);
            getMatchingPlants(neighbourPlant);
        }
    }
}

void discoverRegion(Plant* plant)
{
    Region* region = new Region;
    region->name = plant->name;
    discoverPlantResult.clear();
    exploredPlants.clear();
    exploredPlants.emplace_back(plant);
    getMatchingPlants(plant);

    plant->region = region;
    region->plants.emplace_back(plant);

    for (auto plant2 : discoverPlantResult)
    {
        plant2->region = region;
        region->plants.emplace_back(plant2);
    }

    regions.emplace_back(region);
}

void calculateFences()
{
    for (int i = 0; i < plants.size(); i++)
    {
        for (int j = 0; j < plants[i].size(); j++)
        {
            int neighbours = 4 - getValidNeighbours(plants[i][j]).size();
            plants[i][j]->region->fence += neighbours;
        }
    }
}

void calculatePrices()
{
    for (int i = 0; i < regions.size(); i++)
    {
        price += regions[i]->fence*regions[i]->plants.size();
    }
}


void clean()
{
    for (auto plant: plants)
    {
        for (auto plant: plant)
        {
            delete plant;
        }
    }

    for (auto region: regions)
    {
        delete region;
    }
}

void part1()
{
    std::ifstream file("day12/real_input.txt");

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<Plant*> plantLine;
        for (int i = 0; i < line.length(); i++)
        {
            Plant* p = new Plant;
            p->name = line[i];
            p->iCord = plants.size();
            p->jCord = i;
            plantLine.push_back(p);
        }
        plants.push_back(plantLine);
    }

    for (int i = 0; i < plants.size(); i++)
    {
        for (int j = 0; j < plants[i].size(); j++)
        {
            if (plants[i][j]->region == nullptr)
            {
                discoverRegion(plants[i][j]);
            }
        }
    }

    calculateFences();
    calculatePrices();

    std::cout << price << std::endl;

    clean();
}

void part2()
{
}