#ifndef SCOREREADER_H
#define SCOREREADER_H

#include <iostream>
#include <memory>
#include <string>
#include "MusicalScore.h"
#include "Waveform.h"
#include "Envelope.h"
#include "MusicalStaff.h"

class ScoreReader {
public:
    ScoreReader();
    virtual ~ScoreReader();

    void readScore(std::istream& input_stream, MusicalScore& score) const;
    void readStaff(std::istream& is, MusicalScore& score, MusicalStaff& staff) const;

    std::shared_ptr<Waveform> readWaveform(std::istream& input_stream, MusicalScore& score) const;
    std::shared_ptr<Envelope> readEnvelope(std::istream& input_stream, MusicalScore& score) const;
    std::shared_ptr<Instrument> readInstrument(std::istream& is, MusicalScore& score) const;
};

#endif /* SCOREREADER_H */
