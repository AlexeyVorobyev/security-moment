#ifndef UTILS_H
#define UTILS_H

#include "vector"
#include "string"


class Utils {

public:

    template<class InputIterator, class OutputIterator, class Predicate>
    static OutputIterator copyIf(
            InputIterator first,
            InputIterator last,
            OutputIterator result,
            Predicate pred
    ) {
        while (first != last) {
            if (pred(*first))
                *result++ = *first;
            ++first;
        }
        return result;
    }

    static std::vector<std::string> splitString(std::string s, std::string delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }

        res.push_back (s.substr (pos_start));
        return res;
    }
};


#endif //UTILS_H
