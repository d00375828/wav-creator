#ifndef SCORE_EDITOR_AUX_H
#define SCORE_EDITOR_AUX_H

#include "ApplicationData.h"

// Waveforms
void listScoreWaveformsUI(ApplicationData& app);
void addScoreWaveformUI(ApplicationData& app);
void editScoreWaveformUI(ApplicationData& app);

// Envelopes
void readScoreUI(ApplicationData& app);
void listScoreEnvelopesUI(ApplicationData& app);
void addScoreEnvelopeUI(ApplicationData& app);
void editScoreEnvelopeUI(ApplicationData& app);

// Instruments
void listScoreInstrumentsUI(ApplicationData& app);
void addScoreInstrumentUI(ApplicationData& app);
void editScoreInstrumentUI(ApplicationData& app);

// File output
void writeScoreUI(ApplicationData& app);

// Registration
int register_score_editor_commands(ApplicationData& app_data);
int score_editor(ApplicationData& app_data);

// Time Signature
void setScoreTimeSignatureUI(ApplicationData& app);
void setScoreTempoUI(ApplicationData& app);

// Staffs
void setStaffInstrumentUI(ApplicationData& app);
void listScoreStavesUI(ApplicationData& app);
void addStaffUI(ApplicationData& app);
void showStaffUI(ApplicationData& app);
void addStaffNoteUI(ApplicationData& app);
void renderScoreUI(ApplicationData& app);

// Test
void buildScoreInstrumentFromWaveformAndEnvelopePair(ApplicationData& app, std::shared_ptr<Waveform> w, std::shared_ptr<Envelope> e);
void buildScoreAllPossibleInstrumentsUI(ApplicationData& app);

void addStaffNoteRunUI(ApplicationData& app);
void removeStaffUI(ApplicationData& app);

#endif // SCORE_EDITOR_AUX_H