/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Tile.cpp
*/

#include "Tile.hpp"
#include <random>
#include <iostream>


Tile::Tile()
{
    this->_x = 0;
    this->_y = 0;
    this->_ressources[ResourcesTypes::FOOD] = 0;
    this->_ressources[ResourcesTypes::LINEMATE] = 0;
    this->_ressources[ResourcesTypes::DERAUMERE] = 0;
    this->_ressources[ResourcesTypes::SIBUR] = 0;
    this->_ressources[ResourcesTypes::MENDIANE] = 0;
    this->_ressources[ResourcesTypes::PHIRAS] = 0;
    this->_ressources[ResourcesTypes::THYSTAME] = 0;
    this->_is_drawn = true;
}

Tile::Tile(int x, int y)
{
    this->_x = x;
    this->_y = y;
    this->explode = -1;
    this->_index = y + x;
    for (int i = 0; i < 4; i++)
        this->triangleActualPos.push_back({0, -10, 0});
    this->_ressources[ResourcesTypes::FOOD] = 0;
    this->_ressources[ResourcesTypes::LINEMATE] = 0;
    this->_ressources[ResourcesTypes::DERAUMERE] = 0;
    this->_ressources[ResourcesTypes::SIBUR] = 0;
    this->_ressources[ResourcesTypes::MENDIANE] = 0;
    this->_ressources[ResourcesTypes::PHIRAS] = 0;
    this->_ressources[ResourcesTypes::THYSTAME] = 0;
    for (auto &resource : this->_ressources) {
        this->_ressourcesActualPos[resource.first] = {0, 0, 0};
        this->_ressourcesPosScale[resource.first] = {(float)drand48(), (float)drand48()};
    }
    this->_is_drawn = true;
}

bool doCubesIntersect(Vector3 cube1Pos, Vector3 cube1Size, Vector3 cube2Pos, Vector3 cube2Size)
{
    if (cube1Pos.x + cube1Size.x < cube2Pos.x || cube1Pos.x > cube2Pos.x + cube2Size.x)
        return false;
    if (cube1Pos.y + cube1Size.y < cube2Pos.y || cube1Pos.y > cube2Pos.y + cube2Size.y)
        return false;
    if (cube1Pos.z + cube1Size.z < cube2Pos.z || cube1Pos.z > cube2Pos.z + cube2Size.z)
        return false;
    return true;
}

void Tile::findValidRessourcePos(std::pair<ResourcesTypes, int> resource, Vector3 lineUp, Vector3 lineDown, Vector3 lineSide)
{
    Vector3 vX = Vector3(0, 0, 0);
    if (_ressourcesPosScale[resource.first].y < .5)
        vX = Vector3Scale(lineUp, _ressourcesPosScale[resource.first].x);
    else
        vX = Vector3Scale(Vector3Normalize(lineUp), _ressourcesPosScale[resource.first].x * Vector3Length(lineDown));
    Vector3 vY = Vector3Scale(lineSide, _ressourcesPosScale[resource.first].y);
    Vector3 randPos = Vector3Add(vX, vY);
    //randPos = Vector3Add(randPos, Vector3Scale(_normal, .2f));
    this->_ressourcesPos[resource.first] = randPos;
}

Vector3 lerp(Vector3 actualPos, Vector3 aimPos, float speed, float dt) {
    Vector3 diff = Vector3Subtract(aimPos, actualPos);
    if (Vector3Length(diff) < (speed * dt))
        return aimPos;
    Vector3 res = Vector3Add(actualPos, Vector3Scale(diff, speed * dt));
    return res;
}

