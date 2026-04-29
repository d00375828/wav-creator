#include "MusicalScore.h"

MusicalScore::MusicalScore()
    : timeSignature(), tempo(100.0) {}

MusicalScore::MusicalScore(const TimeSignature& ts, const double tempo_value)
    : timeSignature(ts), tempo(tempo_value > 0.0 ? tempo_value : 100.0) {}

Waveforms& MusicalScore::getWaveforms() {
    return waveforms;
}

const Waveforms& MusicalScore::getWaveforms() const {
    return waveforms;
}

Envelopes& MusicalScore::getEnvelopes() {
    return envelopes;
}

const Envelopes& MusicalScore::getEnvelopes() const {
    return envelopes;
}

Instrumentarium& MusicalScore::getInstrumentarium() {
    return instruments;
}

const Instrumentarium& MusicalScore::getInstrumentarium() const {
    return instruments;
}

TimeSignature& MusicalScore::getTimeSignature() {
    return timeSignature;
}

const TimeSignature& MusicalScore::getTimeSignature() const {
    return timeSignature;
}

double MusicalScore::getTempo() const {
    return tempo;
}

void MusicalScore::setTempo(const double new_tempo) {
    if (new_tempo > 0.0) {
        tempo = new_tempo;
    }
}

void MusicalScore::addStaff(const MusicalStaff& staff) {
    staves.addStaff(staff.getName(), staff);
}

MusicalStaff& MusicalScore::getStaff(const std::string& name) {
    return staves.getStaff(name);
}

const MusicalStaff& MusicalScore::getStaff(const std::string& name) const {
    return staves.getStaff(name);
}

MusicalStaves& MusicalScore::getStaves() {
    return staves;
}

const MusicalStaves& MusicalScore::getStaves() const {
    return staves;
}

void MusicalScore::renderStaff(const MusicalStaff& staff, const int samples_per_second, AudioTrack& track) const {
    staff.render(timeSignature, tempo, samples_per_second, track);
}

void MusicalScore::renderStaves(const int samples_per_second, std::map<std::string, AudioTrack>& tracks) const {
    for (auto it = staves.begin(); it != staves.end(); ++it) {
        AudioTrack track;
        it->second.render(timeSignature, tempo, samples_per_second, track);
        tracks[it->first] = track;
    }
}

void MusicalScore::renderWavChannels(const int samples_per_second, std::vector<AudioTrack>& channels) const {
    std::map<std::string, AudioTrack> tracks;
    renderStaves(samples_per_second, tracks);

    for (auto it = tracks.begin(); it != tracks.end(); ++it) {
        channels.push_back(it->second);
    }
}