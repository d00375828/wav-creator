#include "TriangleWaveform.h"
#include <cmath>

TriangleWaveform::TriangleWaveform(const std::string& name)
    : Waveform(name, "triangle") {}

TriangleWaveform::~TriangleWaveform() {}

double TriangleWaveform::generateOneSample(const double frequency, const int sample_number, const double samples_per_second) const {
    double cycle_position = computeSampleCyclePosition(frequency, sample_number, samples_per_second);
    double maximum_amplitude = getAmplitude();
    
    if (cycle_position < 0.25) {
        return (4.0 * (cycle_position - 0.0) + 0.0) * maximum_amplitude;
    } 
    else if (cycle_position < 0.75) { 
        return (-4.0 * (cycle_position - 0.25) + 1.0) * maximum_amplitude;
    } 
    else {
        return (4.0 * (cycle_position - 0.75) - 1.0) * maximum_amplitude;
    }
}