std::tuple<Vector3, Vector3> Tile::drawTile(RaylibWrapper &wrapper, float lon, float radius, float lat, int segmentsLong, int segmentsLat, Vector3 center)
{
    float lon1 = 2.0f * PI * lon / segmentsLong;
    float lon2 = 2.0f * PI * (lon + 1) / segmentsLong;
    float lat1 = PI * lat / segmentsLat;
    float lat2 = PI * (lat + 1) / segmentsLat;

    Vector3 p1 = ComputeSpherePoint(radius, lat1, lon1);
    Vector3 p2 = ComputeSpherePoint(radius, lat2, lon1);
    Vector3 p3 = ComputeSpherePoint(radius, lat2, lon2);
    Vector3 p4 = ComputeSpherePoint(radius, lat1, lon2);
    //point between p1 and p3
    p1 = Vector3Add(p1, center);
    p2 = Vector3Add(p2, center);
    p3 = Vector3Add(p3, center);
    p4 = Vector3Add(p4, center);
    float tileWidth = Vector3Distance(p1, p4);
    float tileHeight = Vector3Distance(p1, p2);
    Vector3 line1 = Vector3Subtract(p2, p1);
    Vector3 line2 = Vector3Subtract(p4, p1);

    this->triangleActualPos[0] = lerp(this->triangleActualPos[0], p1, _lerpSpeed, wrapper.getDeltaTime());
    this->triangleActualPos[1] = lerp(this->triangleActualPos[1], p2, _lerpSpeed, wrapper.getDeltaTime());
    this->triangleActualPos[2] = lerp(this->triangleActualPos[2], p3, _lerpSpeed, wrapper.getDeltaTime());
    this->triangleActualPos[3] = lerp(this->triangleActualPos[3], p4, _lerpSpeed, wrapper.getDeltaTime());
    if (_is_drawn) {
        wrapper.Draw3DTriangle(this->triangleActualPos[0], this->triangleActualPos[1], this->triangleActualPos[2], _index % 2 == 0 ? GREEN : DARKGREEN);
        wrapper.Draw3DTriangle(this->triangleActualPos[0], this->triangleActualPos[2], this->triangleActualPos[3], _index % 2 == 0 ? GREEN : DARKGREEN);
        //std::cout << this->triangleActualPos[0].x << " " << this->triangleActualPos[0].y << " " << this->triangleActualPos[0].z << std::endl;
    }
    this->setWidth(tileWidth);
    this->setHeight(tileHeight);
    this->_normal = Vector3Scale(Vector3Normalize(Vector3CrossProduct(Vector3Subtract(p2, p1), Vector3Subtract(p4, p1))), -1);
    return {line1, line2};
}


std::vector<Vector3> generateCirclePoints(const Vector3& center, const Vector3& normal, float radius, int numPoints) {
    std::vector<Vector3> points;
    points.reserve(numPoints);
    if (numPoints == 1) {
        points.push_back(center);
        return points;
    }

    // Find a vector on the plane
    Vector3 arbitraryVec = Vector3CrossProduct(normal, Vector3(1, 0, 0));
    if (arbitraryVec.x == 0 && arbitraryVec.y == 0 && arbitraryVec.z == 0) {
        arbitraryVec = Vector3CrossProduct(normal, Vector3(0, 1, 0));
    }
    Vector3 u = Vector3Normalize(arbitraryVec);
    Vector3 v = Vector3Normalize(Vector3CrossProduct(normal, u));

    for (int i = 0; i < numPoints; ++i) {
        float angle = 2 * M_PI * i / numPoints;
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);
        Vector3 point = center + u * x + v * y;
        points.push_back(point);
    }

    return points;
}


