#pragma once

#include <string>
#include <vector>

class CSVReader {
public:
    CSVReader();
    ~CSVReader();
    static const std::vector<int>& load(const char* fileName);
    static int getWidth();
    static int getHeight();

private:
    static std::vector<int> mCSV;
    static int mWidthCount;
    static int mHeightCount;
};
