#include "Frequency.h"
#include <cmath>
#include <vector>

double Frequency::trt = std::pow(2.0, 1.0 / 12.0);
std::map<std::string, double> Frequency::smFrequencies = Frequency::generateFrequencies();

double Frequency::computeFactor(const unsigned int& octaves, const unsigned int& keys) {
    return std::pow(2.0, octaves) * std::pow(trt, keys);
}

double Frequency::moveLeft(const double& frequency, const unsigned int& octaves, const unsigned int& keys) {
    return frequency / computeFactor(octaves, keys);
}

double Frequency::moveRight(const double& frequency, const unsigned int& octaves, const unsigned int& keys) {
    return frequency * computeFactor(octaves, keys);
}

std::map<std::string, double> Frequency::generateFrequencies() {
    std::map<std::string, double> freq_map;

    const double A4 = 440.0;

    std::vector<std::string> note_names = {
        "C", "C#", "Db", "D", "D#", "Eb", "E",
        "F", "F#", "Gb", "G", "G#", "Ab",
        "A", "A#", "Bb", "B"
    };

    std::vector<std::pair<std::string, int>> key_to_semitone = {
        {"C", 0}, {"C#", 1}, {"Db", 1}, {"D", 2}, {"D#", 3}, {"Eb", 3},
        {"E", 4}, {"F", 5}, {"F#", 6}, {"Gb", 6}, {"G", 7}, {"G#", 8}, {"Ab", 8},
        {"A", 9}, {"A#", 10}, {"Bb", 10}, {"B", 11}
    };

    double C0 = moveLeft(A4, 4, 9);

    for (int octave = 0; octave <= 9; ++octave) {
        for (const auto& pair : key_to_semitone) {
            const std::string& note = pair.first;
            int key = pair.second;
            double freq = moveRight(C0, octave, key);
            freq_map[note + std::to_string(octave)] = freq;
        }
    }

    return freq_map;
}

double Frequency::getFrequency(const std::string& note) {
    if (smFrequencies.find(note) != smFrequencies.end()) {
        return smFrequencies[note];
    }
    return 0.0;
}
