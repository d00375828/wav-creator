#include "Envelope.h"

Envelope::Envelope(const std::string& name, const std::string& type_name)
    : name(name), type_name(type_name), maximum_amplitude(1.0) {}

Envelope::Envelope(const std::string& name, const std::string& type_name, const double amplitude)
    : name(name), type_name(type_name), maximum_amplitude(amplitude) {}

Envelope::~Envelope() {}

const std::string& Envelope::getName() const {
    return name;
}

const std::string& Envelope::getTypeName() const {
    return type_name;
}

double Envelope::getMaximumAmplitude() const {
    return maximum_amplitude;
}

void Envelope::setName(const std::string& new_name) {
    name = new_name;
}

void Envelope::setTypeName(const std::string& new_type_name) {
    type_name = new_type_name;
}

void Envelope::setMaximumAmplitude(const double amplitude) {
    if (amplitude > 0.0) {
        maximum_amplitude = amplitude;
    }
}
