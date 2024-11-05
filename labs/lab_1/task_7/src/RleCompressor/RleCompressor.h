#ifndef RLECOMPRESSOR_H
#define RLECOMPRESSOR_H

#include "string"
#include "map"
#include "vector"

/**
 * Класс, описывающий логику Rle компрессии
 * */
class RleCompressor {

public:
    RleCompressor() = default;

    std::string compress(const std::string& initialSequence) {

        if (initialSequence.length() < 2) {
            return initialSequence;
        }

        std::string compressedSequence;


        char lastSymbol = initialSequence[0];
        char currentSymbol = initialSequence[1];
        int count = 1;

        for (int i = 1; i < initialSequence.length(); i++) {
            currentSymbol = initialSequence[i];

            if (lastSymbol == currentSymbol) {
                count+=1;
                lastSymbol = currentSymbol;

                continue;
            }

            if (count != 1) {
                compressedSequence+=std::to_string(count);
            }

            compressedSequence+=lastSymbol;

            lastSymbol = currentSymbol;
            count = 1;
        }

            if (count != 1) {
                compressedSequence+=std::to_string(count);
            }

            compressedSequence+=lastSymbol;

            lastSymbol = currentSymbol;
            count = 1;

        return compressedSequence;
    };
};


#endif //RLECOMPRESSOR_H
