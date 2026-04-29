#ifndef WAVWRITER_H
#define WAVWRITER_H

#include <string>
#include "MusicalScore.h"
#include "WAVFile.h"

class WavWriter {
public:
    WavWriter();
    virtual ~WavWriter();

    void writeWavFromScore(const MusicalScore& score,
                           const int samples_per_second,
                           const int bits_per_sample,
                           const std::string& wav_filename) const;
};

#endif // WAVWRITER_H
