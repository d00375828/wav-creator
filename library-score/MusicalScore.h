#ifndef MUSICAL_SCORE_H
#define MUSICAL_SCORE_H

#include "Waveforms.h"
#include "Envelopes.h"
#include "Instrumentarium.h"
#include "TimeSignature.h"
#include "MusicalStaves.h"
#include "AudioTrack.h"

class MusicalScore {
private:
    Waveforms waveforms;
    Envelopes envelopes;
    Instrumentarium instruments; 
    TimeSignature timeSignature;
    double tempo;
    MusicalStaves staves;

public:
    MusicalScore();
    MusicalScore(const TimeSignature& time_signature, const double tempo);

    Waveforms& getWaveforms();
    const Waveforms& getWaveforms() const;

    Envelopes& getEnvelopes();             
    const Envelopes& getEnvelopes() const;

    Instrumentarium& getInstrumentarium();             
    const Instrumentarium& getInstrumentarium() const; 

    TimeSignature& getTimeSignature();
    const TimeSignature& getTimeSignature() const;

    double getTempo() const;
    void setTempo(const double tempo);

    void addStaff(const MusicalStaff& staff);
    MusicalStaff& getStaff(const std::string& name);
    const MusicalStaff& getStaff(const std::string& name) const;

    MusicalStaves& getStaves();
    const MusicalStaves& getStaves() const;

    void renderStaff(const MusicalStaff& staff, const int samples_per_second, AudioTrack& track) const;
    void renderStaves(const int samples_per_second, std::map<std::string, AudioTrack>& tracks) const;
    void renderWavChannels(const int samples_per_second, std::vector<AudioTrack>& channels) const;
};

#endif // MUSICAL_SCORE_H
