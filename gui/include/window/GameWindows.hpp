/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** GameWindows.hpp
*/

#pragma once

#include "Game.hpp"
#include "PlayerInfoWindow.hpp"


namespace Window {
    class GameWindows
    {
        public :
            void newPlayerInfoWindow(Human player);
            PlayerInfoWindow &getPlayerInfoWindow(int id) {
                return _playerInfoWindows[id];
            }

        private :
            std::vector<PlayerInfoWindow> _playerInfoWindows;
    };
}