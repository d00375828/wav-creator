#include "WavWriter.h"

WavWriter::WavWriter() {}

WavWriter::~WavWriter() {}

void WavWriter::writeWavFromScore(const MusicalScore& score,
                                  const int samples_per_second,
                                  const int bits_per_sample,
                                  const std::string& wav_filename) const {
    std::vector<AudioTrack> channels;
    score.renderWavChannels(samples_per_second, channels);

    WAVFile wav(samples_per_second, bits_per_sample);
    wav.writeFile(wav_filename, channels);
}
