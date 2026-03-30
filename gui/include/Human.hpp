/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Human.hpp
*/

#pragma once

#include "Tile.hpp"
#include "Team.hpp"
#include "AWindow.hpp"
#include "GameModel.hpp"
#include <chrono>

#define NORTH 1
#define EAST 2
#define SOUTH 3
#define WEST 4

enum class AnimType {
    IDLE = 0,
    WALK,
    COLLECT,
    DROP,
    PRAY_START,
    PRAY,
    PRAY_STOP,
    DEATH
};

class Team;

class Human
{
public:
    Human(Team& team, Vector2 position, int level, int &timeUnit);

    Vector2 getPosition();
    void setPosition(Vector2 position);
    Vector3 getStartPos();
    void setStartPos(Vector3 pos);
    Vector3 getAimPos();
    void setAimPos(Vector3 pos);
    AnimType getAnimType();
    void setAnimType(AnimType animType);
    void setNewPos(bool newPos);
    int getNbPlayed() const;
    float getPercentageProgress();
    Team &getTeam();
    void setRessource(ResourcesTypes type, int nb);
    void addRessource(ResourcesTypes type, int nb);
    void removeRessource(ResourcesTypes type, int nb);
    int getLevel();
    void levelUp();
    std::map<ResourcesTypes, int> &getInventory();
    void setId(int id);
    int getId();
    void setOrientation(int orientation);
    int getOrientation();
    void draw(RaylibWrapper &wrapper, Vector3 normal, float scale);
    std::string getName() {
        return _name;
    }
    std::unique_ptr<Window::AWindow> &getPlayerInfoWindow() {
        return _playerInfoWindow;
    }
    std::unique_ptr<Window::AWindow> &getPlayerPopupWindow() {
        return _playerPopupWindow;
    }
    void setActualPos(Vector3 pos) {
        _actualPos = pos;
    }
    Vector3 getActualPos() {
        return _actualPos;
    }
    bool isClicked(RaylibWrapper &wrapper);
private:
    // GameModel _model;
    int &_timeUnit;
    std::chrono::time_point<std::chrono::system_clock> _startAnim;
    bool _newPos = false;
    float _animDuration;
    AnimType _animType;
    std::vector<GameModel> _models;
    Vector2 _position;
    std::string _name;
    Team& _team;
    std::map<ResourcesTypes, int> _inventory;
    int _level;
    int _id;
    int _orientation;
    Vector3 _startPos;
    Vector3 _actualPos;
    Vector3 _aimPos;
    std::unique_ptr<Window::AWindow> _playerInfoWindow;
    std::unique_ptr<Window::AWindow> _playerPopupWindow;
};
