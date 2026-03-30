/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** ResourcesTypes.hpp
*/

#pragma once
#include <map>
#include <string>
#include "raylib.h"

enum class ResourcesTypes {
    FOOD = 0,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
};

static std::map<ResourcesTypes, std::string> resourcesNames = {
    {ResourcesTypes::FOOD, "Food"},
    {ResourcesTypes::LINEMATE, "Linemate"},
    {ResourcesTypes::DERAUMERE, "Deraumere"},
    {ResourcesTypes::SIBUR, "Sibur"},
    {ResourcesTypes::MENDIANE, "Mendiane"},
    {ResourcesTypes::PHIRAS, "Phiras"},
    {ResourcesTypes::THYSTAME, "Thystame"}
};

static std::map<ResourcesTypes, Color> resourcesColors = {
    {ResourcesTypes::FOOD, YELLOW},
    {ResourcesTypes::LINEMATE, BLUE},
    {ResourcesTypes::DERAUMERE, GREEN},
    {ResourcesTypes::SIBUR, RED},
    {ResourcesTypes::MENDIANE, PURPLE},
    {ResourcesTypes::PHIRAS, ORANGE},
    {ResourcesTypes::THYSTAME, PINK}
};
