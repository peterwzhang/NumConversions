# Number Conversion Problem Generator

This is a program made in C++ that randomly generates number system conversion problems.

## Problem Types

The following problem types can be generated:

1. binary to octal
2. binary to decimal
3. binary to hexadecimal
4. octal to binary
5. octal to decimal
6. octal to hexadecimal
7. decimal to binary
8. decimal to octal
9. decimal to hexadecimal
10. hexadecimal to binary
11. hexadecimal to octal
12. hexadecimal to decimal

## Installation

You can compile the program by using the makefile provided in the repository.

```text
git clone https://github.com/PeterTheAmazingAsian/NumConversions.git
cd NumConversions
make release
./NumConversions
```

## Usage

Upon running the program, the user will be prompted for a number of problems to practice. The problems will be generated one by one, then asked to the user. After each question the users' answer will be checked. Once all questions are completed a final score will be shown.

Make sure when entering octal numbers you prefix your number with a 0 and when entering hexadecimal prefix your number with 0x.
