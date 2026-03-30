/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** GameMenu.hpp
*/

#pragma once

#include "AWindow.hpp"
#include "Team.hpp"
#include <memory>

namespace Window
{
    class GameMenu {
        public :
            GameMenu();
            ~GameMenu();
            void draw();
            void drawSpeedSlider();
            void setSpeed(int speed) {
                _speed = speed;
            };
            int getSpeed() {
                return _speed;
                };
            int getPreviousSpeed() {
                return _previousSpeed;
            };
            void updatePreviousSpeed() {
                _previousSpeed = _speed;
            };
            void setTeams(std::vector<Team> teams) {
                _teams = teams;
            };
            std::vector<Team> getTeams() {
                return _teams;
            };
            int getFollowPlayer() {
                return _followPlayer;
            };
            void setFollowPlayer(int id) {
                _followPlayer = id;
            };
        protected :
            bool _isSetSpeedOnScreen;
            int _speed;
            int _previousSpeed;
            int _followPlayer;
            std::vector<Team> _teams;
    };
    
}
