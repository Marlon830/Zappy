/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Firework.hpp
*/

#pragma once

#include "RaylibWrapper.hpp"
#include <raylib.h>
#include <vector>
#include <iostream>

class Firework {
    public :
        Firework(int x, int y, double radius, Color color, double speed);
        Firework(Color color);
        void draw(RaylibWrapper &wrapper);
        void explode(RaylibWrapper &wrapper);
    protected :
        Vector2 aimPos;
        Sound launchSound;
        Sound explodeSound;
        Vector2 actualPos;
        double radius;
        bool _explode;
        Color color;
        double speed;
        int depth;
        bool _soundInit;
        std::vector<Vector3> particlesAimPos;
        std::vector<Vector3> particlesActualPos;
    
};