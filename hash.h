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
        unsigned long long values[5] = {0};

        HASH_INDEX_T hash = 0;

        double numSubs = std::ceil(k.size())/6;
        int start = k.size();

        int pow = 1;
        int index = 4;
        int result = 0;

        for(int i = 0; i < numSubs; i++){
            start = k.size() - 1 - (6*i);
            if(start < 0){
                break;
            }

            for(int j = start; j >= start-5; j--){
                if(j < 0){
                    break;
                }
                char charecter = tolower(k[j]);
                int value = letterDigitToNumber(charecter);
                result = value*pow;
                pow *= 36;

                values[index] += result;
            }

            pow = 1;
            index--;
        }

        for(int i = 0; i < 5; i++){
          hash += rValues[i] * values[i];
        }
        return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= 'a' && letter <= 'z'){
            return letter - 'a';
        } else if(letter >= '0' && letter <= '9'){
            return letter - '0' + 26;
        } else {
            return 0;
        }
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
