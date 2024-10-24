template<class InputIterator, class OutputIterator, class Predicate>
OutputIterator copyIf(
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