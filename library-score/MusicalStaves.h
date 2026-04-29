#ifndef MUSICAL_STAVES_H
#define MUSICAL_STAVES_H

#include <map>
#include <string>
#include "MusicalStaff.h"

class MusicalStaves {
protected:
    std::map<std::string, MusicalStaff> mStaves;

public:
    MusicalStaves();
    virtual ~MusicalStaves();

    void addStaff(const std::string& name, const MusicalStaff& staff);
    
    MusicalStaff& getStaff(const std::string& name);
    const MusicalStaff& getStaff(const std::string& name) const;

    unsigned int size() const;

    typedef std::map<std::string, MusicalStaff>::iterator iterator;
    typedef std::map<std::string, MusicalStaff>::const_iterator const_iterator;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

//Test
    void removeStaff(const std::string& name);
};

#endif // MUSICAL_STAVES_H
