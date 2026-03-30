/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "RaylibWrapper.hpp"
#include "PlayerInfoWindow.hpp"
#include "GameMenu.hpp"

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <sys/select.h>

Game::Game()
    : _port(7894), _machine("127.0.0.1"), _map(1, 1), _tempMap(1, 1), _timeUnit(100)
{
    _followPlayer = -1;
    _gameEnded = false;
    srand(time(NULL));
}

Game::Game(int port, std::string machine, bool shittyServer)
    : _port(port), _machine(machine), _map(1, 1), _tempMap(1, 1), _timeUnit(100), _shittyServer(shittyServer)
{
    _followPlayer = -1;
    _gameEnded = false;
    srand(time(NULL));
}

Game::~Game()
{
    _followPlayer = -1;
    _gameEnded = false;
}

ssize_t Game::sendMessage(int sock, const std::string &message)
{
    return send(sock, message.c_str(), message.size(), 0);
}

std::string Game::receiveMessage(int sock)
{
    char buffer[1024] = {0};
    ssize_t valread = recv(sock, buffer, sizeof(buffer), 0);
    if (valread < 0)
    {
        std::cerr << "Error receiving message: " << std::strerror(errno) << std::endl;
    }
    return std::string(buffer, valread);
}

std::vector<std::string> Game::split(std::string str, std::string delim)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;

    while ((pos = str.find(delim)) != std::string::npos)
    {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delim.length());
    }
    tokens.push_back(str);
    return tokens;
}

