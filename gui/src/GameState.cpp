/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** GameState.cpp
*/

#include "GameState.hpp"

GameState::GameState()
    : _map(1, 1), _timeUnit(100)
{
}

GameState::~GameState()
{
}

std::vector<std::string> GameState::split(std::string str, std::string delim)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;

    while ((pos = str.find(delim)) != std::string::npos) {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delim.length());
    }
    tokens.push_back(str);
    return tokens;
}

void GameState::draw(RaylibWrapper &wrapper)
{
    this->_map.draw(wrapper);
}

void GameState::addTeam(std::string name)
{
    this->_teams.push_back(Team(name));
}

void GameState::modify(ModificationType type, std::string data)
{
    if (type == ModificationType::MODIFY_MAP) {
        while (data.find("\n") != std::string::npos) {
            std::string line = data.substr(0, data.find("\n"));
            std::vector<std::string> tokens = this->split(line, " ");
            int x = std::stoi(tokens[0]);
            int y = std::stoi(tokens[1]);
            std::vector<Tile> &tiles = this->_map.getTiles();
            tiles[y * this->_map.getWidth() + x].setRessource(ResourcesTypes::FOOD, std::stoi(tokens[2]));
            tiles[y * this->_map.getWidth() + x].setRessource(ResourcesTypes::LINEMATE, std::stoi(tokens[3]));
            tiles[y * this->_map.getWidth() + x].setRessource(ResourcesTypes::DERAUMERE, std::stoi(tokens[4]));
            tiles[y * this->_map.getWidth() + x].setRessource(ResourcesTypes::SIBUR, std::stoi(tokens[5]));
            tiles[y * this->_map.getWidth() + x].setRessource(ResourcesTypes::MENDIANE, std::stoi(tokens[6]));
            tiles[y * this->_map.getWidth() + x].setRessource(ResourcesTypes::PHIRAS, std::stoi(tokens[7]));
            tiles[y * this->_map.getWidth() + x].setRessource(ResourcesTypes::THYSTAME, std::stoi(tokens[8]));
            data.erase(0, data.find("\n") + 1);
        }
    } else if (type == ModificationType::NEW_PLAYER) {
        std::vector<std::string> tokens = this->split(data, " ");
        int playerId = std::stoi(tokens[0]);
        int x = std::stoi(tokens[1]);
        int y = std::stoi(tokens[2]);
        int orientation = std::stoi(tokens[3]);
        int level = std::stoi(tokens[4]);
        std::string teamName = tokens[5];
        for (auto &team : this->_teams) {
            if (team.getName() == teamName) {
                std::shared_ptr<Human> human = std::make_shared<Human>(team, Vector2(x * 1.0f, y * 1.0f), level, this->_timeUnit);
                this->_humans.push_back(human);
                this->_humans.back().get()->setId(playerId);
                this->_humans.back().get()->setOrientation(orientation);
                break;
            }
        }
        this->_map.getTiles()[y * this->_map.getWidth() + x].addHuman(this->_humans.back());
        if (tokens.size() > 6) {
            int eggId = std::stoi(tokens[6]);
            for (auto it = this->_eggs.begin(); it != this->_eggs.end(); it++) {
                if (it->get()->getId() == eggId) {
                    this->_map.getTiles()[it->get()->getPosition().y() * this->_map.getWidth() + it->get()->getPosition().x()].removeEgg(eggId);
                    this->_eggs.erase(it);
                    break;
                }
            }
        }
    } else if (type == ModificationType::EGG_LAYED) {
        std::vector<std::string> tokens = this->split(data, " ");
        int eggId = std::stoi(tokens[0]);
        int x = std::stoi(tokens[1]);
        int y = std::stoi(tokens[2]);
        std::shared_ptr<Egg> egg = std::make_shared<Egg>(eggId, this->_map.getTiles()[y * this->_map.getWidth() + x]);
        this->_eggs.push_back(egg);
        this->_map.getTiles()[y * this->_map.getWidth() + x].addEgg(this->_eggs.back());
    } else if (type == ModificationType::EGG_DIED) {
        int eggId = std::stoi(data);
        for (auto it = this->_eggs.begin(); it != this->_eggs.end(); it++) {
            if (it->get()->getId() == eggId) {
                this->_map.getTiles()[it->get()->getPosition().y() * this->_map.getWidth() + it->get()->getPosition().x()].removeEgg(eggId);
                this->_eggs.erase(it);
                break;
            }
        }
    } else if (type == ModificationType::PLAYER_COLLECT) {
        std::vector<std::string> tokens = this->split(data, " ");
        int playerId = std::stoi(tokens[0]);
        ResourcesTypes type = static_cast<ResourcesTypes>(std::stoi(tokens[1]));
        for (auto &human : this->_humans) {
            if (human->getId() == playerId) {
                human->addRessource(type, 1);
                this->_map.getTiles()[human->getPosition().y * this->_map.getWidth() + human->getPosition().x].removeRessource(type, 1);
                break;
            }
        }
    } else if (type == ModificationType::PLAYER_DROP) {
        std::vector<std::string> tokens = this->split(data, " ");
        int playerId = std::stoi(tokens[0]);
        ResourcesTypes type = static_cast<ResourcesTypes>(std::stoi(tokens[1]));
        for (auto &human : this->_humans) {
            if (human->getId() == playerId) {
                human->removeRessource(type, 1);
                this->_map.getTiles()[human->getPosition().y * this->_map.getWidth() + human->getPosition().x].addRessource(type, 1);
                break;
            }
        }
    } else if (type == ModificationType::PLAYER_FOOD) {
        std::vector<std::string> tokens = this->split(data, " ");
        int playerId = std::stoi(tokens[0]);
        int food = std::stoi(tokens[1]);
        for (auto &human : this->_humans) {
            if (human->getId() == playerId) {
                human->setRessource(ResourcesTypes::FOOD, food);
                break;
            }
        }
    } else if (type == ModificationType::PLAYER_DIED) {
        int playerId = std::stoi(data);
        for (auto it = this->_humans.begin(); it != this->_humans.end(); it++) {
            if (it->get()->getId() == playerId) {
                this->_map.getTiles()[it->get()->getPosition().y * this->_map.getWidth() + it->get()->getPosition().x].removeHuman(playerId);
                this->_humans.erase(it);
                break;
            }
        }
    } else if (type == ModificationType::SET_TIME_UNIT) {
        this->_timeUnit = std::stoi(data);
    } else if (type == ModificationType::UPDATE_TIME_UNIT) {
        this->_timeUnit = std::stoi(data);
    }
}
