/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** IWindow.hpp
*/

#pragma once
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>

#include "imgui.h"
#include "rlImGui.h"


namespace Window
{
    class AWindow {
        public :
            std::string getName() {return name;};
            bool isOnScreen() {return _isOnScreen;};
            void setIsOnScreen(bool isOnScreen) {_isOnScreen = isOnScreen;};
            virtual void draw() = 0;
            virtual void open() = 0;
        protected :
            std::string name;
            bool _isOnScreen;
            
        
    };
    
} // namespace Window

