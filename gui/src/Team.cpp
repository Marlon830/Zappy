/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Team.cpp
*/

#include "Team.hpp"
#include "Human.hpp"

Team::Team(std::string name)
    : _name(name), _level(1)
{
}

Team::~Team()
{
}

void Team::addPlayer(std::shared_ptr<Human> human)
{
    this->_members.push_back(human);
}

void Team::removePlayer(int playerId)
{
    for (auto it = this->_members.begin(); it != this->_members.end(); it++) {
        if ((*it)->getId() == playerId) {
            this->_members.erase(it);
            return;
        }
    }
}

std::vector<std::shared_ptr<Human>>& Team::getMembers()
{
    return this->_members;
}

std::string Team::getName()
{
    return this->_name;
}

int Team::getLevel()
{
    return this->_level;
}