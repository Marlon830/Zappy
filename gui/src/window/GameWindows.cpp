/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** GameWindows.hpp
*/

#include "GameWindows.hpp"


namespace Window {
    void GameWindows::newPlayerInfoWindow(Human player)
    {
        _playerInfoWindows.push_back(PlayerInfoWindow(player));
    }
}