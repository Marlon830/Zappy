/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Map.cpp
*/

#include "Map.hpp"
#include <iostream>
#include <cmath>

Map::Map(int width, int height)
    : _egg("gui/assets/the_rock.obj", "gui/assets/the_rock.png")
{
    this->_width = width;
    this->_height = height;
    this->_tiles = std::vector<Tile>(width * height);
    for (int i = 0; i < width * height; i++) {
        this->truePos.push_back(i);
        this->_tiles[i] = Tile(i % width, i / width);
    }
    this->_center = {0, 0};
    this->_previousCenter = {0, 0};
    this->_ressources.push_back(GameModel("gui/assets/food.obj", "gui/assets/food.png"));
    this->_ressources.push_back(GameModel("gui/assets/linemate.obj", "gui/assets/linemate.png"));
    this->_ressources.push_back(GameModel("gui/assets/deraumere.obj", "gui/assets/deraumere.png"));
    this->_ressources.push_back(GameModel("gui/assets/sibur.obj", "gui/assets/sibur.png"));
    this->_ressources.push_back(GameModel("gui/assets/mendiane.obj", "gui/assets/mendiane.png"));
    this->_ressources.push_back(GameModel("gui/assets/phiras.obj", "gui/assets/phiras.png"));
    this->_ressources.push_back(GameModel("gui/assets/thystame.obj", "gui/assets/thystame.png"));
}

std::vector<Tile> &Map::getTiles()
{
    return this->_tiles;
}

Tile Map::getTile(int x, int y) const
{
    return this->_tiles[y * this->_width + x];
}

int Map::getWidth() const
{
    return this->_width;
}

int Map::getHeight() const
{
    return this->_height;
}

void Map::setTile(int x, int y, Tile tile)
{
    this->_tiles[y * this->_width + x] = tile;
}

void DrawLatitudeLines(Vector3 center, float radius, int segments, RaylibWrapper &wrapper) {
    for (int i = 1; i < segments; i++) {
        float latitude = PI * i / segments;
        float y = radius * cosf(latitude);
        float r = radius * sinf(latitude);

        Vector3 start = { center.x + r, center.y + y, center.z };
        for (int j = 1; j <= segments; j++) {
            float longitude = 2.0f * PI * j / segments;
            Vector3 end = {
                center.x + r * cosf(longitude),
                center.y + y,
                center.z + r * sinf(longitude)
            };

            wrapper.Draw3DLine(start, end, DARKGRAY);
            start = end;
        }
    }
}

// Function to draw longitude lines
void DrawLongitudeLines(Vector3 center, float radius, int segments, RaylibWrapper &wrapper) {
    for (int i = 0; i < segments; i++) {
        float longitude = 2.0f * PI * i / segments;
        Vector3 start = { center.x + radius * cosf(longitude), center.y, center.z + radius * sinf(longitude) };

        for (int j = 1; j < segments; j++) {
            float latitude = PI * j / segments;
            float y = radius * cosf(latitude);
            float r = radius * sinf(latitude);

            Vector3 end = {
                center.x + r * cosf(longitude),
                center.y + y,
                center.z + r * sinf(longitude)
            };

            wrapper.Draw3DLine(start, end, DARKGRAY);
            start = end;
        }
    }
}

Vector3 ComputeSpherePoint(float radius, float latitude, float longitude) {
    return (Vector3){
        radius * sinf(latitude) * cosf(longitude),
        radius * cosf(latitude),
        radius * sinf(latitude) * sinf(longitude)
    };
}

void Map::draw(RaylibWrapper &wrapper)
{
    Vector2 screenSize = wrapper.GetScreenSize();
    Vector3 center = {0, -10.0f, 0};
    float radius = 20.0f;
    int segmentsLong = std::max(this->_width, this->_height) * 2;
    int segmentsLat = std::max(this->_width, this->_height);
    for (int i = 0; i < this->_width * this->_height; i++) {
        int truex = i % this->_width;
        int truey = i / this->_width;
        this->_tiles[truePos[this->_width - 1 - truex + this->_width * truey]].draw(wrapper, center, truex - ((_width % 2 ? _width + 1 : _width) / 2), radius, truey + (segmentsLat - _height) / 2, segmentsLong, segmentsLat, this->_ressources, this->_egg, std::max(this->_width, this->_height));   
    }
    /* for (int lat = 0; lat < segmentsLat; lat++) {
        float lat1 = PI * lat / segmentsLat;
        float lat2 = PI * (lat + 1) / segmentsLat;

        for (int lon = 0; lon < segmentsLong; lon++) {
            if (((segmentsLat - _height) / 2 <= lat && lat < (segmentsLat + _height) / 2) && (lon < _width / 2 || lon >= segmentsLong - ((_width % 2 ? _width + 1 : _width) / 2)))
                continue;
            drawSegment(lon, radius, lat, segmentsLong, segmentsLat, center, wrapper, LIGHTGRAY);
        }
    } */
}

void Map::lookAtCenter()
{
    int xdif = this->_previousCenter.x - this->_center.x;
    int ydif = this->_previousCenter.y - this->_center.y;
    for (int i = 0; i < this->_width * this->_height; i++) {
        int j = truePos[i];
        int newX = (j - xdif) < 0 ? this->_width - xdif + j : (j - xdif) % this->_width;
        int newY = ((j / _width) - ydif) < 0 ? this->_height - ydif + (j / _width) : (j / _width - ydif) % this->_height;
        truePos[i] = newY * this->_width + newX;
    }
    _previousCenter = _center;
}

void Map::rotateMap(int direction)
{    
    _previousCenter = _center;
    if (direction == 0) {
        _center.x += 1;
        if (_center.x > _width)
            _center.x = _center.x - _width;
    } else if (direction == 1) {
        _center.x -= 1;
        if (_center.x < 0)
            _center.x = _width + _center.x;
    } else if (direction == 2) {
        _center.y += 1;
        if (_center.y > _height)
            _center.y = _center.y - _height;
    } else if (direction == 3) {
        _center.y -= 1;
        if (_center.y < 0)
            _center.y = _height + _center.y;
    }
    lookAtCenter();
}

bool Map::operator==(const Map &map) const
{
    if (this->_width != map.getWidth() || this->_height != map.getHeight())
        return false;
    for (int x = 0; x < this->_width; x++) {
        for (int y = 0; y < this->_height; y++) {
            if (this->getTile(x, y) != map.getTile(x, y))
                return false;
        }
    }
    return true;
}
