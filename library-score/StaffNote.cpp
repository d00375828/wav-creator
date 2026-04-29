#include "StaffNote.h"

// Constructors
StaffNote::StaffNote() : note(), start(0.0) {}

StaffNote::StaffNote(const Note& n, const double s) : note(n), start(0.0) {
    setStart(s);
}

// Getters
Note& StaffNote::getNote() {
    return note;
}

const Note& StaffNote::getNote() const {
    return note;
}

double StaffNote::getStart() const {
    return start;
}

// Setter
void StaffNote::setStart(const double s) {
    if (s >= 0.0) {
        start = s;
    }
}

// Output operator
std::ostream& operator<<(std::ostream& os, const StaffNote& staff_note) {
    const Note& note = staff_note.getNote();
    os << staff_note.getStart() << " "
       << note.getDuration() << " "
       << note.getName() << "(" << note.getFrequency() << ")";
    return os;
}
