/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Human.cpp
*/

#include "Human.hpp"
#include "PlayerInfoWindow.hpp"
#include "PlayerPopupWindow.hpp"
#include <fstream>

Human::Human(Team& team, Vector2 position, int level, int &timeUnit)
    : _timeUnit(timeUnit), _team(team), _position(position), _level(level), _playerInfoWindow(std::make_unique<Window::PlayerInfoWindow>(*this)), _playerPopupWindow(std::make_unique<Window::PlayerPopup>(*this))
{
    //temporary inventory
    this->_inventory[ResourcesTypes::FOOD] = 10;
    this->_inventory[ResourcesTypes::LINEMATE] = 0;
    this->_inventory[ResourcesTypes::DERAUMERE] = 0;
    this->_inventory[ResourcesTypes::SIBUR] = 0;
    this->_inventory[ResourcesTypes::MENDIANE] = 0;
    this->_inventory[ResourcesTypes::PHIRAS] = 0;
    this->_inventory[ResourcesTypes::THYSTAME] = 0;

    //team.addPlayer(std::make_shared<Human>(*this));
    setPosition(position);
    this->_actualPos = {0.0f, -10.0f, 0.0f};

    std::ifstream file("./gui/names.txt");
    std::string line;
    int random = rand() % 1000;
    for (int i = 0; i < random; i++) {
        std::getline(file, line);
    }
    this->_name = line;
    this->_models.push_back(GameModel("gui/assets/idle.glb"));
    this->_models.push_back(GameModel("gui/assets/walk.glb"));
    this->_models.push_back(GameModel("gui/assets/collect.glb"));
    this->_models.push_back(GameModel("gui/assets/collect.glb", "", true));
    this->_models.push_back(GameModel("gui/assets/pray_start_stop.glb", "", true));
    this->_models.push_back(GameModel("gui/assets/pray.glb"));
    this->_models.push_back(GameModel("gui/assets/pray_start_stop.glb"));
    this->_models.push_back(GameModel("gui/assets/death.glb"));
    this->_animType = AnimType::IDLE;
}

Vector2 Human::getPosition()
{
    return this->_position;
}

void Human::setPosition(Vector2 position)
{
    this->_position = position;
}

Vector3 Human::getStartPos()
{
    return this->_startPos;
}

void Human::setStartPos(Vector3 pos)
{
    this->_startPos = pos;
}

Vector3 Human::getAimPos()
{
    return this->_aimPos;
}

void Human::setAimPos(Vector3 pos)
{
    if (this->_newPos == false && this->_animType == AnimType::WALK && !Vector3Equals(this->_aimPos, pos)) {
        this->_startPos = Vector3Add(this->_startPos, Vector3Subtract(pos, this->_aimPos));
    }
    this->_aimPos = pos;
    if (this->_newPos) {
        this->_newPos = false;
    }
}

AnimType Human::getAnimType()
{
    return this->_animType;
}

void Human::setAnimType(AnimType animType)
{
    if (animType == AnimType::WALK) {
        this->_animDuration = 7.0f / static_cast<float>(this->_timeUnit) * 1000.0f;
        this->_startAnim = std::chrono::system_clock::now();
        this->_startPos = this->_actualPos;
    }
    this->_models.at(static_cast<int>(this->_animType)).resetAnim();
    this->_animType = animType;
}

void Human::setNewPos(bool newPos)
{
    this->_newPos = newPos;
}

int Human::getNbPlayed() const
{
    return this->_models.at(static_cast<int>(this->_animType)).getNbPlayed();
}

float Human::getPercentageProgress()
{
    auto now = std::chrono::system_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->_startAnim).count();
    return static_cast<float>(diff) / this->_animDuration;
}

Team &Human::getTeam()
{
    return this->_team;
}

void Human::setRessource(ResourcesTypes type, int nb)
{
    this->_inventory[type] = nb;
}

void Human::addRessource(ResourcesTypes type, int nb)
{
    this->_inventory[type] += nb;
}

void Human::removeRessource(ResourcesTypes type, int nb)
{
    this->_inventory[type] -= nb;
}

int Human::getLevel()
{
    return this->_level;
}

void Human::levelUp()
{
    this->_level++;
}

std::map<ResourcesTypes, int> &Human::getInventory()
{
    return this->_inventory;
}

void Human::setId(int id)
{
    this->_id = id;
}

int Human::getId()
{
    return this->_id;
}

void Human::setOrientation(int orientation)
{
    this->_orientation = orientation;
    for (auto &model : this->_models) {
        model.applyOrientation(orientation);
    }
}

int Human::getOrientation()
{
    return this->_orientation;
}

void Human::draw(RaylibWrapper &wrapper, Vector3 normal, float scale)
{
    // wrapper.DrawSphere(_actualPos, 1.0f, this->_team.getColor());
    if (this->_animType == AnimType::WALK) {
        auto now = std::chrono::system_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->_startAnim).count();
        if (diff > this->_animDuration) {
            this->_models.at(static_cast<int>(this->_animType)).resetAnim();
            this->_animType = AnimType::IDLE;
        }
    }
    this->_models.at(static_cast<int>(this->_animType)).drawModel(this->_actualPos, normal, scale, this->_team.getColor(), wrapper, this->_orientation);
}

bool Human::isClicked(RaylibWrapper &wrapper)
{
    Vector2 mousePos = GetMousePosition();
    Ray ray = GetScreenToWorldRay(mousePos, wrapper.getCamera());
    RayCollision collision = GetRayCollisionSphere(ray, _actualPos, 1.0f);
    if (collision.hit) {
        return true;
    }
    return false;
}
