#ifndef ENVELOPE_TEST_AUX_H
#define ENVELOPE_TEST_AUX_H

#include "ApplicationData.h"

// Fills the AudioTrack with an envelope based on user input
void fill_audio_track_with_envelope(ApplicationData& app_data);

// Runs the envelope test, configuring the audio track and filling it with envelope data
int envelope_test(ApplicationData& app_data);

#endif // ENVELOPE_TEST_AUX_H
