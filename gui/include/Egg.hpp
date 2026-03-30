/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Egg.hpp
*/

#pragma once

#include "Team.hpp"
#include "RaylibWrapper.hpp"
#include "GameModel.hpp"

class Tile;

class Egg
{
public:
    Egg(int id, Tile& position);

    void draw(RaylibWrapper &wrapper, Vector3 normal, GameModel &eggModel, float scale);

    void setId(int id);
    void setPosition(Tile& position);
    void setActualPos(Vector3 pos) {
        _actualPos = pos;
    };
    Vector3 getActualPos() {
        return _actualPos;
    };
    int getId();
    Tile &getPosition();
private:
    Tile& _position;
    Vector3 _actualPos;
    int _id;
};
