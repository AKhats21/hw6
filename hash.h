#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long arr[5];
        size_t size = k.size();
        for (int i = 4; i >= 0; i--) {
            unsigned long long temp = 0;
            size_t n = 1;
            for (size_t j = 0; j < 6; j++) {
                //check if char position is available
                if (27 - (i * 6 + 3 - j) >= size) {
                    temp += 0;
                    // std::cout << temp;
                    break;
                }
                temp += letterDigitToNumber(k[size - (27 - (i * 6 + 3 - j)) - 1]) * n; 
                n *= 36;
            }
            arr[i] = temp;
        }
        HASH_INDEX_T x = 0;
        for (size_t i = 0; i < 5; i++) {
            x += rValues[i] * arr[i];
        }
        return x;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        //uppercase
        if (letter >= 'A' && letter <= 'Z') return letter - 'A';
        if (letter >= 'a' && letter <= 'z') return letter - 'a';
        if (letter >= '0' && letter <= '9') return 'z' - 'a' + (letter - '0') + 1;
        else return 0;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
