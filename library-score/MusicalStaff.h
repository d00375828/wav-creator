#ifndef MUSICAL_STAFF_H
#define MUSICAL_STAFF_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "StaffNote.h"
#include "Instrument.h"
#include "TimeSignature.h"
#include "AudioTrack.h"

class MusicalStaff {
protected:
    std::string name;
    std::shared_ptr<Instrument> instrument;
    std::vector<StaffNote> notes;

public:
    MusicalStaff();
    MusicalStaff(std::shared_ptr<Instrument> instrument);
    MusicalStaff(const std::string& name, std::shared_ptr<Instrument> instrument);
    MusicalStaff(const MusicalStaff& src);
    virtual ~MusicalStaff();

    MusicalStaff& operator=(const MusicalStaff& rhs) = default;

    virtual std::string toString() const;

    const std::string& getName() const;
    void setName(const std::string& name);

    std::shared_ptr<Instrument> getInstrument();
    std::shared_ptr<const Instrument> getInstrument() const;
    void setInstrument(std::shared_ptr<Instrument> instrument);

    void addNote(const StaffNote& note);
    const std::vector<StaffNote>& getNotes() const;

    double getDurationInWholeNotes() const;

    void render(const TimeSignature& time_signature, const double tempo,
                const int samples_per_second, AudioTrack& track) const;
};

// Free function
std::ostream& operator<<(std::ostream& output_stream, const MusicalStaff& staff);

#endif // MUSICAL_STAFF_H
