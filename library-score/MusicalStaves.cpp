#include "MusicalStaves.h"

// Constructor
MusicalStaves::MusicalStaves() {}

// Destructor
MusicalStaves::~MusicalStaves() {}

void MusicalStaves::addStaff(const std::string& name, const MusicalStaff& staff) {
    mStaves[name] = staff;
}

MusicalStaff& MusicalStaves::getStaff(const std::string& name) {
    auto it = mStaves.find(name);
    if (it != mStaves.end()) {
        return it->second;
    }

    static MusicalStaff static_empty;
    return static_empty;
}

const MusicalStaff& MusicalStaves::getStaff(const std::string& name) const {
    auto it = mStaves.find(name);
    if (it != mStaves.end()) {
        return it->second;
    }

    static MusicalStaff static_empty;
    return static_empty;
}

unsigned int MusicalStaves::size() const {
    return static_cast<unsigned int>(mStaves.size());
}

// Iterators
MusicalStaves::iterator MusicalStaves::begin() {
    return mStaves.begin();
}

MusicalStaves::const_iterator MusicalStaves::begin() const {
    return mStaves.begin();
}

MusicalStaves::iterator MusicalStaves::end() {
    return mStaves.end();
}

MusicalStaves::const_iterator MusicalStaves::end() const {
    return mStaves.end();
}

// Test
void MusicalStaves::removeStaff(const std::string& name) {
    mStaves.erase(name);
}
