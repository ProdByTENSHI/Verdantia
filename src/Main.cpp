#include "core/Game.hpp"
#include <spdlog/spdlog.h>

int main(int argc, char** argv) {
    spdlog::info("{}", argv[0]);
    Game game;
    game.Update();

    return 0;
}