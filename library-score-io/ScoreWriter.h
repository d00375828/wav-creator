#ifndef SCOREWRITER_H
#define SCOREWRITER_H

#include <iostream>
#include <memory>
#include <string>
#include "MusicalScore.h"
#include "Waveform.h"
#include "Envelope.h"
#include "Instrument.h"
#include "MusicalStaff.h"

class ScoreWriter {
public:
    ScoreWriter();
    virtual ~ScoreWriter();

    void writeScore(std::ostream& output_stream, const MusicalScore& score) const;
    void writeInstrument(std::ostream& output_stream, const MusicalScore& score, const Instrument& instrument) const;
    void writeWaveform(std::ostream& output_stream, const MusicalScore& score, const Waveform& waveform) const;
    void writeEnvelope(std::ostream& output_stream, const MusicalScore& score, const Envelope& envelope) const;
    void writeStaff(std::ostream& os, const MusicalScore& score, const MusicalStaff& staff) const;
    void writeStaffNote(std::ostream& os, const MusicalScore& score, const StaffNote& staff_note) const;
    
    std::string getDurationLetter(const double duration) const;
    std::string formatNote(const Note& note) const;
};

#endif /* SCOREWRITER_H */