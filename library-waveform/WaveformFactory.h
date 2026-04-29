#ifndef WAVEFORM_FACTORY_H
#define WAVEFORM_FACTORY_H

#include "Waveform.h"
#include "SineWaveform.h"
#include "SquareWaveform.h"
#include "SawtoothWaveform.h"
#include "TriangleWaveform.h"
#include <memory>
#include <vector>
#include <string>

class WaveformFactory {
public:
    enum WaveformId { WF_SINE, WF_SQUARE, WF_SAWTOOTH, WF_TRIANGLE, WF_ERROR };

    const static std::vector<std::string> WaveformName;

    static std::unique_ptr<Waveform> create(WaveformId id, const std::string& name);
    static std::unique_ptr<Waveform> create(const std::string& id, const std::string& name);
    static WaveformId stringToWaveformId(const std::string& id);
    static bool validStringId(const std::string& id);
    
    virtual ~WaveformFactory() = default;
};

#endif // WAVEFORM_FACTORY_H
