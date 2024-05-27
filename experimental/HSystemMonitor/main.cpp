#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

std::string readFileLine(const std::string& filepath, const std::string& key) {
    std::ifstream file(filepath);
    std::string line;

    while (std::getline(file, line)) {
        if (line.find(key) != std::string::npos) {
            return line;
        }
    }
    return "";
}

std::string trim(const std::string& str) {
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isspace(*it)) {
        it++;
    }

    std::string::const_reverse_iterator rit = str.rbegin();
    while (rit.base() != it && std::isspace(*rit)) {
        rit++;
    }

    return std::string(it, rit.base());
}

// Tokenize function to split string by spaces
std::vector<std::string> tokenize(const std::string& str) {
    std::istringstream stream(str);
    std::string token;
    std::vector<std::string> tokens;
    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

std::string getMemTotal() {
    return readFileLine("/proc/meminfo", "MemTotal");
}

std::string getCPUModel() {
    std::string line = readFileLine("/proc/cpuinfo", "model name");
    if (!line.empty()) {
        // Find the position of the colon and space
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            // Extract and trim the part after the colon
            std::string model = line.substr(colonPos + 1);
            return trim(model);
        }
    }
    return "";
}




int main() {
    std::string memTotal = getMemTotal();

    if (!memTotal.empty()) {
        std::cout << "Original string: " << memTotal << std::endl;
        auto tokens = tokenize(memTotal);
        if (tokens.size() > 2) {
            std::string value = tokens[1];
            std::string unit = tokens[2];
            std::cout << "Value: " << value << std::endl;
            std::cout << "Unit: " << unit << std::endl;
        } else {
            std::cout << "Failed to tokenize the string properly." << std::endl;
        }
    } else {
        std::cout << "MemTotal not found in /proc/meminfo" << std::endl;
    }


    std::string cpuModel = getCPUModel();
    std::cout << "CPU Model: " << cpuModel << std::endl;



    return 0;
}

