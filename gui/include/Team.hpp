/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Team.hpp
*/

#pragma once

#include <vector>
#include <string>
#include <memory>
#include "raylib.h"

class Human;

class Team
{
public:
    Team(std::string name);
    ~Team();

    std::vector<std::shared_ptr<Human>>& getMembers();
    std::string getName();
    int getLevel();
    void addPlayer(std::shared_ptr<Human> human);
    void removePlayer(int playerId);
    Color getColor() {
        return _color;
    };
    void setColor(Color color) {
        _color = color;
    };
private:
    std::vector<std::shared_ptr<Human>> _members;
    std::string _name;
    int _level;
    Color _color;
};


static std::vector<Color> teamColors = {
    RED,
    BLUE,
    GREEN,
    YELLOW,
    ORANGE,
    PINK,
    PURPLE,
    BROWN,
    BEIGE,
    LIME,
    GOLD,
    SKYBLUE,
    VIOLET,
    DARKBLUE,
    DARKGREEN,
    DARKPURPLE,
    DARKGRAY,
    LIGHTGRAY,
    GRAY,
    BLACK
};