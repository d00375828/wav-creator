#ifndef AUDIO_TRACK_H
#define AUDIO_TRACK_H

#include <vector>
#include <cmath>

class AudioTrack {
protected:
    int samplesPerSecond;          
    double seconds;                
    std::vector<double> values;    


    void resizeValues();

public:
    // Default constructor initializes data members to zero
    AudioTrack();

    // Getter 
    int getSamplesPerSecond() const;
    double getSeconds() const;
    unsigned int getSize() const;
    double getValue(const unsigned int index) const;


    // Setter 
    void setSamplesPerSecond(const int samplesPerSecond);
    void setSeconds(const double seconds);
    void setSize(const int samplesPerSecond, const double seconds);
    void setValue(const unsigned int index, const double value);


    bool indexValid(const unsigned int index) const;
    
    void addAt(const AudioTrack& other_track, double offset_seconds);


    AudioTrack operator*(const AudioTrack& rhs) const;
};

#endif // AUDIO_TRACK_H
