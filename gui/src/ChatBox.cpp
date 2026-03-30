/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** ChatBox.cpp
*/

#include "ChatBox.hpp"
#include <iostream>

namespace Window
{
    ChatBox::ChatBox()
    {
        this->_newMessage = false;
    }

    void ChatBox::draw(RaylibWrapper &wrapper)
    {
        Vector2 size = wrapper.GetScreenSize();
        ImVec2 windowPos(0, size.y - size.y * 0.2);
        ImGui::SetNextWindowSize(ImVec2(size.x * 0.2, size.y * 0.2), ImGuiCond_Always);
        ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
        ImGui::Begin("Chat", nullptr, ImGuiWindowFlags_NoResize);

        bool shouldScroll = false;
        float scrollY = ImGui::GetScrollY();
        float scrollMaxY = ImGui::GetScrollMaxY();

        if (scrollY >= scrollMaxY) {
            shouldScroll = true;
        }

        ImGui::BeginChild("Scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);

        bool isScrollbarActive = ImGui::IsWindowFocused() &&
                                (ImGui::IsMouseDragging(ImGuiMouseButton_Left) || ImGui::IsMouseDown(ImGuiMouseButton_Left)) &&
                                ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);

        for (std::size_t i = 0; i < this->_messages.size(); i++) {
            ImGui::TextWrapped("%s: %s", this->_messages[i].first.c_str(), this->_messages[i].second.c_str());
        }
        if (this->_newMessage && shouldScroll && !isScrollbarActive) {
            ImGui::SetScrollHereY(1.0f);
        }
        this->_newMessage = false;
        ImGui::EndChild();
        ImGui::End();
    }

    void ChatBox::addMessage(std::string name, std::string message)
    {
        this->_messages.push_back(std::make_pair(name, message));
        this->_newMessage = true;
    }
}
