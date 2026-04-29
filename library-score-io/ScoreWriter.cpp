#include "ScoreWriter.h"
#include <memory>
#include <string>
#include <iostream>
#include "MusicalScore.h"
#include "Waveform.h"
#include "Envelope.h"
#include "Instrument.h"
#include "ADEnvelope.h"
#include "ADSREnvelope.h"

ScoreWriter::ScoreWriter() {
}

ScoreWriter::~ScoreWriter() {
}

void ScoreWriter::writeScore(std::ostream& output_stream, const MusicalScore& score) const {
    output_stream << "SCORE" << std::endl;

    const TimeSignature& ts = score.getTimeSignature();
    output_stream << "  TIME-SIGNATURE " << ts.getBeatsPerBar() << " " << ts.getBeatValue() << std::endl;

    output_stream << "  TEMPO " << score.getTempo() << std::endl;

    output_stream << std::endl;

    for (auto it = score.getWaveforms().begin(); it != score.getWaveforms().end(); ++it) {
        writeWaveform(output_stream, score, *it->second);
    }

    for (auto it = score.getEnvelopes().begin(); it != score.getEnvelopes().end(); ++it) {
        writeEnvelope(output_stream, score, *it->second);
    }

    for (auto it = score.getInstrumentarium().begin(); it != score.getInstrumentarium().end(); ++it) {
        writeInstrument(output_stream, score, *it->second);
    }
    
    for (auto it = score.getStaves().begin(); it !=score.getStaves().end(); ++it) {
        writeStaff(output_stream, score, it->second);
    }

    output_stream << "  MIXER" << std::endl;
    output_stream << "  MIXER-END" << std::endl;
    output_stream << std::endl;

    output_stream << "SCORE-END" << std::endl;
}


void ScoreWriter::writeInstrument(std::ostream& output_stream, const MusicalScore& score, const Instrument& instrument) const {
    output_stream << "  INSTRUMENT " << instrument.getName() << std::endl;
    
    if (instrument.getWaveform()) {
        writeWaveform(output_stream, score, *instrument.getWaveform());
    }
    
    if (instrument.getEnvelope()) {
        writeEnvelope(output_stream, score, *instrument.getEnvelope());
    }
    
    output_stream << "  INSTRUMENT-END" << std::endl;
    output_stream << std::endl;
}

void ScoreWriter::writeWaveform(std::ostream& output_stream, const MusicalScore& score [[maybe_unused]], const Waveform& waveform) const {
    output_stream << "    WAVEFORM " << waveform.getName() << " " << waveform.getTypeName() << std::endl;
    
    output_stream << "      AMPLITUDE " << waveform.getAmplitude() << std::endl;
    
    output_stream << "    WAVEFORM-END" << std::endl;
    output_stream << std::endl;  
}

void ScoreWriter::writeEnvelope(std::ostream& output_stream, const MusicalScore& score [[maybe_unused]], const Envelope& envelope) const {
    output_stream << "    ENVELOPE " << envelope.getName() << " " << envelope.getTypeName() << std::endl;
    
    output_stream << "      MAXIMUM-AMPLITUDE " << envelope.getMaximumAmplitude() << std::endl;
    
    if (auto adEnv = dynamic_cast<const ADEnvelope*>(&envelope)) {
        output_stream << "      ATTACK-SECONDS " << adEnv->getAttackSeconds() << std::endl;
    }
    else if (auto adsrEnv = dynamic_cast<const ADSREnvelope*>(&envelope)) {
        output_stream << "      ATTACK-SECONDS " << adsrEnv->getAttackSeconds() << std::endl;
        output_stream << "      DECAY-SECONDS " << adsrEnv->getDecaySeconds() << std::endl;
        output_stream << "      SUSTAIN-AMPLITUDE " << adsrEnv->getSustainAmplitude() << std::endl;
        output_stream << "      RELEASE-SECONDS " << adsrEnv->getReleaseSeconds() << std::endl;
    }
    
    
    output_stream << "    ENVELOPE-END" << std::endl;
    output_stream << std::endl;  
}

void ScoreWriter::writeStaff(std::ostream& os, const MusicalScore& score, const MusicalStaff& staff) const {
    os << "  STAFF " << staff.getName() << " " << staff.getInstrument()->getName() << std::endl;

    const std::vector<StaffNote>& notes = staff.getNotes();
    for (const auto& sn : notes) {
        writeStaffNote(os, score, sn);
    }

    os << "  STAFF-END" << std::endl;
    os << std::endl;
}

void ScoreWriter::writeStaffNote(std::ostream& os, const MusicalScore& score [[maybe_unused]], const StaffNote& staff_note) const {
    os << "    " << staff_note.getStart() << " "
       << formatNote(staff_note.getNote()) << std::endl;
}

std::string ScoreWriter::getDurationLetter(const double duration) const {
    constexpr double epsilon = 0.001;

    if (std::abs(duration - (1.0 / 16.0)) < epsilon) return "s";
    if (std::abs(duration - (1.0 / 8.0)) < epsilon) return "e";
    if (std::abs(duration - (1.0 / 4.0)) < epsilon) return "q";
    if (std::abs(duration - (1.0 / 2.0)) < epsilon) return "h";
    if (std::abs(duration - 1.0) < epsilon) return "w";

    return "?"; 
}

std::string ScoreWriter::formatNote(const Note& note) const {
    return getDurationLetter(note.getDuration()) + note.getName();
}

