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

int generateRandomInt(int min, int max){
    static std::mt19937 mt(static_cast<std::mt19937::result_type>(std::time(nullptr)));
    std::uniform_int_distribution rand(min, max);
    return rand(mt);
}
template <typename T>
void printProblem(T number, NumberSystem convertFrom, NumberSystem convertTo){
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

void generateProblem(int randNum){
    int problemNumber { (generateRandomInt(0, std::numeric_limits<std::uint8_t>::max())) };
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
            return;
    }
}

int main(){
    int numbersToConvert{ getInt("How many numbers would you like to practice? ") };
    for (auto i{0}; i < numbersToConvert; ++i){
        std::cout << std::dec << i + 1 << ": ";
        generateProblem(generateRandomInt(0, static_cast<int>(ProblemTypes::maxIndex) - 1));
    }
}

