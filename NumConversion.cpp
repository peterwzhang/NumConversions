#include <bitset>
#include <cstdint>
#include <ctime>
#include <ios>
#include <iostream>
#include <limits>
#include <random>
#include <string_view>

enum class NumberSystem{
    binary,
    octal,
    decimal,
    hexadecimal
};

std::string_view nsToString(NumberSystem ns){
    switch (ns) {
        case NumberSystem::binary:
            return std::string_view{ "binary" };
        case NumberSystem::octal:
            return std::string_view{ "octal" };
        case NumberSystem::decimal:
            return std::string_view{ "decimal" };
        case NumberSystem::hexadecimal:
            return std::string_view{ "hexadecimal" };
        default: // should never reach here
            return std::string_view{ "none" };
    }
}

enum class ProblemTypes{
    binaryToOctal,
    binaryToDecimal,
    binaryToHexadecimal,
    octalToBinary,
    octalToDecimal,
    octalToHexadecimal,
    decimalToBinary,
    decimalToOctal,
    decimalToHexadecimal,
    hexadecimalToBinary,
    hexadecimalToOctal,
    hexadecimalToDecimal,
    maxIndex // range 0 -> (maxIndex - 1)
};

int getInt(std::string_view prompt){
    int userInput{};
    while (true){
        std::cout << prompt;
        std::cin >> userInput;
        if (std::cin.fail()){
            std::cout << "Invalid input, please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    return userInput;
}

int generateRandomInt(const int min, const int max){
    static std::mt19937 mt(static_cast<std::mt19937::result_type>(std::time(nullptr)));
    std::uniform_int_distribution rand(min, max);
    return rand(mt);
}
template <typename T>
void printProblem(const T number, const NumberSystem convertFrom, const NumberSystem convertTo){
    std::cout << "Convert ";
    switch (convertFrom){
        case NumberSystem::octal:
            std::cout << '0' << std::oct;
            break;
        case NumberSystem::decimal:
            std::cout << std::dec;
            break;
        case NumberSystem::hexadecimal:
            std::cout << "0x" << std::hex;
            break;
        case NumberSystem::binary:
            std::cout << "0b";
        default:
            break;
    }
    std::cout << number << " to " << nsToString(convertTo) << ": \n";
}

int getAns(const NumberSystem convertTo){
    std::cout << "Please enter an ";
    // ? this probably is not needed, but will test
    switch (convertTo){
        case NumberSystem::binary:
            std::cout << "binary number (put a 0b in the front): ";
            std::cin >> std::dec;
        case NumberSystem::octal:
            std::cout << "octal number (put a 0 in the front): ";
            std::cin >> std::oct;
            break;
        case NumberSystem::decimal:
            std::cout << "decimal number: ";
            std::cin >> std::dec;
            break;
        case NumberSystem::hexadecimal:
            std::cout << "hexadecimal number (put a 0x in the front): ";
            std::cin >> std::hex;
            break;
        default:
            return -1;
    }
    int ans{};
    std::cin >> ans;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return ans;
}

template <size_t S>
bool testProblem(const std::bitset<S> problemNumber, const NumberSystem convertTo){
    
}

bool testProblem(const int problemNumber, const NumberSystem convertTo){

}

bool generateProblem(int randNum){
    const int problemNumber { (generateRandomInt(0, std::numeric_limits<std::uint8_t>::max())) }; // 0-255 range should be good
    switch(static_cast<ProblemTypes>(randNum)){
        case ProblemTypes::binaryToOctal:
            printProblem(std::bitset<8>(problemNumber), NumberSystem::binary, NumberSystem::octal);
            break;
        case ProblemTypes::binaryToDecimal:
            printProblem(std::bitset<8>(problemNumber), NumberSystem::binary, NumberSystem::decimal);
            break;
        case ProblemTypes::binaryToHexadecimal:
            printProblem(std::bitset<8>(problemNumber), NumberSystem::binary, NumberSystem::hexadecimal);
            break;
        case ProblemTypes::octalToBinary:
            printProblem(problemNumber, NumberSystem::octal, NumberSystem::binary);
            break;
        case ProblemTypes::octalToDecimal:
            printProblem(problemNumber, NumberSystem::octal, NumberSystem::decimal);
            break;
        case ProblemTypes::octalToHexadecimal:
            printProblem(problemNumber, NumberSystem::octal, NumberSystem::hexadecimal);
            break;
        case ProblemTypes::decimalToBinary:
            printProblem(problemNumber, NumberSystem::decimal, NumberSystem::binary);
                break;
        case ProblemTypes::decimalToOctal:
            printProblem(problemNumber, NumberSystem::decimal, NumberSystem::octal);
            break;
        case ProblemTypes::decimalToHexadecimal:
            printProblem(problemNumber, NumberSystem::decimal, NumberSystem::hexadecimal);
            break;
        case ProblemTypes::hexadecimalToBinary:
            printProblem(problemNumber, NumberSystem::hexadecimal, NumberSystem::binary);
            break;
        case ProblemTypes::hexadecimalToOctal:
            printProblem(problemNumber, NumberSystem::hexadecimal, NumberSystem::octal);
            break;
        case ProblemTypes::hexadecimalToDecimal:
            printProblem(problemNumber, NumberSystem::hexadecimal, NumberSystem::decimal);
            break;
        default: // should never reach here
            return false;
    }
}

int main(){
    const int numbersToConvert{ getInt("How many numbers would you like to practice? ") };
    for (auto i{0}; i < numbersToConvert; ++i){
        std::cout << std::dec << i + 1 << ": ";
        generateProblem(generateRandomInt(0, static_cast<int>(ProblemTypes::maxIndex) - 1));
    }
}

