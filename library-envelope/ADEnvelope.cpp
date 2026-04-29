#include "ADEnvelope.h"

// Constructor: Default values for AD envelope
ADEnvelope::ADEnvelope(const std::string& name)
    : ADSREnvelope(name, "AD", 1.0, 0.0, 0.0, 0.0, 0.0) {}

// Constructor: Uses specified attack time, other values set to 0 or default
ADEnvelope::ADEnvelope(const std::string& name, const double maximum_amplitude, const double attack_seconds)
    : ADSREnvelope(name, "AD", maximum_amplitude, attack_seconds, 0.0, 0.0, 0.0) {}

// Destructor
ADEnvelope::~ADEnvelope() {}

// Generates amplitude values for an AD envelope
void ADEnvelope::generateAmplitudes(const double seconds, const int samples_per_second, AudioTrack& track) const {
    // Check if there's enough time to complete the attack stage
    if (seconds < getAttackSeconds()) {
        return;
    }
    track.setSize(samples_per_second,seconds);

    // Compute sample positions
    int attack_samples = (getAttackSeconds() * samples_per_second);
    int decay_samples = (seconds * samples_per_second);

    // Assign attack phase amplitudes (0 to max amplitude)
    assignAttackAmplitudes(0, attack_samples, track, 0.0, getMaximumAmplitude());

    // Assign decay phase amplitudes (max amplitude to 0)
    assignDecayAmplitudes(attack_samples, decay_samples, track, getMaximumAmplitude(), 0.0);
}
