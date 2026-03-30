/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** GameState.hpp
*/

#pragma once

#include <vector>
#include "Point2d.hpp"
#include "Team.hpp"
#include "Map.hpp"
#include "Egg.hpp"
#include "Human.hpp"

enum class ModificationType {
    MODIFY_MAP = 0,
    NEW_PLAYER,
    EGG_LAYED,
    EGG_DIED,
    PLAYER_COLLECT,
    PLAYER_DROP,
    PLAYER_FOOD,
    PLAYER_DIED,
    SET_TIME_UNIT,
    UPDATE_TIME_UNIT
};

class GameState
{
public:
    GameState();
    ~GameState();

    std::vector<std::string> split(std::string str, std::string delim);
    void draw(RaylibWrapper &wrapper);
    void addTeam(std::string name);
    void modify(ModificationType type, std::string data);
private:
    int _timeUnit;
    Map _map;
    std::vector<Team> _teams;
    std::vector<std::shared_ptr<Egg>> _eggs;
    std::vector<std::shared_ptr<Human>> _humans;
};
