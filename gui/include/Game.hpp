/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Game.hpp
*/

#pragma once

#include <vector>
#include <queue>
#include "GameState.hpp"
#include "Point2d.hpp"
#include "Egg.hpp"
#include "GameWindows.hpp"
#include "GameMenu.hpp"
#include "ChatBox.hpp"
#include "Firework.hpp"

class Game
{
public:
    Game();
    Game(int port, std::string machine, bool shittyServer);
    ~Game();

    ssize_t sendMessage(int sock, const std::string &message);
    std::string receiveMessage(int sock);
    std::vector<std::string> split(std::string str, std::string delim);
    void processServerMessage(std::string message);
    void *communicateWithServer();
    int run();
    GameState &getCurrentGameState() {
        return this->_currentGameState;
    };
    GameState &getGameStateAt(int turn) {
        return this->_history[turn];
    }
    void draw(Point2d POV);
    void draw(GameState state, Point2d POV);
    Point2d &getPOV();
    void setPOV(Point2d newPOV);
    void setPOV(Tile tilePOV);
    void setMap(Map map);
    void askNextGameState();
    void eventHandler(RaylibWrapper &window);
private:
    bool _shittyServer = false;
    int _port;
    std::string _machine;
    int _sock;
    bool _isRunning = true;
    int _timeUnit;
    std::vector<GameState> _history; // useless
    // std::vector<Window> _windows;
    GameState _currentGameState;
    GameState _initialGameState;
    std::queue<std::vector<int>> _incantations;
    std::vector<std::pair<ModificationType, std::string>> _modifications;
    Point2d POV;
    Window::GameMenu _menu;
    Window::ChatBox _chat;
    Map _map;
    std::mutex _mapMutex;
    Map _tempMap;
    std::vector<Team> _teams;
    std::vector<std::shared_ptr<Egg>> _eggs;
    std::vector<std::shared_ptr<Human>> _humans;
    int _followPlayer;
    bool _gameEnded;
    bool _startEndGame = false;
    std::string _winner;
};

