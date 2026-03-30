/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Firework.cpp
*/

#include "Firework.hpp"
#include <cmath>

Vector3 generateRandomPointOnSphere(float radius)
{
    float theta = static_cast<float>(rand()) / RAND_MAX * 2.0f * M_PI;
    float phi = static_cast<float>(rand()) / RAND_MAX * M_PI;

    float x = radius * sin(phi) * cos(theta);
    float y = radius * sin(phi) * sin(theta);
    float z = radius * cos(phi);

    return {x, y, z};
}

Firework::Firework(int x, int y, double radius, Color color, double speed)
{
    this->aimPos = {0.0f + x, 0.0f + y};
    this->actualPos = {0.0f + x, -100.0f};
    this->radius = radius;
    this->color = Color(color.r + rand() % 10, color.g + rand() % 10, color.b + rand() % 10, 255);
    this->speed = speed;
    this->_explode = false;
    this->depth = 25;
    this->_soundInit = false;
}

Firework::Firework(Color color)
{
    int x = rand() % 10 * (rand() % 2 == 0 ? -1 : 1);
    int y = rand() % 13 * -1;
    this->depth = rand() % 15 + 10;
    this->aimPos = {0.0f + x, 0.0f + y};
    this->actualPos = {0.0f + x, -100};
    this->color = color;
    this->radius = .1;
    this->speed = rand() % 5 + 5;
    _explode = false;
}

Vector2 lerp2d(Vector2 a, Vector2 b, float t)
{
    if (std::abs(a.x - b.x) < 0.1 && std::abs(a.y - b.y) < 0.1)
        return (b);
    return {a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t};
}

Vector3 lerp3d(Vector3 a, Vector3 b, float t)
{
    if (std::abs(a.x - b.x) < 0.1 && std::abs(a.y - b.y) < 0.1 && std::abs(a.z - b.z) < 0.1)
        return (b);
    return {a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t};
}

void Firework::explode(RaylibWrapper &wrapper)
{
    int count = 0;
    if (wrapper.IsSoundPlaying(explodeSound) == false)
    {
        wrapper.PlaySound(explodeSound);
    }
    for (int i = 0; i < particlesAimPos.size(); i++)
    {
        particlesActualPos[i] = lerp3d(particlesActualPos[i], particlesAimPos[i], wrapper.getDeltaTime() * 3);
        float distance = Vector3Distance(particlesActualPos[i], particlesAimPos[i]);
        Color fading = Color(color.r, color.g, color.b, 255 < 50 * distance ? 255 : 50 * distance);
        wrapper.DrawSphere(particlesActualPos[i], 0.05, fading);
        if (particlesActualPos[i].x == particlesAimPos[i].x && particlesActualPos[i].y == particlesAimPos[i].y)
        {
            count++;
        }
    }
    if (count == 36)
    {
        int x = rand() % 15 * (rand() % 2 == 0 ? -1 : 1);
        int y = rand() % 13 * -1;
        this->depth = rand() % 15 + 10;
        this->speed = rand() % 5 + 5;
        this->aimPos = {0.0f + x, 0.0f + y};
        this->actualPos = {0.0f + x, -100};
        this->particlesActualPos.clear();
        this->particlesAimPos.clear();
        _explode = false;
    }
}

void Firework::draw(RaylibWrapper &wrapper)
{
    if (!_soundInit)
    {
        launchSound = wrapper.LoadSound("gui/assets/firework_launch.mp3");
        explodeSound = wrapper.LoadSound("gui/assets/firework_boom.mp3");
        wrapper.PlaySound(launchSound);
        _soundInit = true;
    }
    double dt = wrapper.getDeltaTime();
    actualPos = lerp2d(actualPos, aimPos, dt * speed);
    Vector3 pos3d = {depth, actualPos.y, actualPos.x};
    if (actualPos.x != aimPos.x || actualPos.y != aimPos.y)
    {
        if (wrapper.IsSoundPlaying(launchSound) == false)
        {
            wrapper.PlaySound(launchSound);
        }
        wrapper.DrawSphere(pos3d, this->radius, color);
        return;
    }
    if (_explode == false)
    {
        _explode = true;
        for (int i = 0; i < 36; i++)
        {
            Vector3 pos = generateRandomPointOnSphere(5);
            pos.x += depth;
            pos.y += actualPos.y;
            pos.z += actualPos.x;
            particlesAimPos.push_back(pos);
            particlesActualPos.push_back(pos3d);
        }
    }
    explode(wrapper);
}
