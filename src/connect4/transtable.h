#ifndef SCRATCH_TRANSTABLE_H
#define SCRATCH_TRANSTABLE_H

#include <cassert>
#include <cstdint>
#include <vector>
#include <cstring>

// https://blog.gamesolver.org/solving-connect-four/07-transposition-table/
class TranspositionTable {

private:
    struct Entry {
        uint64_t key: 56;
        uint8_t val = UINT64_C(0);
    };

    std::vector<Entry> t;

    unsigned int index(uint64_t key) const {
        return key % t.size();
    }

public:

    TranspositionTable(unsigned int size) : t(size) {
        assert(size > 0);
    }

    void reset() {
        Entry e;
        e.key = UINT64_C(0);
        std::fill(t.begin(), t.end(), e);
//        memset(&t[0], 0, t.size() * sizeof(Entry));
    }

    void put(uint64_t key, uint8_t val) {
        assert(key < (1LL << 56));
        unsigned int i = index(key);
        t[i].key = key;
        t[i].val = val;
    }

    bool get(uint64_t key, uint8_t &out) const {
        assert(key < (1LL << 56));
        unsigned int i = index(key);
        if (t[i].key == key) {
            out = t[i].val;
            return true;
        }
        return false;
    }

};

#endif
