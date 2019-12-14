#include "CSVReader.h"
#include "../System/Game.h"
#include <cassert>
#include <fstream>
#include <sstream>

CSVReader::CSVReader() = default;

CSVReader::~CSVReader() = default;

const std::vector<int>& CSVReader::load(const char* fileName) {
    //中身リセット
    mCSV.clear();

    setDataDirectory();

    //読み込み開始
    std::ifstream ifs(fileName, std::ios::in);
    assert(ifs);

    std::string line;
    bool first = true;
    while (!ifs.eof()) {
        std::getline(ifs, line);

        const char delimiter = ',';
        for (const auto& s : line) {
            if (s != delimiter) {
                mCSV.emplace_back(s - 48);
            }
        }

        if (first) {
            first = false;
            mWidthCount = mCSV.size();
        }
    }
    mHeightCount = mCSV.size() / mWidthCount;

    return mCSV;
}

int CSVReader::getWidth() {
    return mWidthCount;
}

int CSVReader::getHeight() {
    return mHeightCount;
}

std::vector<int> CSVReader::mCSV;
int CSVReader::mWidthCount = 0;
int CSVReader::mHeightCount = 0;
