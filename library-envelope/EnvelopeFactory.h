#ifndef ENVELOPE_FACTORY_H
#define ENVELOPE_FACTORY_H

#include <memory>
#include <vector>
#include <string>
#include "Envelope.h"
#include "ADEnvelope.h"
#include "ADSREnvelope.h"

class EnvelopeFactory {
public:
    enum EnvelopeId {
        EN_AD,
        EN_ADSR,
        EN_ERROR
    };

    const static std::vector<std::string> EnvelopeName;

    static std::unique_ptr<Envelope> create(EnvelopeId id, const std::string& name);
    static std::unique_ptr<Envelope> create(const std::string& id, const std::string& name);
    static EnvelopeId stringToEnvelopeId(const std::string& id);
    static bool validStringId(const std::string& id);
    virtual ~EnvelopeFactory() = default;
};

#endif // ENVELOPE_FACTORY_H