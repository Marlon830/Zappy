/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** PlayerInfoWindow.cpp
*/

#include "PlayerInfoWindow.hpp"



namespace Window
{

    PlayerInfoWindow::PlayerInfoWindow(Human &human) : _human(human)
    {
        this->_isOnScreen = true;
    }

    void PlayerInfoWindow::draw()
    {
        ImGui::SetNextWindowSize(ImVec2(230, 190), ImGuiCond_FirstUseEver);
        ImGui::Begin(this->_human.getName().c_str(), &_isOnScreen, ImGuiWindowFlags_NoCollapse);
        ImGui::Text("Player Level: %d", _human.getLevel());
        //i want a tab with the inventory
        ImGui::BeginTable("Inventory", 2);
        ImGui::TableSetupColumn("Item");
        //i want red bg for the header
        ImGui::TableSetupColumn("Quantity");
        ImGui::TableHeadersRow();
        for (auto &item : _human.getInventory()) {
            std::string name = resourcesNames[item.first];
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text(name.c_str());
            ImGui::TableNextColumn();
            ImGui::Text("%d", item.second);
        }
        ImGui::EndTable();
        ImGui::End();
    }

    void PlayerInfoWindow::open()
    {
        _isOnScreen = true;
    }
    
} // namespace Window
