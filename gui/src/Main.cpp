/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-marlon.pegahi
** File description:
** main.cpp
*/

#include "RaylibWrapper.hpp"
#include "PlayerInfoWindow.hpp"
#include "Human.hpp"
#include "Team.hpp"
#include "Map.hpp"
#include "Game.hpp"

int main(int argc, char *argv[]) {
    int port = 7894;
    std::string machine = "127.0.0.1";
    bool shittyServer = false;

    try {
        for (int i = 1; i < argc; i++) {
            if (std::string(argv[i]) == "-p" && i + 1 < argc) {
                char *end;
                port = std::strtol(argv[++i], &end, 10);
                if (*end != '\0') {
                    throw std::invalid_argument("Invalid port number");
                }
            } else if (std::string(argv[i]) == "-h" && i + 1 < argc) {
                machine = argv[++i];
            } else if (std::string(argv[i]) == "-s") {
                shittyServer = true;
            } else {
                throw std::invalid_argument("Invalid arguments");
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error parsing arguments: " << e.what() << std::endl;
        return 84;
    }
    Game game(port, machine, shittyServer);
    return game.run();
}
