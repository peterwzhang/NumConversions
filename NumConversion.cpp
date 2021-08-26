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

void applyPrintFormat(const NumberSystem ns){
    switch (ns){
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
            std::cout << "0b" << std::dec;
        default:
            break;
    }
}

template <typename T>
void printProblem(const T number, const NumberSystem convertFrom, const NumberSystem convertTo){
    std::cout << "Convert ";
    applyPrintFormat(convertFrom);
    std::cout << number << " to " << nsToString(convertTo) << '\n';
}

int getAns(const NumberSystem convertTo){
    std::cout << "Please enter an ";
    switch (convertTo){
        case NumberSystem::binary:
            std::cout << "binary number: ";
            std::cin >> std::dec;
            break;
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
    if (convertTo == NumberSystem::binary){
        std::bitset<8> ans{};
        std::cin >> ans;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return static_cast<int>(ans.to_ulong());
    }
    // convert to non binary
    int ans{};
    std::cin >> ans;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return ans;
}

//TODO: fix this
template <size_t S>
bool testProblem(const std::bitset<S> problemNumber, const NumberSystem convertTo){
    int userAns{ getAns(convertTo) };
    int ans = static_cast<int>(problemNumber.to_ulong()); // okay conversion (0-255 range)
    if (userAns == ans){
        std::cout << "Correct!\n";
        return true;
    }
    else{
        std::cout << "Incorrect, the answer is: ";
        applyPrintFormat(convertTo);
        std::cout << ans << '\n';
        return false;
    }
}

bool testProblem(const int problemNumber, const NumberSystem convertTo){
    int userAns{ getAns(convertTo) };
    if (userAns == problemNumber){
        std::cout << "Correct!\n";
        return true;
    }
    else{
        std::cout << "Incorrect, the answer is: ";
        applyPrintFormat(convertTo);
        if (convertTo == NumberSystem::binary){
            std::cout << std::bitset<8>(problemNumber) << '\n';
        }
        else {
            std::cout << problemNumber << '\n';
        }
        return false;
    }
}

bool generateProblem(int randNum){
    const int problemNumber { (generateRandomInt(0, std::numeric_limits<std::uint8_t>::max())) }; // 0-255 range should be good
    switch(static_cast<ProblemTypes>(randNum)){
        case ProblemTypes::binaryToOctal:
            printProblem(std::bitset<8>(problemNumber), NumberSystem::binary, NumberSystem::octal);
            return testProblem(std::bitset<8>(problemNumber), NumberSystem::octal);
        case ProblemTypes::binaryToDecimal:
            printProblem(std::bitset<8>(problemNumber), NumberSystem::binary, NumberSystem::decimal);
            return testProblem(std::bitset<8>(problemNumber), NumberSystem::decimal);
        case ProblemTypes::binaryToHexadecimal:
            printProblem(std::bitset<8>(problemNumber), NumberSystem::binary, NumberSystem::hexadecimal);
            return testProblem(std::bitset<8>(problemNumber), NumberSystem::hexadecimal);
        case ProblemTypes::octalToBinary:
            printProblem(problemNumber, NumberSystem::octal, NumberSystem::binary);
            return testProblem(problemNumber, NumberSystem::binary);
        case ProblemTypes::octalToDecimal:
            printProblem(problemNumber, NumberSystem::octal, NumberSystem::decimal);
            return testProblem(problemNumber, NumberSystem::decimal);
        case ProblemTypes::octalToHexadecimal:
            printProblem(problemNumber, NumberSystem::octal, NumberSystem::hexadecimal);
            return testProblem(problemNumber, NumberSystem::hexadecimal);
        case ProblemTypes::decimalToBinary:
            printProblem(problemNumber, NumberSystem::decimal, NumberSystem::binary);
            return testProblem(problemNumber, NumberSystem::binary);
        case ProblemTypes::decimalToOctal:
            printProblem(problemNumber, NumberSystem::decimal, NumberSystem::octal);
            return testProblem(problemNumber, NumberSystem::octal);
        case ProblemTypes::decimalToHexadecimal:
            printProblem(problemNumber, NumberSystem::decimal, NumberSystem::hexadecimal);
            return testProblem(problemNumber, NumberSystem::hexadecimal);
        case ProblemTypes::hexadecimalToBinary:
            printProblem(problemNumber, NumberSystem::hexadecimal, NumberSystem::binary);
            return testProblem(problemNumber, NumberSystem::binary);
        case ProblemTypes::hexadecimalToOctal:
            printProblem(problemNumber, NumberSystem::hexadecimal, NumberSystem::octal);
            return testProblem(problemNumber, NumberSystem::octal);
        case ProblemTypes::hexadecimalToDecimal:
            printProblem(problemNumber, NumberSystem::hexadecimal, NumberSystem::decimal);
            return testProblem(problemNumber, NumberSystem::decimal);
        default: // should never reach here
            return false;
    }
}

void askProblems(const int numbersToConvert){
    int correct{ 0 };
    for (auto i{0}; i < numbersToConvert; ++i){
        std::cout << std::dec << i + 1 << ": ";
        if (generateProblem(generateRandomInt(0, static_cast<int>(ProblemTypes::maxIndex) - 1))){
            ++correct;
        }
    }
    std::cout << std::dec;
    std::cout << "You got " << correct << " correct out of " << numbersToConvert << '\n';
}


int main(){
    const int numbersToConvert{ getInt("How many numbers would you like to practice? ") };
    askProblems(numbersToConvert);
    return 0;
}