void Tile::draw(RaylibWrapper &wrapper, Vector3 center, float lon, float radius, float lat, int segmentsLong, int segmentsLat, std::vector<GameModel> &ressources, GameModel &eggModel, const int &maxTiles)
{
    int i = 0;
    
    //if (this->_humans.size() > 0)
    if (this->_normal.x == 0 && this->_normal.y == 0 && this->_normal.z == 0)
        this->_normal = {0, 1, 0};
    if (this->explode != -1) {
        double time = wrapper.getEllapsedTime() - explode;
        if (time <= 5.0f) {
            center = Vector3Add(center, {(rand() % 2 ? 1.0f : -1.0f) * (rand() % 2) * 0.5f * float(time), (rand() % 2 ? 1.0f : -1.0f) * (rand() % 2) * 0.5f * float(time), (rand() % 2 ? 1.0f : -1.0f) * (rand() % 2) * 0.5f * float(time)});
        }
        if (time > 5.0f) {
            _lerpSpeed = 5.0f;
            center = Vector3Add(center, Vector3Scale(_normal, 50.0f));
        }
    }
    float lon1 = 2.0f * PI * lon / segmentsLong;
    float lon2 = 2.0f * PI * (lon + 1) / segmentsLong;
    float lat1 = PI * lat / segmentsLat;
    float lat2 = PI * (lat + 1) / segmentsLat;
    Vector3 p1 = Vector3Add(ComputeSpherePoint(radius, lat1, lon1), center);
    Vector3 p2 = Vector3Add(ComputeSpherePoint(radius, lat2, lon2), center);
    Vector3 p3 = Vector3Add(ComputeSpherePoint(radius, lat2, lon1), center);
    Vector3 middle = Vector3Scale(Vector3Add(p1, p2), 0.5f);
    std::tuple<Vector3, Vector3> lines = drawTile(wrapper, lon, radius, lat, segmentsLong, segmentsLat, center);
    Vector3 line1 = std::get<0>(lines);
    Vector3 line2 = std::get<1>(lines);
    Vector3 line3 = Vector3Subtract(p3, p2);
    for (auto &ressource : this->_ressources) {
        if (ressource.second <= 0)
            continue;
        int nb = ressource.second;
        findValidRessourcePos(ressource, line2, line3, line1);
        if (ressource.second > 0) {
            Vector3 aimPos = Vector3Add(this->_ressourcesPos[ressource.first], p1);
            Vector3 actualPos = lerp(this->_ressourcesActualPos[ressource.first], aimPos, _lerpSpeed, wrapper.getDeltaTime());
            this->_ressourcesActualPos[ressource.first] = actualPos;
            if (_is_drawn) {
                float scale = nb;
                if (ressource.first == ResourcesTypes::FOOD)
                    scale *= 0.005f;
                else
                    scale *= 0.2f;
                scale *= std::max((15.0f / maxTiles), 1.0f);
                ressources.at(static_cast<int>(ressource.first)).drawModel(actualPos, Vector3Scale(line1, -1), scale, WHITE, wrapper, 1);
            }
        }
    }
    std::vector<Vector3> circularEggsPoints = generateCirclePoints(middle, _normal, 0.5f, this->_eggs.size());
    for (auto &egg : this->_eggs) {
        Vector3 aimPos = circularEggsPoints[i];
        Vector3 actualPos = lerp(egg.get()->getActualPos(), aimPos, _lerpSpeed, wrapper.getDeltaTime());
        egg.get()->setActualPos(actualPos);
        if (_is_drawn)
            egg->draw(wrapper, Vector3Scale(line1, -1), eggModel, 0.1f * std::max((15.0f / maxTiles), 1.0f));
        i++;
    }
    i = 0;
    std::vector<Vector3> circularHumansPoints = generateCirclePoints(middle, _normal, 0.5f, this->_humans.size());
    for (auto &human : this->_humans) {
        if (human->getAnimType() == AnimType::DEATH && human->getNbPlayed() >= 1) {
            this->removeHuman(human->getId());
            continue;
        }
        if ((human->getAnimType() == AnimType::COLLECT || human->getAnimType() == AnimType::DROP || human->getAnimType() == AnimType::PRAY_STOP) && human->getNbPlayed() >= 1) {
            human->setAnimType(AnimType::IDLE);
        }
        if (human->getAnimType() == AnimType::PRAY_START && human->getNbPlayed() >= 1) {
            human->setAnimType(AnimType::PRAY);
        }
        Vector3 aimPos = circularHumansPoints[i];
        human->setAimPos(aimPos);
        Vector3 actualPos;
        if (human->getAnimType() == AnimType::WALK) {
            float progress = human->getPercentageProgress();
            actualPos = Vector3Add(human->getStartPos(), Vector3Scale(Vector3Subtract(human->getAimPos(), human->getStartPos()), progress));
            actualPos = lerp(human.get()->getActualPos(), actualPos, this->_lerpSpeed, wrapper.getDeltaTime());
        } else {
            actualPos = lerp(human.get()->getActualPos(), aimPos, this->_lerpSpeed, wrapper.getDeltaTime());
        }
        human.get()->setActualPos(actualPos);
        if (_is_drawn)
            human.get()->draw(wrapper, Vector3Scale(line1, -1), 0.01f * std::max((15.0f / maxTiles), 1.0f));
        i++;
    }
}

int Tile::x()
{
    return this->_x;
}

int Tile::y()
{
    return this->_y;
}

void Tile::setX(int x)
{
    this->_x = x;
}

void Tile::setY(int y)
{
    this->_y = y;
}

void Tile::setRessources(Tile tile)
{
    this->_ressources = tile.getRessources();
}

void Tile::setRessource(ResourcesTypes type, int nb)
{
    this->_ressources[type] = nb;
}

void Tile::addRessource(ResourcesTypes type, int nb)
{
    this->_ressources[type] += nb;
}

void Tile::removeRessource(ResourcesTypes type, int nb)
{
    this->_ressources[type] -= nb;
}

int Tile::getRessource(ResourcesTypes type) const
{
    return this->_ressources.at(type);
}

std::map<ResourcesTypes, int> Tile::getRessources() const
{
    return this->_ressources;
}

std::vector<std::shared_ptr<Egg>> Tile::getEggs()
{
    return this->_eggs;
}

void Tile::removeEgg(int eggId)
{
    for (auto it = this->_eggs.begin(); it != this->_eggs.end(); it++) {
        if (it->get()->getId() == eggId) {
            this->_eggs.erase(it);
            return;
        }
    }
}

void Tile::addEgg(std::shared_ptr<Egg> egg)
{
    this->_eggs.push_back(egg);
}

std::vector<std::shared_ptr<Human>> Tile::getHumans()
{
    return this->_humans;
}

void Tile::removeHuman(int humanId)
{
    std::cout << "removing human on tile : " << this->_index << std::endl;
    for (auto it = this->_humans.begin(); it != this->_humans.end(); it++) {
        if (it->get()->getId() == humanId) {
            this->_humans.erase(it);
            return;
        }
    }
}

void Tile::addHuman(std::shared_ptr<Human> human)
{
    this->_humans.push_back(human);
}

bool Tile::operator==(const Tile &tile) const
{
    for (auto &ressource : this->_ressources) {
        if (ressource.second != tile.getRessource(ressource.first)) {
            return false;
        }
    }
    return true;
}
