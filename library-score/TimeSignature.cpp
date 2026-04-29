#include "TimeSignature.h"

TimeSignature::TimeSignature()
    : beatsPerBar(4), beatValue(4) {}

TimeSignature::TimeSignature(const int beats_per_bar, const int beat_value)
    : beatsPerBar(4), beatValue(4) {
    setBeatsPerBar(beats_per_bar);
    setBeatValue(beat_value);
}

int TimeSignature::getBeatsPerBar() const {
    return beatsPerBar;
}

int TimeSignature::getBeatValue() const {
    return beatValue;
}

void TimeSignature::setBeatsPerBar(const int beats_per_bar) {
    if (beats_per_bar >= 1) {
        beatsPerBar = beats_per_bar;
    }
}

void TimeSignature::setBeatValue(const int beat_value) {
    if (beat_value >= 1) {
        beatValue = beat_value;
    }
}
