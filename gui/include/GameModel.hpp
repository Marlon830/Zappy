/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** GameModel.hpp
*/

#pragma once

#include "RaylibWrapper.hpp"
#include <memory>

class GameModel
{
public:
    GameModel(std::string path, std::string texturePath = "", bool reverse = false);
    ~GameModel();
    
    void applyOrientation(int orientation);
    int getNbPlayed() const;
    void resetAnim();
    void drawModel(Vector3 position, Vector3 normal, float scale, Color tint, RaylibWrapper &wrapper, int orientation);
private:
    Model _model;
    int _orientation = 1;
    bool _reverse;
    int _nbPlayed = 0;
    int _animsCount = -1;
    unsigned int _animIndex = 0;
    unsigned int _animCurrentFrame = 0;
    ModelAnimation *_modelAnimations;
    std::string _path;
    std::string _texturePath;
    std::string _extension;
};
