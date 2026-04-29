// SquareWaveform.h
#ifndef SQUARE_WAVEFORM_H
#define SQUARE_WAVEFORM_H

#include "Waveform.h"

class SquareWaveform : public Waveform {
public:
    SquareWaveform(const std::string& name);
    virtual ~SquareWaveform();

    virtual double generateOneSample(const double frequency, const int sample_number, const double samples_per_second) const override;
};

#endif // SQUARE_WAVEFORM_H