#include "WaveformFactory.h"

const std::vector<std::string> WaveformFactory::WaveformName = {"sine", "square", "sawtooth", "triangle", "error"};

std::unique_ptr<Waveform> WaveformFactory::create(WaveformId id, const std::string& name) {
    switch (id) {
        case WF_SINE:
            return std::make_unique<SineWaveform>(name);
        case WF_SQUARE:
            return std::make_unique<SquareWaveform>(name);
        case WF_SAWTOOTH:
            return std::make_unique<SawtoothWaveform>(name);
        case WF_TRIANGLE:
            return std::make_unique<TriangleWaveform>(name);
        default:
            return nullptr;
    }
}

std::unique_ptr<Waveform> WaveformFactory::create(const std::string& id, const std::string& name) {
    return create(stringToWaveformId(id), name);
}

WaveformFactory::WaveformId WaveformFactory::stringToWaveformId(const std::string& id) {
    for (size_t i = 0; i < WaveformName.size(); ++i) {
        if (WaveformName[i] == id) {
            return static_cast<WaveformId>(i);
        }
    }
    return WF_ERROR;
}

bool WaveformFactory::validStringId(const std::string& id) {
    return stringToWaveformId(id) != WF_ERROR;
}
