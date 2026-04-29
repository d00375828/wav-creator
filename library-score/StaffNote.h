#ifndef STAFF_NOTE_H
#define STAFF_NOTE_H

#include "Note.h"
#include <iostream>

class StaffNote {
protected:
    Note note;
    double start;

public:
    StaffNote();
    StaffNote(const Note& note, const double start);

    Note& getNote();
    const Note& getNote() const;

    double getStart() const;
    void setStart(const double start);
};

// Free function
std::ostream& operator<<(std::ostream& os, const StaffNote& staff_note);

#endif // STAFF_NOTE_H
