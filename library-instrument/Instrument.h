#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <string>
#include <memory>
#include "Waveform.h"   
#include "Envelope.h"   
#include "AudioTrack.h" 

class Instrument {
protected:
    std::string name;                          
    std::shared_ptr<Waveform> waveform;        
    std::shared_ptr<Envelope> envelope;        

public:
    // Constructors
    Instrument();

    Instrument(const std::string& name, std::shared_ptr<Waveform> waveform, std::shared_ptr<Envelope> envelope);

    // Virtual destructor
    virtual ~Instrument();

    // Getter 
    const std::string& getName() const;

    std::shared_ptr<Waveform> getWaveform() const;

    std::shared_ptr<Envelope> getEnvelope() const;

    // Setter
    void setName(const std::string& name);

    void setWaveform(std::shared_ptr<Waveform> waveform);

    void setEnvelope(std::shared_ptr<Envelope> envelope);

    // Method to generate samples for the audio track
    void generateSamples(const double frequency, const double seconds, const int samples_per_second, AudioTrack& track) const;
};

#endif // INSTRUMENT_H