void Game::processServerMessage(std::string message)
{
    while (message.find("\n") != std::string::npos)
    {
        std::string line = message.substr(0, message.find("\n"));
        std::string command = line.substr(0, 3);
        if (command == "bct")
        {
            // content of a tile at X Y (food, linemate, deraumere, sibur, mendiane, phiras, thystame)
            std::vector<std::string> tokens = this->split(line, " ");
            int x = std::stoi(tokens[1]);
            int y = std::stoi(tokens[2]);
            std::vector<Tile> &tiles = this->_tempMap.getTiles();
            tiles[y * this->_tempMap.getWidth() + x].setRessource(ResourcesTypes::FOOD, std::stoi(tokens[3]));
            tiles[y * this->_tempMap.getWidth() + x].setRessource(ResourcesTypes::LINEMATE, std::stoi(tokens[4]));
            tiles[y * this->_tempMap.getWidth() + x].setRessource(ResourcesTypes::DERAUMERE, std::stoi(tokens[5]));
            tiles[y * this->_tempMap.getWidth() + x].setRessource(ResourcesTypes::SIBUR, std::stoi(tokens[6]));
            tiles[y * this->_tempMap.getWidth() + x].setRessource(ResourcesTypes::MENDIANE, std::stoi(tokens[7]));
            tiles[y * this->_tempMap.getWidth() + x].setRessource(ResourcesTypes::PHIRAS, std::stoi(tokens[8]));
            tiles[y * this->_tempMap.getWidth() + x].setRessource(ResourcesTypes::THYSTAME, std::stoi(tokens[9]));
            if (x == this->_tempMap.getWidth() - 1 && y == this->_tempMap.getHeight() - 1 && this->_map != this->_tempMap)
            {
                std::string data;
                this->_mapMutex.lock();
                for (int x = 0; x < this->_map.getWidth(); x++)
                {
                    for (int y = 0; y < this->_map.getHeight(); y++)
                    {
                        if (this->_map.getTile(x, y) != this->_tempMap.getTile(x, y))
                        {
                            data += std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(this->_tempMap.getTile(x, y).getRessource(ResourcesTypes::FOOD)) + " " + std::to_string(this->_tempMap.getTile(x, y).getRessource(ResourcesTypes::LINEMATE)) + " " + std::to_string(this->_tempMap.getTile(x, y).getRessource(ResourcesTypes::DERAUMERE)) + " " + std::to_string(this->_tempMap.getTile(x, y).getRessource(ResourcesTypes::SIBUR)) + " " + std::to_string(this->_tempMap.getTile(x, y).getRessource(ResourcesTypes::MENDIANE)) + " " + std::to_string(this->_tempMap.getTile(x, y).getRessource(ResourcesTypes::PHIRAS)) + " " + std::to_string(this->_tempMap.getTile(x, y).getRessource(ResourcesTypes::THYSTAME)) + "\n";
                        }
                        this->_map.getTiles()[y * this->_map.getWidth() + x].setRessources(this->_tempMap.getTile(x, y));
                    }
                }
                this->_mapMutex.unlock();
                std::cerr << "MAP UPDATED" << std::endl;
                this->_modifications.push_back(std::make_pair(ModificationType::MODIFY_MAP, data));
            }
        }
        else if (command == "ebo")
        {
            // player connected to an egg #e
            std::vector<std::string> tokens = this->split(line, " ");
            int eggId = 0;
            if (this->_shittyServer)
            {
                eggId = std::stoi(tokens[1]);
            }
            else
            {
                eggId = std::stoi(tokens[1].substr(1));
            }
            for (auto it = this->_eggs.begin(); it != this->_eggs.end(); it++)
            {
                if (it->get()->getId() == eggId)
                {
                    this->_mapMutex.lock();
                    this->_map.getTiles()[it->get()->getPosition().y() * this->_map.getWidth() + it->get()->getPosition().x()].removeEgg(eggId);
                    this->_eggs.erase(it);
                    this->_mapMutex.unlock();
                    break;
                }
            }
            if (this->_modifications.size() > 0 && this->_modifications.back().first == ModificationType::NEW_PLAYER)
            {
                this->_modifications.back().second += " " + std::to_string(eggId);
            }
            std::cerr << "EGG BROKEN: " << eggId << std::endl;
        }
        else if (command == "edi")
        {
            // an egg #e died (someone ejected it)
            std::vector<std::string> tokens = this->split(line, " ");
            int eggId = 0;
            if (this->_shittyServer)
            {
                eggId = std::stoi(tokens[1]);
            }
            else
            {
                eggId = std::stoi(tokens[1].substr(1));
            }
            for (auto it = this->_eggs.begin(); it != this->_eggs.end(); it++)
            {
                if (it->get()->getId() == eggId)
                {
                    this->_mapMutex.lock();
                    this->_map.getTiles()[it->get()->getPosition().y() * this->_map.getWidth() + it->get()->getPosition().x()].removeEgg(eggId);
                    this->_eggs.erase(it);
                    this->_mapMutex.unlock();
                    break;
                }
            }
            this->_modifications.push_back(std::make_pair(ModificationType::EGG_DIED, std::to_string(eggId)));
            std::cerr << "EGG DIED: " << eggId << std::endl;
        }
        else if (command == "enw")
        {
            // an egg #e was laid by a player #n at X Y
            std::vector<std::string> tokens = this->split(line, " ");
            int eggId = 0;
            int playerId = 0;
            if (this->_shittyServer)
            {
                eggId = std::stoi(tokens[1]);
                playerId = std::stoi(tokens[2]);
            }
            else
            {
                eggId = std::stoi(tokens[1].substr(1));
                playerId = std::stoi(tokens[2].substr(1));
            }
            int x = std::stoi(tokens[3]);
            int y = std::stoi(tokens[4]);
            this->_mapMutex.lock();
            std::shared_ptr<Egg> egg = std::make_shared<Egg>(eggId, this->_map.getTiles()[y * this->_map.getWidth() + x]);
            this->_eggs.push_back(egg);
            this->_map.getTiles()[y * this->_map.getWidth() + x].addEgg(this->_eggs.back());
            this->_mapMutex.unlock();
            this->_modifications.push_back(std::make_pair(ModificationType::EGG_LAYED, std::to_string(eggId) + " " + std::to_string(x) + " " + std::to_string(y)));
            std::cerr << "EGG LAID: " << eggId << " " << playerId << " " << x << " " << y << std::endl;
        }
        else if (command == "msz")
        {
            // map size (X Y)
            std::vector<std::string> tokens = this->split(line, " ");
            this->_map = Map(std::stoi(tokens[1]), std::stoi(tokens[2]));
            this->_tempMap = Map(std::stoi(tokens[1]), std::stoi(tokens[2]));
            std::cerr << "MAP SIZE: " << tokens[1] << " " << tokens[2] << std::endl;
        }
        else if (command == "pbc")
        {
            // player #n broadcast message M
            std::vector<std::string> tokens = this->split(line, " ");
            int playerId = 0;
            if (this->_shittyServer)
            {
                playerId = std::stoi(tokens[1]);
            }
            else
            {
                playerId = std::stoi(tokens[1].substr(1));
            }
            std::string message = line.substr(5 + tokens[1].size());
            std::string name;
            for (auto &human : this->_humans)
            {
                if (human->getId() == playerId)
                {
                    name = human->getName();
                    break;
                }
            }
            this->_chat.addMessage(name, message);
            std::cerr << "PLAYER BROADCAST: " << playerId << " " << message << std::endl;
        }
        else if (command == "pdi")
        {
            // player #n died
            std::vector<std::string> tokens = this->split(line, " ");
            int playerId = 0;
            if (this->_shittyServer)
            {
                playerId = std::stoi(tokens[1]);
            }
            else
            {
                playerId = std::stoi(tokens[1].substr(1));
            }
            for (auto it = this->_humans.begin(); it != this->_humans.end(); it++)
            {
                if (it->get()->getId() == playerId)
                {
                    this->_mapMutex.lock();
                    it->get()->setAnimType(AnimType::DEATH);
                    it->get()->getTeam().removePlayer(playerId);
                    this->_humans.erase(it);
                    this->_mapMutex.unlock();
                    break;
                }
            }
            this->_modifications.push_back(std::make_pair(ModificationType::PLAYER_DIED, std::to_string(playerId)));
            std::cerr << "PLAYER DIED: " << playerId << std::endl;
        }
        else if (command == "pdr")
        {
            // player #n dropped one resource i
            std::vector<std::string> tokens = this->split(line, " ");
            int playerId = 0;
            if (this->_shittyServer)
            {
                playerId = std::stoi(tokens[1]);
            }
            else
            {
                playerId = std::stoi(tokens[1].substr(1));
            }
            ResourcesTypes type = static_cast<ResourcesTypes>(std::stoi(tokens[2]));
            for (auto &human : this->_humans)
            {
                if (human->getId() == playerId)
                {
                    this->_mapMutex.lock();
                    human->removeRessource(type, 1);
                    human->setAnimType(AnimType::DROP);
                    this->_map.getTiles()[human->getPosition().y * this->_map.getWidth() + human->getPosition().x].addRessource(type, 1);
                    this->_mapMutex.unlock();
                    break;
                }
            }
            this->_modifications.push_back(std::make_pair(ModificationType::PLAYER_DROP, std::to_string(playerId) + " " + std::to_string(static_cast<int>(type))));
            std::cerr << "PLAYER DROP: " << playerId << " " << static_cast<int>(type) << std::endl;
        }
        else if (command == "pex")
        {
            // player #n eject (make a request to know the new position of #n)
            std::vector<std::string> tokens = this->split(line, " ");
            int playerId = 0;
            if (this->_shittyServer)
            {
                playerId = std::stoi(tokens[1]);
            }
            else
            {
                playerId = std::stoi(tokens[1].substr(1));
            }
            std::string message;
            if (this->_shittyServer)
            {
                message = "ppo " + std::to_string(playerId) + "\n";
            }
            else
            {
                message = "ppo #" + std::to_string(playerId) + "\n";
            }
            this->sendMessage(this->_sock, message);
            std::cerr << "PLAYER EJECTED: " << playerId << std::endl;
        }
        else if (command == "pfk")
        {
            // an egg started to be laid by player #n
        }
        else if (command == "pgt")
        {
            // player #n take one resource i
            std::vector<std::string> tokens = this->split(line, " ");
            int playerId = 0;
            if (this->_shittyServer)
            {
                playerId = std::stoi(tokens[1]);
            }
            else
            {
                playerId = std::stoi(tokens[1].substr(1));
            }
            ResourcesTypes type = static_cast<ResourcesTypes>(std::stoi(tokens[2]));
            for (auto &human : this->_humans)
            {
                if (human->getId() == playerId)
                {
                    this->_mapMutex.lock();
                    human->addRessource(type, 1);
                    human->setAnimType(AnimType::COLLECT);
                    this->_map.getTiles()[human->getPosition().y * this->_map.getWidth() + human->getPosition().x].removeRessource(type, 1);
                    this->_mapMutex.unlock();
                    break;
                }
            }
            this->_modifications.push_back(std::make_pair(ModificationType::PLAYER_COLLECT, std::to_string(playerId) + " " + std::to_string(static_cast<int>(type))));
            std::cerr << "PLAYER TAKE: " << playerId << " " << static_cast<int>(type) << std::endl;
        }
        else if (command == "pic")
        {
            // start of an incantation at X Y with player level L and with players #n #n etc...
            std::vector<std::string> tokens = this->split(line, " ");
            int x = std::stoi(tokens[1]);
            int y = std::stoi(tokens[2]);
            int level = std::stoi(tokens[3]);
            std::vector<int> playerIds;
            for (size_t i = 4; i < tokens.size(); i++)
            {
                if (this->_shittyServer)
                {
                    playerIds.push_back(std::stoi(tokens[i]));
                }
                else
                {
                    playerIds.push_back(std::stoi(tokens[i].substr(1)));
                }
                this->_mapMutex.lock();
                for (auto &human : this->_humans)
                {
                    if (human->getId() == playerIds.back())
                    {
                        human->setAnimType(AnimType::PRAY_START);
                        break;
                    }
                }
                this->_mapMutex.unlock();
            }
            this->_incantations.push(playerIds);
            std::cerr << "INCANTATION START: " << x << " " << y << " " << level << " ";
            for (auto &playerId : playerIds)
            {
                std::cerr << playerId << " ";
            }
            std::cerr << std::endl;
        }
        else if (command == "pie")
        {
            // end of an incantation at X Y with result R (0: fail, 1: success)
            std::vector<std::string> tokens = this->split(line, " ");
            int x = std::stoi(tokens[1]);
            int y = std::stoi(tokens[2]);
            int result = std::stoi(tokens[3]);
            std::vector<int> playerIds = this->_incantations.front();
            for (auto &playerId : playerIds)
            {
                for (auto &human : this->_humans)
                {
                    if (human.get()->getId() == playerId)
                    {
                        if (result == 1)
                        {
                            human.get()->levelUp();
                        }
                        human.get()->setAnimType(AnimType::PRAY_STOP);
                        break;
                    }
                }
            }
            std::cerr << "INCANTATION END: " << x << " " << y << " " << result << std::endl;
            this->_incantations.pop();
        }
        else if (command == "pin")
        { // get a response only if I ask
            // player #n inventory at X Y (food, linemate, deraumere, sibur, mendiane, phiras, thystame)
            std::vector<std::string> tokens = this->split(line, " ");
            int playerId = 0;
            if (this->_shittyServer)
            {
                playerId = std::stoi(tokens[1]);
            }
            else
            {
                playerId = std::stoi(tokens[1].substr(1));
            }
            // int x = std::stoi(tokens[2]);
            // int y = std::stoi(tokens[3]);
            int food = std::stoi(tokens[4]);
            // int linemate = std::stoi(tokens[5]);
            // int deraumere = std::stoi(tokens[6]);
            // int sibur = std::stoi(tokens[7]);
            // int mendiane = std::stoi(tokens[8]);
            // int phiras = std::stoi(tokens[9]);
            // int thystame = std::stoi(tokens[10]);
            for (auto &human : this->_humans)
            {
                if (human->getId() == playerId)
                {
                    this->_mapMutex.lock();
                    human->setRessource(ResourcesTypes::FOOD, food);
                    this->_mapMutex.unlock();
                    break;
                }
            }
            this->_modifications.push_back(std::make_pair(ModificationType::PLAYER_FOOD, std::to_string(playerId) + " " + std::to_string(food)));
            std::cerr << "UPDATE PLAYER FOOD: " << playerId << " " << food << std::endl;
        }
        else if (command == "plv")
        { // get a response only if I ask
            // player #n level L
        }
        else if (command == "pnw")
        {
            // new player #n connected at X Y with orientation O and level L and name of the team N
            std::vector<std::string> tokens = this->split(line, " ");
            int playerId = 0;
            if (this->_shittyServer)
            {
                playerId = std::stoi(tokens[1]);
            }
            else
            {
                playerId = std::stoi(tokens[1].substr(1));
            }
            int x = std::stoi(tokens[2]);
            int y = std::stoi(tokens[3]);
            int orientation = std::stoi(tokens[4]);
            int level = std::stoi(tokens[5]);
            std::string teamName = tokens[6];
            this->_mapMutex.lock();
            for (auto &team : this->_teams)
            {
                if (team.getName() == teamName)
                {
                    std::shared_ptr<Human> human = std::make_shared<Human>(team, Vector2(x * 1.0f, y * 1.0f), level, this->_timeUnit);
                    team.addPlayer(human);
                    this->_humans.push_back(human);
                    this->_humans.back().get()->setId(playerId);
                    this->_humans.back().get()->setOrientation(orientation);
                    break;
                }
            }
            this->_map.getTiles()[y * this->_map.getWidth() + x].addHuman(this->_humans.back());
            this->_mapMutex.unlock();
            this->_modifications.push_back(std::make_pair(ModificationType::NEW_PLAYER, std::to_string(playerId) + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(orientation) + " " + std::to_string(level) + " " + teamName));
            std::cerr << "NEW PLAYER: " << playerId << " " << x << " " << y << " " << orientation << " " << level << " " << teamName << std::endl;
        }
        else if (command == "ppo")
        {
            // player #n position X Y with orientation O
            std::vector<std::string> tokens = this->split(line, " ");
            int playerId = 0;
            if (this->_shittyServer)
            {
                playerId = std::stoi(tokens[1]);
            }
            else
            {
                playerId = std::stoi(tokens[1].substr(1));
            }
            int x = std::stoi(tokens[2]);
            int y = std::stoi(tokens[3]);
            int orientation = std::stoi(tokens[4]);
            for (auto &human : this->_humans)
            {
                if (human->getId() == playerId)
                {
                    this->_mapMutex.lock();
                    if (human->getOrientation() == orientation)
                    {
                        this->_map.getTiles()[human->getPosition().y * this->_map.getWidth() + human->getPosition().x].removeHuman(playerId);
                        human->setPosition({x * 1.0f, y * 1.0f});
                        human->setAnimType(AnimType::WALK);
                        human->setNewPos(true);
                        this->_map.getTiles()[y * this->_map.getWidth() + x].addHuman(human);
                    }
                    else
                    {
                        human->setOrientation(orientation);
                    }
                    this->_mapMutex.unlock();
                    break;
                }
            }
            std::cerr << "PLAYER POSITION: " << playerId << " " << x << " " << y << " " << orientation << std::endl;
            // TODO add to modifications
        }
        else if (command == "sbp")
        {
            // command parameter
        }
        else if (command == "seg")
        {
            std::vector<std::string> tokens = this->split(line, " ");
            this->_winner = tokens[1];
            this->_startEndGame = true;
        }
        else if (command == "sgt")
        {
            // time unit T
            std::vector<std::string> tokens = this->split(line, " ");
            this->_timeUnit = std::stoi(tokens[1]);
            this->_modifications.push_back(std::make_pair(ModificationType::SET_TIME_UNIT, std::to_string(this->_timeUnit)));
            std::cerr << "SET TIME UNIT: " << this->_timeUnit << std::endl;
            this->_menu.setSpeed(this->_timeUnit);
        }
        else if (command == "smg")
        {
            // message M from the server
        }
        else if (command == "sst")
        {
            // time unit T modification
            std::vector<std::string> tokens = this->split(line, " ");
            this->_timeUnit = std::stoi(tokens[1]);
            this->_modifications.push_back(std::make_pair(ModificationType::UPDATE_TIME_UNIT, std::to_string(this->_timeUnit)));
            std::cerr << "MODIFY TIME UNIT: " << this->_timeUnit << std::endl;
        }
        else if (command == "suc")
        {
            // unknown command
        }
        else if (command == "tna")
        {
            // name of the team N
            std::vector<std::string> tokens = this->split(line, " ");
            this->_teams.push_back(Team(tokens[1]));
            this->_teams.back().setColor(teamColors[(this->_teams.size() - 1) % teamColors.size()]);
            this->_currentGameState.addTeam(tokens[1]);
            this->_initialGameState.addTeam(tokens[1]);
            std::cerr << "TEAM ADDED: " << tokens[1] << std::endl;
        }
        // std::cerr << "line: " << line << std::endl;
        message.erase(0, message.find("\n") + 1);
    }
}

