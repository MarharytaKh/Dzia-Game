#include "GameSaver.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;
//I took the idea of how to implement saving in the game from here (video is in russian... (ಥ ▽ ಥ) )
//https://www.youtube.com/watch?v=Rq2wina7tOc&t=158s
GameSaver::GameSaver() {
    if (!fs::exists(saveDir)) {
        fs::create_directory(saveDir);
    }
}

void GameSaver::deleteOldestSave() const {
    std::vector<fs::directory_entry> files;
    for (const auto& entry : fs::directory_iterator(saveDir)) {
        files.push_back(entry);
    }
    if (files.size() >= maxSaves) {
        auto oldestFile = std::min_element(files.begin(), files.end(),
                  [](const fs::directory_entry& a, const fs::directory_entry& b) {
                                               return fs::last_write_time(a) < fs::last_write_time(b);
                                           });
        fs::remove(oldestFile->path());
    }
}

void GameSaver::saveGame(const std::string& fileName, int heroX, int heroY, int phase) {
    deleteOldestSave();
    std::ofstream outFile(std::string(saveDir) + "/" + fileName);
    if (outFile.is_open()) {

        outFile << heroX << "\n";
        outFile << heroY << "\n";
        outFile << phase << "\n";
        outFile.close();
    } else {
        std::cerr << "Failed to open file for writing\n";
    }
}

bool GameSaver::loadGame(const std::string& fileName,  int &heroX, int &heroY, int &phase) {
    std::ifstream inFile(std::string(saveDir) + "/" + fileName);
    if (inFile.is_open()) {
        inFile >> heroX;
        inFile >> heroY;
        inFile >> phase;
        inFile.close();
        return true;
    } else {
        std::cerr << "Failed to open file for reading\n";
        return false;
    }
}

std::vector<std::string> GameSaver::getSaveFiles() {
    std::vector<std::string> saveFiles;
    for (const auto& entry : fs::directory_iterator(saveDir)) {
        saveFiles.push_back(entry.path().filename().string());
    }
    return saveFiles;
}