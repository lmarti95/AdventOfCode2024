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

enum FenceLocation {TOP, BOTTOM, LEFT, RIGHT};
enum TraverseLocation {UP, DOWN, LEFTTraverse, RIGHTTraverse};

class Region;

class Fence
{
public:
    bool compacted = false;
    FenceLocation location;
};

class Plant
{
    public:
    int iCord;
    int jCord;
    std::string name;
    Region* region = nullptr;
    std::vector<Fence> fences;
};

class Region
{
    public:
    std::string name;
    std::vector<Plant*> plants;
    int sides = 0;
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

std::vector<Fence> getFencesPlant(Plant* plant)
{
    std::vector<Fence> result;

    if (!(plant->iCord != 0 and plants[plant->iCord-1][plant->jCord]->name.compare(plant->name) == 0))
    {
        Fence fence;
        fence.location = TOP;
        result.emplace_back(fence);
    }

    if (!(plant->iCord != plants.size()-1 and plants[plant->iCord+1][plant->jCord]->name.compare(plant->name) == 0))
    {
        Fence fence;
        fence.location = BOTTOM;
        result.emplace_back(fence);
    }

    if (!(plant->jCord != 0 and plants[plant->iCord][plant->jCord-1]->name.compare(plant->name) == 0))
    {
        Fence fence;
        fence.location = LEFT;
        result.emplace_back(fence);
    }

    if (!(plant->jCord != plants[plant->iCord].size()-1 and plants[plant->iCord][plant->jCord+1]->name.compare(plant->name) == 0))
    {
        Fence fence;
        fence.location = RIGHT;
        result.emplace_back(fence);
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
            plants[i][j]->fences = getFencesPlant(plants[i][j]);
        }
    }
}

Plant* getPlant(Plant* plant, TraverseLocation location)
{
    if (location == UP && plant->iCord != 0 and plants[plant->iCord-1][plant->jCord]->name.compare(plant->name) == 0)
    {
        return plants[plant->iCord-1][plant->jCord];
    }

    if (location == DOWN && plant->iCord != plants.size()-1 and plants[plant->iCord+1][plant->jCord]->name.compare(plant->name) == 0)
    {
        return plants[plant->iCord+1][plant->jCord];
    }

    if (location == LEFTTraverse && plant->jCord != 0 and plants[plant->iCord][plant->jCord-1]->name.compare(plant->name) == 0)
    {
        return plants[plant->iCord][plant->jCord-1];
    }

    if (location == RIGHTTraverse && plant->jCord != plants[plant->iCord].size()-1 and plants[plant->iCord][plant->jCord+1]->name.compare(plant->name) == 0)
    {
        return plants[plant->iCord][plant->jCord+1];
    }

    return nullptr;
}

bool compactFence(Plant* plant, FenceLocation location)
{
    for (int i = 0; i < plant->fences.size(); i++)
    {
        if (plant->fences[i].location == location)
        {
            plant->fences[i].compacted = true;
            return true;
        }
    }

    return false;
}

void compactFences(Plant* plant)
{
    for (int i = 0; i < plant->fences.size(); i++)
    {
        if (plant->fences[i].compacted)
        {
            continue;
        }

        if (plant->fences[i].location == TOP || plant->fences[i].location == BOTTOM)
        {
            Plant* plant2 = getPlant(plant, LEFTTraverse);
            bool foundFence = true;
            while (plant2 != nullptr && foundFence)
            {
                foundFence = compactFence(plant2, plant->fences[i].location);
                plant2 = getPlant(plant2, LEFTTraverse);
            }

            Plant* plant3 = getPlant(plant, RIGHTTraverse);
            foundFence = true;
            while (plant3 != nullptr && foundFence)
            {
                foundFence = compactFence(plant3, plant->fences[i].location);
                plant3 = getPlant(plant3, RIGHTTraverse);
            }
        }
        else
        {
            Plant* plant2 = getPlant(plant, UP);
            bool foundFence = true;
            while (plant2 != nullptr && foundFence)
            {
                foundFence = compactFence(plant2, plant->fences[i].location);
                plant2 = getPlant(plant2, UP);
            }

            Plant* plant3 = getPlant(plant, DOWN);
            foundFence = true;
            while (plant3 != nullptr && foundFence)
            {
                foundFence = compactFence(plant3, plant->fences[i].location);
                plant3 = getPlant(plant3, DOWN);
            }
        }
    }
}

void calculatePrices()
{
    for (int i = 0; i < regions.size(); i++)
    {
        price += regions[i]->sides*regions[i]->plants.size();
    }
}

void calculateSides(Region* region)
{
    for (int i = 0; i < region->plants.size(); i++)
    {
        for (int j = 0; j < region->plants[i]->fences.size(); j++)
        {
            if (!region->plants[i]->fences[j].compacted)
            {
                region->sides++;
            }
        }
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

    for (int i = 0; i < plants.size(); i++)
    {
        for (int j = 0; j < plants[i].size(); j++)
        {
            compactFences(plants[i][j]);
        }
    }

    for (int i = 0; i < regions.size(); i++)
    {
        calculateSides(regions[i]);
    }

    calculatePrices();

    std::cout << price << std::endl;

    clean();
}

void part2()
{
}