#include "AudioTrack.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

// Default constructor initializes data members to zero
AudioTrack::AudioTrack() : samplesPerSecond(0), seconds(0.0), values() {}

int AudioTrack::getSamplesPerSecond() const {
    return samplesPerSecond;
}

double AudioTrack::getSeconds() const {
    return seconds;
}

unsigned int AudioTrack::getSize() const {
    return values.size();
}

void AudioTrack::setSamplesPerSecond(const int newSamplesPerSecond) {
    if (newSamplesPerSecond < 1) {
        return;
    }
    samplesPerSecond = newSamplesPerSecond;
    resizeValues();
}

void AudioTrack::setSeconds(const double newSeconds) {
    if (newSeconds <= 0.0) {
        return; 
    }
    seconds = newSeconds;
    resizeValues();
}

void AudioTrack::setSize(const int newSamplesPerSecond, const double newSeconds) {
    if (newSamplesPerSecond < 1 || newSeconds <= 0.0) {
        return; 
    }
    samplesPerSecond = newSamplesPerSecond;
    seconds = newSeconds;
    resizeValues();
}

bool AudioTrack::indexValid(const unsigned int index) const {
    return index < values.size();
}

double AudioTrack::getValue(const unsigned int index) const {
    if (!indexValid(index)) {
        return -INFINITY;
    }
    return values[index];
}

void AudioTrack::setValue(const unsigned int index, const double value) {
    if (indexValid(index)) {
        values[index] = value;
    }
}

void AudioTrack::resizeValues() {
    if (samplesPerSecond > 0 && seconds > 0) {
        values.clear();
        values.resize(static_cast<unsigned int>(samplesPerSecond * seconds), 0.0);
    }
}
AudioTrack AudioTrack::operator*(const AudioTrack& rhs) const {
    if (this->samplesPerSecond != rhs.getSamplesPerSecond()) {
        throw std::invalid_argument("Sample rates do not match");
    }
    if (this->getSize() != rhs.getSize()) {
        throw std::invalid_argument("Track sizes do not match");
    }

    AudioTrack newTrack;
    newTrack.setSize(this->samplesPerSecond, this->seconds);

    for (size_t i = 0; i < this->values.size(); ++i) {
        double num = this->values[i] * rhs.getValue(i);
        newTrack.setValue(i, num);
    } 

    return newTrack;
}


void AudioTrack::addAt(const AudioTrack& other_track, double offset_seconds) {
    if (samplesPerSecond <= 0 || other_track.getSamplesPerSecond() != samplesPerSecond) {
        return;
    }

    int start_index = static_cast<int>(offset_seconds * samplesPerSecond);
    if (start_index < 0) return;

    int needed_size = start_index + other_track.getSize();
    if (needed_size > static_cast<int>(values.size())) {
        values.resize(needed_size, 0.0);
        seconds = static_cast<double>(values.size()) / samplesPerSecond;
    }

    for (unsigned int i = 0; i < other_track.getSize(); ++i) {
        values[start_index + i] += other_track.getValue(i);
    }
}


