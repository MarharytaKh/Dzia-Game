#include "GameSaver.h"
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

static int failures = 0;

static void check(bool condition, const std::string& message) {
    if (!condition) {
        std::cerr << "FAIL: " << message << "\n";
        ++failures;
    }
}

int main() {
    fs::remove_all("saves");

    GameSaver saver;
    check(fs::exists("saves"), "saves directory is created");
    check(GameSaver::getSaveFiles().empty(), "no saves at start");

    saver.saveGame("slot1.txt", 120, 340, 2);
    int x = 0;
    int y = 0;
    int phase = 0;
    check(GameSaver::loadGame("slot1.txt", x, y, phase), "load existing save");
    check(x == 120 && y == 340 && phase == 2, "loaded values match saved values");

    check(!GameSaver::loadGame("missing.txt", x, y, phase), "load missing save fails");

    saver.saveGame("slot2.txt", 1, 1, 1);
    saver.saveGame("slot3.txt", 2, 2, 2);
    saver.saveGame("slot4.txt", 3, 3, 3);
    check(GameSaver::getSaveFiles().size() == 3, "no more than 3 saves are kept");
    check(GameSaver::loadGame("slot4.txt", x, y, phase) && phase == 3, "newest save is kept");

    fs::remove_all("saves");

    if (failures == 0) {
        std::cout << "All GameSaver tests passed\n";
    }
    return failures == 0 ? 0 : 1;
}
