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

        std::map<char,int> symbolFrequency;

        std::vector<char> symbolOrder;

        for (const char &item: initialSequence) {
            if (symbolFrequency[item]) {
                symbolFrequency[item] += 1;
            }
            else {
                symbolFrequency[item] = 1;
                symbolOrder.insert(symbolOrder.end(),item);
            }
        }

        std::string compressedSequence;

        for (const char item: symbolOrder) {
            compressedSequence += item;

            int frequency = symbolFrequency[item];

            if (frequency > 1) {
                compressedSequence += std::to_string(frequency);
            }
        }

        return compressedSequence;
    };
};


#endif //RLECOMPRESSOR_H
