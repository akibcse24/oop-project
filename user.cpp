#include "user.h"
#include <random>
#include <string>

// Helper to extract numeric part from ID strings
int User::extractIdNumber(const std::string& id, const std::string& prefix) {
    if (id.substr(0, prefix.length()) == prefix) {
        std::string numStr = id.substr(prefix.length());
        if (!numStr.empty()) {
            try {
                return std::stoi(numStr);
            } catch (...) {
                return 0;
            }
        }
    }
    return 0;
}

// Helper to generate formatted ID with leading zeros
std::string User::generateFormattedId(int number, const std::string& prefix, int totalLength) {
    std::string numStr = std::to_string(number);
    std::string id = prefix + numStr;
    // Pad with leading zeros to reach desired length
    while (id.length() < totalLength) {
        id = "0" + id;
    }
    return id;
}

// Helper to generate random password
int User::generatePassword() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(10000, 99999);
    return dis(gen);
}