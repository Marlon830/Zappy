/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** PlayerPopupWindow.cpp
*/

#include "PlayerPopupWindow.hpp"

Window::PlayerPopup::PlayerPopup(Human &human) : _human(human)
{
}



void Window::PlayerPopup::draw()
{
    ImGui::SetNextWindowPos(ImGui::GetMousePos());
    if (ImGui::BeginPopup("PlayerPopup"))
    {
        //std::cout << "_human.getName() = " << _human.getName() << std::endl;
        ImGui::Text("%s", _human.getName().c_str());
        ImGui::Text("Team: %s", _human.getTeam().getName().c_str());
        ImGui::Text("Level: %d", _human.getLevel());
        ImGui::Text("Position: %d, %d", (int)(_human.getPosition().x), (int)(_human.getPosition().y));
        ImGui::EndPopup();
    }
}


void Window::PlayerPopup::open()
{
    ImGui::OpenPopup("PlayerPopup");
}