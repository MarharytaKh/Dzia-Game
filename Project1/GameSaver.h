#pragma once
#include <string>
#include <vector>

class GameSaver {
private:
    static constexpr const char* saveDir = "saves";
    const int maxSaves = 3;

    void deleteOldestSave() const;

public:
    GameSaver();

    static std::vector<std::string> getSaveFiles();

    void saveGame(const std::string &fileName, int heroX, int heroY, int phase);

    static bool loadGame(const std::string &fileName, int &heroX, int &heroY, int &phase);
};


