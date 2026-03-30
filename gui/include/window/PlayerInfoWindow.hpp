/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** PlayerInfoWindow.hpp
*/

#pragma once
#include "AWindow.hpp"
#include "Human.hpp"

namespace Window
{
    class PlayerInfoWindow : public AWindow {
        public :
            PlayerInfoWindow(Human &human);
            void draw() override;
            void open() override;
            
        private :
            Human &_human;
    };
}

