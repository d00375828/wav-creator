#include "Waveform.h"
#include "AudioTrack.h"
#include <cmath>
#include <string>
#include <iostream>

const double two_pi = 6.283185307179586476925286766559;

Waveform::Waveform(const std::string& name, const std::string& type_name)
    : name(name), type_name(type_name), amplitude(1.0) {}

Waveform::~Waveform() {}

const std::string& Waveform::getName() const {
    return name;
}

const std::string& Waveform::getTypeName() const {
    return type_name;
}

double Waveform::getAmplitude() const {
    return amplitude;
}

void Waveform::setName(const std::string& name) {
    this->name = name;
}

void Waveform::setTypeName(const std::string& type_name) {
    this->type_name = type_name;
}

void Waveform::setAmplitude(const double amplitude) {
    if (amplitude >= 0.0 && amplitude <= 1.0) {
        this->amplitude = amplitude;
    }
}

double Waveform::computeSampleAngle(const double frequency, const double sample_number, const int samples_per_second) const {
    double angle = two_pi * sample_number * frequency / samples_per_second;
    return angle;
}

double Waveform::computeSampleCyclePosition(const double frequency, const double sample_number, const int samples_per_second) const {
    double angle = computeSampleAngle(frequency, sample_number, samples_per_second);
    double remaining_angle = std::fmod(angle, two_pi);
    return remaining_angle / two_pi;
}

void Waveform::generateSamples(const double frequency, const double seconds, const int samples_per_second, AudioTrack& track) const {
    int total_samples = static_cast<int>(seconds * samples_per_second);
    track.setSize(samples_per_second, seconds);

    for (int i = 0; i < total_samples; ++i) {
        track.setValue(i, generateOneSample(frequency, i, samples_per_second));
    }
} 
