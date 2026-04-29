#ifndef TRIANGLE_WAVEFORM_H
#define TRIANGLE_WAVEFORM_H

#include "Waveform.h"

class TriangleWaveform : public Waveform {
public:
    TriangleWaveform(const std::string& name);
    virtual ~TriangleWaveform();
    
    virtual double generateOneSample(const double frequency, const int sample_number, const double samples_per_second) const override;
};

#endif // TRIANGLE_WAVEFORM_H

/*Exam 2*/