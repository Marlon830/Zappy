/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** GameModel.cpp
*/

#include "GameModel.hpp"
#include <iostream>

GameModel::GameModel(std::string path, std::string texturePath, bool reverse)
{
    this->_path = path;
    this->_texturePath = texturePath;
    this->_reverse = reverse;
    this->_extension = path.substr(path.find_last_of(".") + 1);
}

GameModel::~GameModel()
{
    if (this->_animsCount != -1) {
        RaylibWrapper::UnloadModel(this->_model);
        if (this->_extension == "glb") {
            RaylibWrapper::UnloadModelAnimations(this->_modelAnimations, this->_animsCount);
        }
    }
}

void GameModel::applyOrientation(int orientation)
{
    if (this->_animsCount == -1) {
        return;
    }
    if (this->_orientation == orientation) {
        return;
    }
    if (std::abs(this->_orientation - orientation) == 2) {
        Matrix rotation = MatrixRotateZ(DEG2RAD * 180.0f);
        this->_model.transform = MatrixMultiply(rotation, this->_model.transform);
        this->_orientation = (this->_orientation + 2) % 4;
        return;
    }
    if (orientation == this->_orientation + 1 || (this->_orientation == 4 && orientation == 1)) {
        Matrix rotation = MatrixRotateZ(DEG2RAD * 90.0f);
        this->_model.transform = MatrixMultiply(rotation, this->_model.transform);
        this->_orientation = orientation;
        return;
    }
    if (orientation == this->_orientation - 1 || (this->_orientation == 1 && orientation == 4)) {
        Matrix rotation = MatrixRotateZ(DEG2RAD * -90.0f);
        this->_model.transform = MatrixMultiply(rotation, this->_model.transform);
        this->_orientation = orientation;
        return;
    }
}

int GameModel::getNbPlayed() const
{
    return this->_nbPlayed;
}

void GameModel::resetAnim()
{
    this->_animCurrentFrame = 0;
    this->_nbPlayed = 0;
}

void GameModel::drawModel(Vector3 position, Vector3 normal, float scale, Color tint, RaylibWrapper &wrapper, int orientation)
{
    if (this->_extension == "obj") {
        if (this->_animsCount == -1) {
            this->_model = wrapper.LoadModel(this->_path.c_str());
            Texture2D texture = wrapper.LoadTexture(this->_texturePath.c_str());
            this->_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
            this->_animsCount = 0;
        }
        wrapper.DrawModel(this->_model, position, scale, tint, normal, -90.0f);
    } else if (this->_extension == "glb") {
        if (this->_animsCount == -1) {
            this->_model = wrapper.LoadModel(this->_path.c_str());
            this->_modelAnimations = wrapper.LoadModelAnimations(this->_path.c_str(), &this->_animsCount);
            if (this->_reverse) {
                this->_animCurrentFrame = this->_modelAnimations[this->_animIndex].frameCount - 1;
            }
            this->applyOrientation(orientation);
        }
        ModelAnimation anim = this->_modelAnimations[this->_animIndex];
        if (this->_reverse) {
            this->_animCurrentFrame--;
            if (this->_animCurrentFrame == -1) {
                this->_animCurrentFrame = anim.frameCount - 1;
            }
            if (this->_animCurrentFrame == 0) {
                this->_nbPlayed++;
            }
        } else {
            this->_animCurrentFrame = (this->_animCurrentFrame + 1) % anim.frameCount;
            if (this->_animCurrentFrame == anim.frameCount - 1) {
                this->_nbPlayed++;
            }
        }
        wrapper.UpdateModelAnimation(this->_model, anim, this->_animCurrentFrame);
        wrapper.DrawModel(this->_model, position, scale, tint, normal, -90.0f);
        //wrapper.Draw3DLine(position, Vector3Add(position, Vector3Scale(normal, 5.0f)), RED);
    }
}
