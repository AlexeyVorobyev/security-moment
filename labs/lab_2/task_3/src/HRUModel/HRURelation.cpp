#include "set"
#include "string"
#include "HRURightEnum.cpp"

struct HRURelation {
    std::string object;
    std::string subject;
    HRURightEnum right;
};

struct HRURelationComparator {
    bool operator()(
            HRURelation a,
            HRURelation b
    ) const {
        return !(a.subject == b.subject
               && a.object == b.object
               && a.right == b.right);
    }
};