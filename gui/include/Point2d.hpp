/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Point2d.hpp
*/

#pragma once

class Point2d
{
public:
    Point2d();
    //Point2d(Tile &tile);
    Point2d(double x, double y);

    double x();
    double y();
private:
    double _x;
    double _y;
};
