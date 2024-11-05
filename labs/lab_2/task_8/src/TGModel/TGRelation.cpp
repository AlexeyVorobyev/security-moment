#include "set"
#include "string"
#include "TGRightEnum.cpp"

struct TGRelation {
    std::string nodeFirst;
    std::string nodeSecond;
    TGRightEnum right;
};

struct TGRelationComparator {
    bool operator()(
            TGRelation a,
            TGRelation b
    ) const {
        return !(a.nodeFirst == b.nodeFirst
               && a.nodeSecond == b.nodeSecond
               && a.right == b.right);
    }
};