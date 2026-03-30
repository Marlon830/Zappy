/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Egg.cpp
*/

#include "Egg.hpp"
#include "Tile.hpp"

Egg::Egg(int id, Tile& position)
    : _id(id), _position(position)
{
    this->_actualPos = {0, -10, 0};
}

void Egg::draw(RaylibWrapper &wrapper, Vector3 normal, GameModel &eggModel, float scale)
{
    eggModel.drawModel(this->_actualPos, normal, scale, WHITE, wrapper, 1);
}

void Egg::setId(int id)
{
    this->_id = id;
}

void Egg::setPosition(Tile& position)
{
    this->_position = position;
}

int Egg::getId()
{
    return this->_id;
}

Tile &Egg::getPosition()
{
    return this->_position;
}
