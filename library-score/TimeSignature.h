#ifndef TIME_SIGNATURE_H
#define TIME_SIGNATURE_H

class TimeSignature {
protected:
    int beatsPerBar;
    int beatValue;

public:
    TimeSignature(); 
    TimeSignature(const int beats_per_bar, const int beat_value);

    int getBeatsPerBar() const;
    int getBeatValue() const;

    void setBeatsPerBar(const int beats_per_bar);
    void setBeatValue(const int beat_value);
};

#endif // TIME_SIGNATURE_H
