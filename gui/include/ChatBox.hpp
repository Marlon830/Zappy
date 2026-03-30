/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** ChatBox.hpp
*/

#pragma once

#include "imgui.h"
#include "imgui_internal.h"
#include "rlImGui.h"
#include "RaylibWrapper.hpp"
#include <vector>
#include <string>

namespace Window
{
    class ChatBox {
        public:
            ChatBox();

            void draw(RaylibWrapper &wrapper);

            void addMessage(std::string name, std::string message);
        private:
            std::vector<std::pair<std::string, std::string>> _messages;
            bool _newMessage;
    };
}
