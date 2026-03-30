/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** GameMenu.cpp
*/

#include "GameMenu.hpp"
#include "Human.hpp"

namespace Window {
    GameMenu::GameMenu()
    {
        this->_isSetSpeedOnScreen = false;
        this->_speed = 1;
        this->_previousSpeed = 1;
        this->_followPlayer = -1;
    }

    GameMenu::~GameMenu()
    {
    }

    void GameMenu::drawSpeedSlider()
    {
        if (!_isSetSpeedOnScreen)
            return;
        ImGui::Begin("Game speed", &_isSetSpeedOnScreen, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::SliderInt("Speed", &_speed, 1, 100);
        ImGui::End();
    }

    void GameMenu::draw()
    {
        drawSpeedSlider();
        //ImGui::Begin("Game Menu", &_isOnScreen, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("Game")) {
                if (ImGui::MenuItem("Game speed", NULL, &_isSetSpeedOnScreen)) {
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Info")) {
                if (ImGui::BeginMenu("Teams")) {
                    for (int i = 0; i < _teams.size(); i++) {
                        if (ImGui::BeginMenu(_teams[i].getName().c_str())) {
                            std::cout << _teams[i].getMembers().size() << std::endl;
                            for (int j = 0; j < _teams[i].getMembers().size(); j++) {
                                std::cout << _teams[i].getMembers()[j].get()->getName() << std::endl;
                                if (ImGui::MenuItem(_teams[i].getMembers()[j].get()->getName().c_str())) {
                                    this->_followPlayer = _teams[i].getMembers()[j].get()->getId();
                                }
                            }
                            ImGui::EndMenu();
                        }
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
        ImGui::EndMainMenuBar();
    }
        //ImGui::End();
    }
}