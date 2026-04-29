#include "MusicalStaff.h"

// Constructors and Destructor
MusicalStaff::MusicalStaff() : name(""), instrument(nullptr), notes() {}

MusicalStaff::MusicalStaff(std::shared_ptr<Instrument> instr)
    : name(""), instrument(instr), notes() {}

MusicalStaff::MusicalStaff(const std::string& name, std::shared_ptr<Instrument> instr)
    : name(name), instrument(instr), notes() {}

MusicalStaff::MusicalStaff(const MusicalStaff& src)
    : name(src.name), instrument(src.instrument), notes(src.notes) {}

MusicalStaff::~MusicalStaff() {}

std::string MusicalStaff::toString() const {
    std::string instr_name = (instrument) ? instrument->getName() : "(no instrument)";
    return name + " " + instr_name;
}

const std::string& MusicalStaff::getName() const {
    return name;
}

void MusicalStaff::setName(const std::string& new_name) {
    name = new_name;
}

std::shared_ptr<Instrument> MusicalStaff::getInstrument() {
    return instrument;
}

std::shared_ptr<const Instrument> MusicalStaff::getInstrument() const {
    return instrument;
}

void MusicalStaff::setInstrument(std::shared_ptr<Instrument> instr) {
    instrument = instr;
}

void MusicalStaff::addNote(const StaffNote& note) {
    notes.push_back(note);
}

const std::vector<StaffNote>& MusicalStaff::getNotes() const {
    return notes;
}

// Time & Render
double MusicalStaff::getDurationInWholeNotes() const {
    double max_end = 0.0;
    for (const StaffNote& note : notes) {
        double end = note.getStart() + note.getNote().getDuration();
        if (end > max_end) {
            max_end = end;
        }
    }
    return max_end;
}

void MusicalStaff::render(const TimeSignature& time_signature, const double tempo,
                          const int samples_per_second, AudioTrack& track) const {
    if (!instrument) return;

    double seconds_per_whole_note = (time_signature.getBeatValue() * 60.0) / tempo;
    double total_seconds = getDurationInWholeNotes() * seconds_per_whole_note;

    track.setSize(samples_per_second, total_seconds);

    for (const StaffNote& sn : notes) {
        double freq = sn.getNote().getFrequency();
        double dur = sn.getNote().getDuration();
        double start = sn.getStart();

        AudioTrack temp;
        instrument->generateSamples(freq, dur * seconds_per_whole_note, samples_per_second, temp);
        track.addAt(temp, start * seconds_per_whole_note);
    }
}

std::ostream& operator<<(std::ostream& output_stream, const MusicalStaff& staff) {
    output_stream << staff.toString();
    return output_stream;
}
