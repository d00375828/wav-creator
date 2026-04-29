#ifndef AD_ENVELOPE_H
#define AD_ENVELOPE_H

#include "ADSREnvelope.h"

class ADEnvelope : public ADSREnvelope {
public:
    // Constructors
    ADEnvelope(const std::string& name);
    ADEnvelope(const std::string& name, const double maximum_amplitude, const double attack_seconds);

    // Destructor
    virtual ~ADEnvelope();

    // Amplitude generation
    virtual void generateAmplitudes(const double seconds, const int samples_per_second, AudioTrack& track) const override;
};

#endif // AD_ENVELOPE_H
