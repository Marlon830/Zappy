/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Point2d.cpp
*/

#include "Point2d.hpp"

Point2d::Point2d()
{
    this->_x = 0;
    this->_y = 0;
}
/* 
Point2d::Point2d(Tile &tile)
{
    this->_x = tile.x();
    this->_y = tile.y();
} */

Point2d::Point2d(double x, double y)
{
    this->_x = x;
    this->_y = y;
}

double Point2d::x()
{
    return this->_x;
}

double Point2d::y()
{
    return this->_y;
}
