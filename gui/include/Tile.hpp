/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Tile.hpp
*/

#pragma once

#include <map>
#include <vector>
#include "ResourcesTypes.hpp"
#include "RaylibWrapper.hpp"
#include "Egg.hpp"
#include "Human.hpp"

class Tile
{
public:
    Tile();
    Tile(int x, int y);

    void draw(RaylibWrapper &wrapper, Vector3 center, float lon, float radius, float lat, int segmentsLong, int segmentsLat, std::vector<GameModel> &ressources, GameModel &eggModel, const int &maxTiles);
    int x();
    int y();
    void setX(int x);
    void setY(int y);
    void setBool(bool is_drawn)
    {
        this->_is_drawn = is_drawn;
    };
    bool getBool()
    {
        return this->_is_drawn;
    };
    int getIndex()
    {
        return _index;
    }
    void setWidth(double width) {
        _width = width;
    };
    void setHeight(double height) {
        _height = height;
    };
    double getWidth() {
        return _width;
    };
    double getHeight() {
        return _height;
    };
    void setAimX(int x) {
        _aimX = x;
    };
    void setAimY(int y) {
        _aimY = y;
    };
    void setExplode(double explode) {
        this->explode = explode;
    };
    double getExplode() {
        return this->explode;
    };
    void setLerpSpeed(double lerpSpeed) {
        _lerpSpeed = lerpSpeed;
    };
    void setIsDrawn(bool is_drawn) {
        _is_drawn = is_drawn;
    };
    void setRessources(Tile tile);
    void setRessource(ResourcesTypes type, int nb);
    void addRessource(ResourcesTypes type, int nb);
    void removeRessource(ResourcesTypes type, int nb);
    int getRessource(ResourcesTypes type) const;
    std::map<ResourcesTypes, int> getRessources() const;
    std::vector<std::shared_ptr<Egg>> getEggs();
    void removeEgg(int eggId);
    void addEgg(std::shared_ptr<Egg> egg);
    std::vector<std::shared_ptr<Human>> getHumans();
    void removeHuman(int humanId);
    void addHuman(std::shared_ptr<Human> human);
    bool operator==(const Tile &tile) const;

private:
    bool _is_drawn;
    int _x;
    int _y;
    double explode;
    int _index;
    int _aimX;
    int _aimY;
    double _width;
    double _height;
    double _lerpSpeed;
    Vector3 _normal;
    std::vector<std::shared_ptr<Egg>> _eggs;
    std::vector<std::shared_ptr<Human>> _humans;
    std::vector<Vector3> triangleActualPos;
    std::map<ResourcesTypes, int> _ressources;
    std::map<ResourcesTypes, Vector3> _ressourcesPos;
    std::map<ResourcesTypes, Vector3> _ressourcesActualPos;
    std::map<ResourcesTypes, Vector2> _ressourcesPosScale;
    void findValidRessourcePos(std::pair<ResourcesTypes, int> resource, Vector3 lineUp, Vector3 lineDown, Vector3 lineSide);
    std::tuple<Vector3, Vector3> drawTile(RaylibWrapper &wrapper, float lon, float radius, float lat, int segmentsLong, int segmentsLat, Vector3 center);
};

Vector3 ComputeSpherePoint(float radius, float latitude, float longitude);