/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Raylib.hpp
*/

#pragma once

#include <string>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"


class RaylibWrapper {
public:
    RaylibWrapper(int width, int height, std::string title);
    ~RaylibWrapper();

    void BeginDrawing();
    void EndDrawing();
    void ClearBackground(Color color);
    bool WindowShouldClose();
    double getDeltaTime();

    void DrawText(std::string text, int posX, int posY, int fontSize, Color color);
    void DrawRectangleFilled(int posX, int posY, int width, int height, Color color);
    void DrawRectangleOutline(int posX, int posY, int width, int height, Color color);
    void DrawRectangleOutline(int posX, int posY, int width, int height, Color color, float thickness);
    void Draw3DLine(Vector3 begin, Vector3 end, Color color);
    void Draw3DCircle(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color);
    void UpdateCamera(CameraMode mode);
    void DrawSphereWire(Vector3 center, float radius, int rings, int slices, Color color);
    void drawCube(Vector3 position, Vector3 size, Color color);
    void drawCube(Vector3 position, Vector3 size, Color color, Vector3 normal);
    void Draw3DPoint(Vector3 position, Color color);
    void Draw3DTriangle(Vector3 v1, Vector3 v2, Vector3 v3, Color color);
    Vector2 GetMousePosition();
    Vector2 GetScreenSize();
    Camera &getCamera() { return this->camera; }
    void DrawSphere(Vector3 center, float radius, Color color);
    void enableDepthTest();
    Vector3 getCameraPosition();
    void setCameraPosition(Vector3 position) {
        this->camera.position = position;
    };
    double getEllapsedTime();
    Vector3 getInitCameraPosition() {
        return initCameraPosition;
    };
    bool isMouseButtonPressed(int button) {
        return IsMouseButtonPressed(button);
    };
    Model LoadModel(std::string path);
    Texture2D LoadTexture(std::string path);
    ModelAnimation *LoadModelAnimations(std::string path, int *animsCount);
    Matrix MatrixRotateX(float angle);
    Matrix MatrixRotateZ(float angle);
    Matrix MatrixMultiply(Matrix left, Matrix right);
    void UpdateModelAnimation(Model model, ModelAnimation anim, int frame);
    void DrawModel(Model model, Vector3 position, float scale, Color tint);
    void DrawModel(Model model, Vector3 position, float scale, Color tint, Vector3 rotationAxis, float rotationAngle);
    static void UnloadModel(Model model);
    static void UnloadModelAnimations(ModelAnimation *modelAnimations, int animsCount);
    void Draw3Dline(Vector3 line, Color color);
    void setGameSpeed(int speed) {
        this->gameSpeed = speed;
    };
    int getGameSpeed() {
        return this->gameSpeed;
    };
    Sound LoadSound(std::string path);
    void PlaySound(Sound sound);
    void UnloadSound(Sound sound);
    bool IsSoundPlaying(Sound sound);
private:
    int screenWidth;
    int screenHeight;
    int gameSpeed;
    std::string windowTitle;
    Camera camera;
    Vector3 initCameraPosition;
};

Vector3 operator+(Vector3 const &a, Vector3 const &b);

Vector3 operator-(Vector3 const &a, Vector3 const &b);

Vector3 operator*(Vector3 const &a, float const &b);
