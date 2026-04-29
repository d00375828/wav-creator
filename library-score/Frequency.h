#ifndef FREQUENCY_H
#define FREQUENCY_H

#include <string>
#include <map>

class Frequency {
protected:
    static double trt;
    static std::map<std::string, double> smFrequencies;

    static double computeFactor(const unsigned int& octaves, const unsigned int& keys);
    static double moveLeft(const double& frequency, const unsigned int& octaves, const unsigned int& keys);
    static double moveRight(const double& frequency, const unsigned int& octaves, const unsigned int& keys);
    static std::map<std::string, double> generateFrequencies();

public:
    static double getFrequency(const std::string& note);
};

#endif // FREQUENCY_H
