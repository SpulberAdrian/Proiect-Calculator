#pragma once
#include <fstream>
#include <string>

class FileHandler {
private:
    std::ifstream inputFile;
    std::ofstream outputFile;
public:
    FileHandler(const std::string& inputFilePath, const std::string& outputFilePath) {
        inputFile.open(inputFilePath);
        outputFile.open(outputFilePath, std::ios_base::app | std::ios_base::out);
        if (!outputFile) {
            outputFile.open(outputFilePath, std::ios_base::app | std::ios_base::out);
        }
    }

    ~FileHandler() {
        if (inputFile.is_open()) {
            inputFile.close();
        }
        if (outputFile.is_open()) {
            outputFile.close();
        }
    }

    bool isInputFileOpen() const {
        return inputFile.is_open();
    }

    bool isEndOfFile() const {
        return inputFile.eof();
    }

    void readFromFile(std::string& expression) {
        if (inputFile.is_open()) {
            inputFile >> expression;
        }
    }

    void writeToFile(const std::string& result) {
        if (outputFile.is_open()) {
            outputFile << result << std::endl;
        }
    }
};
