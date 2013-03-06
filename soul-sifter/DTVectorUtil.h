//
//  DTVectorUtil.h
//  soul-sifter
//
//  Created by Robby Neale on 2/22/13.
//
//

#ifndef soul_sifter_DTVectorUtil_h
#define soul_sifter_DTVectorUtil_h

#include <vector.h>

namespace dogatech {

    template <typename T>
    static bool appendUniqueVector(const vector<T>& src, vector<T>* dest) {
        bool updated = false;
        for (typename vector<T>::const_iterator it = src.begin(); it != src.end(); ++it) {
            if (std::find(dest->begin(), dest->end(), *it) == dest->end()) {
                updated = true;
                dest->push_back(*it);
            }
        }
        return updated;
    }
    
    template <typename T>
    static bool containsVector(const vector<T>& src, const vector<T>& dest) {
        for (typename vector<T>::const_iterator it = src.begin(); it != src.end(); ++it) {
            if (std::find(dest.begin(), dest.end(), *it) == dest.end()) {
                return false;
            }
        }
        return true;
    }
    
    template <typename T>
    static bool equivalentVectors(const vector<T>& l, const vector<T>& r) {
        if (l.size() != r.size()) return false;
        return containsVector(l, r) && containsVector(r, l);
    }

}  // namespace soulsifter

#endif
