/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Raylib.cpp
*/

#include "RaylibWrapper.hpp"
#include "GL/gl.h"  // Include the OpenGL header for depth testing
#include "raymath.h"

RaylibWrapper::RaylibWrapper(int width, int height, std::string title) 
    : screenWidth(width), screenHeight(height), windowTitle(title) {
    InitWindow(screenWidth, screenHeight, windowTitle.c_str());
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    MaximizeWindow();
    Camera camera = {0};
    camera.position = (Vector3){30.0f, -10.0f, 0.001f}; // Camera position
    camera.target = (Vector3){0.0f, -10.0f, 0.0f};     // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};         // Camera up vector (rotation towards target)
    camera.fovy = 90.0f; 
    initCameraPosition = camera.position;
    this->camera = camera;
}

RaylibWrapper::~RaylibWrapper() {
    ::CloseWindow();
}

void RaylibWrapper::BeginDrawing() {
    ::BeginDrawing();
}

void RaylibWrapper::EndDrawing() {
    ::EndDrawing();
}

void RaylibWrapper::ClearBackground(Color color) {
    ::ClearBackground(color);
}

bool RaylibWrapper::WindowShouldClose() {
    return ::WindowShouldClose();
}

void RaylibWrapper::DrawText(std::string text, int posX, int posY, int fontSize, Color color) {
    ::DrawText(text.c_str(), posX, posY, fontSize, color);
}

void RaylibWrapper::DrawRectangleFilled(int posX, int posY, int width, int height, Color color) {
    ::DrawRectangle(posX, posY, width, height, color);
}

void RaylibWrapper::DrawRectangleOutline(int posX, int posY, int width, int height, Color color) {
    ::DrawRectangleLines(posX, posY, width, height, color);
}

void RaylibWrapper::DrawRectangleOutline(int posX, int posY, int width, int height, Color color, float thickness) {
    ::DrawRectangleLinesEx(Rectangle{static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(width), static_cast<float>(height)}, thickness, color);
}

Vector2 RaylibWrapper::GetMousePosition() {
    return ::GetMousePosition();
}

Vector2 RaylibWrapper::GetScreenSize() {
    return Vector2(GetScreenWidth(), GetScreenHeight());
}

void RaylibWrapper::Draw3DLine(Vector3 begin, Vector3 end, Color color) {
    ::DrawLine3D(begin, end, color);
}

void RaylibWrapper::DrawSphere(Vector3 center, float radius, Color color) {
    ::DrawSphere(center, radius, color);
}

void RaylibWrapper::UpdateCamera(CameraMode mode) {
    ::UpdateCamera(&this->camera, mode);
}

void RaylibWrapper::Draw3DCircle(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color) {
    ::DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);
}

void RaylibWrapper::drawCube(Vector3 position, Vector3 size, Color color) {
    /* position.x -= size.x / 2;
    position.y -= size.y / 2;
    position.z -= size.z / 2; */
    ::DrawCube(position, size.x, size.y, size.z, color);
}

void RaylibWrapper::DrawSphereWire(Vector3 center, float radius, int rings, int slices, Color color) {
    ::DrawSphereWires(center, radius, rings, slices, color);
}

void RaylibWrapper::Draw3DPoint(Vector3 position, Color color) {
    ::DrawPoint3D(position, color);
}

void RaylibWrapper::Draw3DTriangle(Vector3 v1, Vector3 v2, Vector3 v3, Color color) {
    ::DrawTriangle3D(v1, v2, v3, color);
}

void RaylibWrapper::enableDepthTest() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); 
    glDisable(GL_CULL_FACE);
}

Vector3 RaylibWrapper::getCameraPosition() {
    return this->camera.position;
}

double RaylibWrapper::getDeltaTime() {
    return ::GetFrameTime();
}

double RaylibWrapper::getEllapsedTime() {
    return ::GetTime();
}

void RaylibWrapper::drawCube(Vector3 position, Vector3 size, Color color, Vector3 normal) {
    Vector3 original = (Vector3){0, 1, 0};
    float angle = Vector3Angle(normal, original);
    Vector3 axis = Vector3CrossProduct(normal, original);
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(angle, axis.x, axis.y, axis.z);
    rlTranslatef(-position.x, -position.y, -position.z);
    drawCube(position, size, color);
    rlPopMatrix();
}

Model RaylibWrapper::LoadModel(std::string path) {
    return ::LoadModel(path.c_str());
}

Texture2D RaylibWrapper::LoadTexture(std::string path) {
    return ::LoadTexture(path.c_str());
}

ModelAnimation *RaylibWrapper::LoadModelAnimations(std::string path, int *animsCount) {
    return ::LoadModelAnimations(path.c_str(), animsCount);
}

Matrix RaylibWrapper::MatrixRotateX(float angle) {
    return ::MatrixRotateX(angle);
}

Matrix RaylibWrapper::MatrixMultiply(Matrix left, Matrix right) {
    return ::MatrixMultiply(left, right);
}

void RaylibWrapper::UpdateModelAnimation(Model model, ModelAnimation anim, int frame) {
    ::UpdateModelAnimation(model, anim, frame);
}

void RaylibWrapper::DrawModel(Model model, Vector3 position, float scale, Color tint) {
    ::DrawModel(model, position, scale, tint);
}

void RaylibWrapper::DrawModel(Model model, Vector3 position, float scale, Color tint, Vector3 rotationAxis, float rotationAngle) {
    ::DrawModelEx(model, position, rotationAxis, rotationAngle, Vector3{scale, scale, scale}, tint);
}

void RaylibWrapper::UnloadModel(Model model) {
    ::UnloadModel(model);
}

void RaylibWrapper::UnloadModelAnimations(ModelAnimation *modelAnimations, int animsCount) {
    ::UnloadModelAnimations(modelAnimations, animsCount);
}

Matrix RaylibWrapper::MatrixRotateZ(float angle) {
    return ::MatrixRotateZ(angle);
}

Vector3 operator+(Vector3 const &a, Vector3 const &b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
};

Vector3 operator-(Vector3 const &a, Vector3 const &b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
};

Vector3 operator*(Vector3 const &a, float const &b) {
    return {a.x * b, a.y * b, a.z * b};
};

void RaylibWrapper::Draw3Dline(Vector3 line, Color color) {
    ::DrawLine3D(Vector3{0, 0, 0}, line, color);
}

Sound RaylibWrapper::LoadSound(std::string path) {
    return ::LoadSound(path.c_str());
}

void RaylibWrapper::PlaySound(Sound sound) {
    ::PlaySound(sound);
}

void RaylibWrapper::UnloadSound(Sound sound) {
    ::UnloadSound(sound);
}

bool RaylibWrapper::IsSoundPlaying(Sound sound) {
    return ::IsSoundPlaying(sound);
}