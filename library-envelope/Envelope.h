#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <string>
#include <iostream>
#include "AudioTrack.h"

// Keyword constants for ScoreReader and related components
inline const std::string MAXIMUM_AMPLITUDE = "MAXIMUM-AMPLITUDE";
inline const std::string ATTACK_SECONDS = "ATTACK-SECONDS";
inline const std::string DECAY_SECONDS = "DECAY-SECONDS";
inline const std::string SUSTAIN_AMPLITUDE = "SUSTAIN-AMPLITUDE";
inline const std::string RELEASE_SECONDS = "RELEASE-SECONDS";

class Envelope {
protected:
    std::string name;
    std::string type_name;
    double maximum_amplitude;

public:
    Envelope(const std::string& name, const std::string& type_name);
    Envelope(const std::string& name, const std::string& type_name, double amplitude);
    virtual ~Envelope();

    virtual void generateAmplitudes(double seconds, int samples_per_second, AudioTrack& track) const = 0;

    const std::string& getName() const;
    const std::string& getTypeName() const;
    double getMaximumAmplitude() const;

    void setName(const std::string& name);
    void setTypeName(const std::string& type_name);
    void setMaximumAmplitude(const double amplitude);
};

#endif // ENVELOPE_H
