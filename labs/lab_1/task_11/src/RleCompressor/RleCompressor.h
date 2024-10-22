#ifndef RLECOMPRESSOR_H
#define RLECOMPRESSOR_H

#include "string"
#include "map"
#include "vector"
#include "iostream"
#include "regex"

/**
 * Класс, описывающий логику Rle компрессии
 * */
class RleCompressor {

public:

    RleCompressor() = default;

    std::string compress(const std::string& initialSequence) {
        std::string prevCompressedSequence = initialSequence;

        std::string curCompressedSequence = this->compressInternal(initialSequence);

        while(prevCompressedSequence != curCompressedSequence) {
            prevCompressedSequence = curCompressedSequence;
            curCompressedSequence = this->compressInternal(curCompressedSequence);
        }

        return curCompressedSequence;
    };

private:

    std::string compressInternal(const std::string& initialSequence) {
        if (initialSequence.length() < 2) {
            return initialSequence;
        }

        int shift = 0;
        int patternLength = 1;
        std::string pattern = initialSequence.substr(shift, patternLength);

        std::string res = initialSequence;

        while (
            patternLength < initialSequence.length() + 1 - shift
        ) {
            if (pattern == "(" || pattern == ")") {
                patternLength++;
                pattern = initialSequence.substr(shift, patternLength);
                continue;
            }
            if (this->replaceMaxRepetitionsInRow(initialSequence,pattern).is) {
                res = this->replaceMaxRepetitionsInRow(initialSequence,pattern).replaceString;
                break;
            }
            std::cout<<pattern<<std::endl;
            if (patternLength + 1 >= initialSequence.length() + 1 - shift) {
                shift++;
                patternLength = 1;
                pattern = initialSequence.substr(shift, patternLength);
            } else {
                patternLength++;
                pattern = initialSequence.substr(shift, patternLength);
            }
        }

        return res;
    }

    std::string replaceSubstring(
        const std::string& original,
        const std::string& toReplace,
        const std::string& replacement
    ) {
        std::string result;
        size_t pos = 0;
        size_t toReplaceLen = toReplace.length();

        while (true) {
            // Находим позицию первого вхождения подстроки
            size_t foundPos = original.find(toReplace, pos);

            // Если не найдено, добавляем оставшуюся часть строки и выходим из цикла
            if (foundPos == std::string::npos) {
                result += original.substr(pos);
                break;
            }

            // Добавляем часть строки до найденного вхождения
            result += original.substr(pos, foundPos - pos);

            // Добавляем замену
            result += replacement;

            // Обновляем позицию для поиска следующего вхождения
            pos = foundPos + toReplaceLen;
        }

        return result;
    }

    struct ReturnVal {
        bool is;
        std::string replaceString;
    };

    ReturnVal replaceMaxRepetitionsInRow(
        const std::string& sequence,
        const std::string& pattern
    ) {
        int replaceSequenceLength = 2;
        std::string replaceSequence = pattern + pattern;

        ReturnVal returnVal = {
            false,
            ""
        };

        if (sequence.find(replaceSequence) == std::string::npos) {
            return returnVal;
        }

        while (sequence.find(replaceSequence + pattern) != std::string::npos) {
            replaceSequenceLength +=1;
            replaceSequence+=pattern;
        }

        returnVal.replaceString = replaceSubstring(
                sequence,
                replaceSequence,
                std::to_string(replaceSequenceLength) + "(" + pattern + ")"
        );

        returnVal.is = true;

        return returnVal;
    }
};


#endif //RLECOMPRESSOR_H
