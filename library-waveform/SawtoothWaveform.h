#ifndef SAWTOOTH_WAVEFORM_H
#define SAWTOOTH_WAVEFORM_H

#include "Waveform.h"

class SawtoothWaveform : public Waveform {
public:
    SawtoothWaveform(const std::string& name);
    virtual ~SawtoothWaveform();
    
    virtual double generateOneSample(const double frequency, const int sample_number, const double samples_per_second) const override;
};

#endif // SAWTOOTH_WAVEFORM_H

/*TEST_PRACTICE*/