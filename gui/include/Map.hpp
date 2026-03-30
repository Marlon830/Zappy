/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Map.hpp
*/

#pragma once

#include <vector>
#include "Tile.hpp"
#include "RaylibWrapper.hpp"
#include "raymath.h"
#include "GameModel.hpp"

class Map
{
public:
    Map(int width, int height);

    std::vector<Tile> &getTiles();
    Tile getTile(int x, int y) const;
    int getWidth() const;
    int getHeight() const;
    void setTile(int x, int y, Tile tile);
    void draw(RaylibWrapper &wrapper);
    // 0 = left, 1 = right, 2 = up, 3 = down
    void rotateMap(int direction);
    void drawSegment(float lon, float radius, float lat, int segmentsLong, int segmentsLat, Vector3 center, RaylibWrapper &wrapper, Color color);
    void lookAtCenter();
    void setCenter(Vector2 center) {
        int x = truePos[center.x + center.y * _width] % _width;
        int y = truePos[center.x + center.y * _width] / _width;
        _center = {(float)x, (float)y};
        _center = center;
    };
    int getWidth() {
        return _width;
    };
    int getHeight() {
        return _height;
    };
    bool operator==(const Map &map) const;
    Vector2 getCenter() {
        return _center;
    };
    Vector2 getPreviousCenter() {
        return _previousCenter;
    };
private:
    std::vector<Tile> _tiles;
    std::vector<int> truePos;
    std::vector<float> randStarPos;
    std::vector<GameModel> _ressources;
    GameModel _egg;
    Vector2 _center;
    Vector2 _previousCenter;
    int _width;
    int _height;
};