void *Game::communicateWithServer()
{
    fd_set readfds;
    struct timeval tv;
    int retval;

    while (this->_isRunning)
    {
        FD_ZERO(&readfds);
        FD_SET(this->_sock, &readfds);

        tv.tv_sec = 1;
        tv.tv_usec = 0;

        retval = select(this->_sock + 1, &readfds, NULL, NULL, &tv);
        if (retval == -1)
        {
            std::cerr << "Error in select: " << std::strerror(errno) << std::endl;
        }
        else if (retval != 0 && FD_ISSET(this->_sock, &readfds))
        {
            std::string message = this->receiveMessage(this->_sock);
            while (message[message.size() - 1] != '\n')
            {
                message += this->receiveMessage(this->_sock);
            }
            this->processServerMessage(message);
        }
    }
    return nullptr;
}

int Game::run()
{
    InitAudioDevice();
    std::vector<Firework> fireworks;
    bool fbool = false;
    this->_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_sock < 0)
    {
        std::cerr << "Error creating socket: " << std::strerror(errno) << std::endl;
        return 84;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->_port);
    if (inet_pton(AF_INET, this->_machine.c_str(), &server_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address: " << this->_machine << std::endl;
        return 84;
    }

    if (connect(this->_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Connection failed: " << std::strerror(errno) << std::endl;
        return 84;
    }

    std::cout << "Connected to server " << this->_machine << " on port " << this->_port << std::endl;

    this->sendMessage(this->_sock, "GRAPHIC\n");

    std::thread communicateWithServerThread(&Game::communicateWithServer, this);

    RaylibWrapper window(800, 600, "ZOAT");
    rlImGuiSetup(true);

    while (!window.WindowShouldClose())
    {
        if (this->_startEndGame) {
            this->_gameEnded = true;
        }
        window.setGameSpeed(this->_timeUnit);
        this->_menu.setTeams(this->_teams);
        if (this->_menu.getSpeed() != this->_menu.getPreviousSpeed())
        {
            std::string message = "sst " + std::to_string(this->_menu.getSpeed()) + "\n";
            this->sendMessage(this->_sock, message);
            this->_menu.updatePreviousSpeed();
        }
        if (this->_menu.getFollowPlayer() != -1)
        {
            _followPlayer = this->_menu.getFollowPlayer();
            this->_menu.setFollowPlayer(-1);
        }
        window.BeginDrawing();
        eventHandler(window);

        if (this->_gameEnded)
        {
            if (!fbool)
            {
                for (int i = 0; i < 15; i++)
                    fireworks.push_back(Firework(RED));
            }
            fbool = true;
        }

        if (_followPlayer != -1)
        {
            for (auto &tile : this->_map.getTiles())
            {
                tile.setLerpSpeed(std::max(1.0f, std::min(10.0f * window.getGameSpeed() / 40.0f, 10.0f)));
            }
            for (auto &human : this->_humans)
            {
                if (human.get()->getId() == _followPlayer)
                {
                    this->_mapMutex.lock();
                    Tile tile = this->_map.getTile(human.get()->getPosition().x, human.get()->getPosition().y);
                    this->_map.setCenter({(float)((tile.x() + this->_map.getWidth() / 2) % this->_map.getWidth()), (float)((tile.y() + this->_map.getHeight() / 2) % this->_map.getHeight())});
                    this->_map.lookAtCenter();
                    this->_mapMutex.unlock();
                    /* rlImGuiBegin();
                    human.get()->getPlayerInfoWindow().get()->draw();
                    rlImGuiEnd(); */
                }
            }
        }
        else
        {
            for (auto &tile : this->_map.getTiles())
            {
                tile.setLerpSpeed(10.0f);
            }
        }
        // window.UpdateCamera(CameraMode::CAMERA_FREE);
        window.ClearBackground(BLACK);
        BeginMode3D(window.getCamera());
        window.enableDepthTest();
        this->_mapMutex.lock();
        this->_map.draw(window);
        this->_mapMutex.unlock();

        if (this->_gameEnded)
        {
            float time = window.getEllapsedTime() - this->_map.getTiles()[0].getExplode();
            if (time >= 5.5)
            {
                for (auto &tile : this->_map.getTiles())
                {
                    tile.setIsDrawn(false);
                }
                for (auto &firework : fireworks)
                    firework.draw(window);
            }
        }

        EndMode3D();
        rlImGuiBegin();
        this->_menu.draw();
        this->_chat.draw(window);
        for (auto &human : this->_humans)
        {
            if (_followPlayer == human.get()->getId())
            {
                human.get()->getPlayerInfoWindow().get()->draw();
            }
            if (human.get()->isClicked(window))
            {
                human.get()->getPlayerPopupWindow().get()->draw();
                human.get()->getPlayerPopupWindow().get()->open();
            }
        }
        rlImGuiEnd();

        if (this->_gameEnded)
        {
            float time = window.getEllapsedTime() - this->_map.getTiles()[0].getExplode();
            Color color = {255, 255, 255, time * 255 / 7 > 255 ? 255 : time * 255 / 7};
            window.DrawText((_winner + " WINS").c_str(), window.GetScreenSize().x / 2 - 50, window.GetScreenSize().y / 2 - 10, 20, color);
        }

        window.EndDrawing();
    }
    CloseAudioDevice();
    this->_isRunning = false;
    communicateWithServerThread.join();
    close(this->_sock);
    return 0;
}

void Game::draw(Point2d POV)
{
    return;
}

void Game::draw(GameState state, Point2d POV)
{
    // TODO
}

Point2d &Game::getPOV()
{
    return this->POV;
}

void Game::setPOV(Point2d newPOV)
{
    this->POV = newPOV;
}

void Game::setPOV(Tile tilePOV)
{
    this->POV = Point2d(tilePOV.x(), tilePOV.y());
}

void Game::setMap(Map map)
{
    this->_map = map;
}

void Game::askNextGameState()
{
    // TODO
}

void Game::eventHandler(RaylibWrapper &window)
{
    if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
    {
        this->_followPlayer = -1;
        this->_mapMutex.lock();
        this->_map.rotateMap(1);
        this->_mapMutex.unlock();
    }
    if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
    {
        this->_followPlayer = -1;
        this->_mapMutex.lock();
        this->_map.rotateMap(0);
        this->_mapMutex.unlock();
    }
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
    {
        this->_followPlayer = -1;
        this->_mapMutex.lock();
        this->_map.rotateMap(2);
        this->_mapMutex.unlock();
    }
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
    {
        this->_followPlayer = -1;
        this->_mapMutex.lock();
        this->_map.rotateMap(3);
        this->_mapMutex.unlock();
    }
    if (IsKeyPressed(KEY_TAB))
    {
        this->_map.setCenter({(float)(rand() % this->_map.getWidth()), (float)(rand() % this->_map.getHeight())});
        this->_map.lookAtCenter();
    }
    if (IsKeyPressed(KEY_X))
        this->_gameEnded = true;
    if (this->_gameEnded)
    {
        this->_mapMutex.lock();
        for (auto &tile : this->_map.getTiles())
        {
            if (tile.getExplode() == -1)
            {
                tile.setExplode(window.getEllapsedTime());
            }
        }
        this->_mapMutex.unlock();
    }
    for (auto &human : this->_humans)
    {

        if (window.isMouseButtonPressed(0) && human.get()->isClicked(window))
        {
            _followPlayer = human.get()->getId();
            human.get()->getPlayerInfoWindow().get()->setIsOnScreen(true);
        }
        if (_followPlayer != human.get()->getId())
        {
            human.get()->getPlayerInfoWindow().get()->setIsOnScreen(false);
        }
    }
}