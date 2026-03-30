/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** PlayerPopupWindow.hpp
*/

#pragma once

#include "AWindow.hpp"
#include "Human.hpp"

namespace Window {
    class PlayerPopup : public AWindow
    {
        public :
            PlayerPopup(Human &human);
            void draw() override;
            void open() override;
        private :
            Human &_human;
    };
}