#include "score_editor_aux.h"
#include "ActionFunctionData.h"
#include "WaveformFactory.h"
#include "menu_test_aux.h"
#include "EnvelopeFactory.h"
#include "ScoreReader.h"
#include "ADEnvelope.h"
#include "ADSREnvelope.h"
#include "Instrument.h"
#include "ScoreWriter.h"
#include "WavWriter.h"

#include <iostream>
#include <iomanip>
#include <fstream>

void listScoreWaveformsUI(ApplicationData& app) {
    const Waveforms& waveforms = app.getScore().getWaveforms();

    for (auto it = waveforms.begin(); it != waveforms.end(); ++it) {
        std::shared_ptr<Waveform> wf = it->second;
        app.getOutputStream() << it->first << " : "
                              << wf->getName() << " "
                              << wf->getTypeName() << " "
                              << wf->getAmplitude() << "\n";
    }
}

void addScoreWaveformUI(ApplicationData& app) {
    app.getOutputStream() << "Waveform name: ";
    std::string name = app.getString("");

    app.getOutputStream() << "Waveform type: ";
    std::string type = app.getString("");

    std::shared_ptr<Waveform> waveform;
    try {
        waveform = WaveformFactory::create(type, name);
    } catch (std::invalid_argument& e) {
        app.getOutputStream() << "Unable to create a waveform of type '" << type << "'.\n";
        return;
    }

    if (!waveform) {
        app.getOutputStream() << "Unable to create a waveform of type '" << type << "'.\n";
        return;
    }

    app.getOutputStream() << "Amplitude: ";
    double amplitude = app.getDouble("");

    waveform->setAmplitude(amplitude);
    app.getScore().getWaveforms().addWaveform(name, waveform);
}

void editScoreWaveformUI(ApplicationData& app) {
    app.getOutputStream() << "Waveform name: ";
    std::string name = app.getString("");

    std::shared_ptr<Waveform> waveform = app.getScore().getWaveforms().getWaveform(name);
    if (!waveform) {
        app.getOutputStream() << "Unable to find a waveform with name '" << name << "'.\n";
        return;
    }

    app.getOutputStream() << "Amplitude(" << waveform->getAmplitude() << "): ";
    double new_amplitude = app.getDouble("");
    waveform->setAmplitude(new_amplitude);
}

int register_score_editor_commands(ApplicationData& app_data) {
    register_menu_test_commands(app_data);

    app_data.addAction(ActionFunctionData("score-list-waveforms", &listScoreWaveformsUI, "List waveforms in the score.", 1));
    app_data.addAction(ActionFunctionData("score-add-waveform", &addScoreWaveformUI, "Add waveform to the score.", 1));
    app_data.addAction(ActionFunctionData("score-edit-waveform", &editScoreWaveformUI, "Edit waveform in the score.", 1));

    app_data.addAction(ActionFunctionData("score-read", &readScoreUI, "Read score from file.", 1));
    app_data.addAction(ActionFunctionData("score-list-envelopes", &listScoreEnvelopesUI, "List envelopes in the score.", 1));
    app_data.addAction(ActionFunctionData("score-add-envelope", &addScoreEnvelopeUI, "Add envelope to the score.", 1));
    app_data.addAction(ActionFunctionData("score-edit-envelope", &editScoreEnvelopeUI, "Edit envelope in the score.", 1));

    app_data.addAction(ActionFunctionData("score-write", &writeScoreUI, "Write score to score file.", 1));
    app_data.addAction(ActionFunctionData("score-list-instruments", &listScoreInstrumentsUI, "List instruments in the score.", 1));
    app_data.addAction(ActionFunctionData("score-add-instrument", &addScoreInstrumentUI, "Add instrument to the score.", 1));
    app_data.addAction(ActionFunctionData("score-edit-instrument", &editScoreInstrumentUI, "Edit instrument in the score.", 1));

    app_data.addAction(ActionFunctionData("score-set-time-signature", &setScoreTimeSignatureUI, "Edit the time signature of a score.", 1));
    app_data.addAction(ActionFunctionData("score-set-tempo", &setScoreTempoUI, "Edit the tempo of a score.", 1));

    app_data.addAction(ActionFunctionData("score-staff-set-instrument", &setStaffInstrumentUI, "Change instrument assigned to a staff in the score.", 1));
    app_data.addAction(ActionFunctionData("score-list-staves", &listScoreStavesUI, "List staves in the score.", 1));
    app_data.addAction(ActionFunctionData("score-add-staff", &addStaffUI, "Add a staff to the score.", 1));
    app_data.addAction(ActionFunctionData("score-show-staff", &showStaffUI, "Display staff details.", 1));
    app_data.addAction(ActionFunctionData("score-staff-add-note", &addStaffNoteUI, "Add a note to a staff.", 1));
    app_data.addAction(ActionFunctionData("score-render", &renderScoreUI, "Render score to wav file.", 1));

    app_data.addAction(ActionFunctionData("score-build-all-instruments", &buildScoreAllPossibleInstrumentsUI, "Build an instrument for each waveform/envelope pair in the score.", 1));
    app_data.addAction(ActionFunctionData("score-staff-add-note-run", &addStaffNoteRunUI, "Add a run of notes to a staff.", 1));
    app_data.addAction(ActionFunctionData("score-remove-staff", &removeStaffUI, "Remove a staff from the score.", 1));
    

    return 0;
}

int score_editor(ApplicationData& app_data) {
    register_score_editor_commands(app_data);
    app_data.mainLoop();
    return 0;
}

void readScoreUI(ApplicationData& app_data) {
    std::string filename;
    app_data.getOutputStream() << "Score filename: ";
    filename = app_data.getString("");
    
    std::ifstream input_file(filename);
    if (!input_file) {
        app_data.getOutputStream() << "Could not open file: " << filename << std::endl;
        return;
    }
    
    ScoreReader reader;
    reader.readScore(input_file, app_data.getScore());
}

void listScoreEnvelopesUI(ApplicationData& app_data) {
    const auto& envelopes = app_data.getScore().getEnvelopes();
    for (auto it = envelopes.begin(); it != envelopes.end(); ++it) {
        const auto& envelope = it->second;
        app_data.getOutputStream() << it->first << " : "
                                << envelope->getName() << " "
                                << envelope->getTypeName() << " "
                                << envelope->getMaximumAmplitude() << std::endl;
    }
}

void addScoreEnvelopeUI(ApplicationData& app_data) {
    std::ostream& out = app_data.getOutputStream();
    
    out << "Envelope name: ";
    std::string name = app_data.getString("");
    
    out << "Envelope type: ";
    std::string type = app_data.getString("");
    
    std::shared_ptr<Envelope> envelope;
    try {
        envelope = EnvelopeFactory::create(type, name);
    } catch (std::invalid_argument& e) {
        out << "Unable to create an envelope of type '" << type << "'." << std::endl;
        return;
    }

    if (!envelope) {
        out << "Unable to create an envelope of type '" << type << "'." << std::endl;
        return;
    }

    out << "Maximum amplitude: ";
    double max_amp = app_data.getDouble("");
    envelope->setMaximumAmplitude(max_amp);

    if (auto ad = std::dynamic_pointer_cast<ADEnvelope>(envelope)) {
        out << "Attack seconds: ";
        double attack = app_data.getDouble("");
        ad->setAttackSeconds(attack);
    } else if (auto adsr = std::dynamic_pointer_cast<ADSREnvelope>(envelope)) {
        out << "Attack seconds: ";
        double attack = app_data.getDouble("");
        
        out << "Decay seconds: ";
        double decay = app_data.getDouble("");
        
        out << "Sustain amplitude: ";
        double sustain = app_data.getDouble("");
        
        out << "Release seconds: ";
        double release = app_data.getDouble("");
        
        adsr->setAttackSeconds(attack);
        adsr->setDecaySeconds(decay);
        adsr->setSustainAmplitude(sustain);
        adsr->setReleaseSeconds(release);
    } else {
        out << "Unknown envelope type '" << type <<"'. Cannot configure parameters." << std::endl;
        return;
    }

    app_data.getScore().getEnvelopes().addEnvelope(name, envelope);
}

void editScoreEnvelopeUI(ApplicationData& app_data) {
    std::ostream& out = app_data.getOutputStream();
    
    out << "Envelope name: ";
    std::string name = app_data.getString("");

    std::shared_ptr<Envelope> envelope = app_data.getScore().getEnvelopes().getEnvelope(name);
    if (!envelope) {
        out << "Unable to find an envelope with name '" << name << "'." << std::endl;
        return;
    }

    double max_amp;
    out << "Maximum amplitude(" << envelope->getMaximumAmplitude() << "): ";
    max_amp = app_data.getDouble("");
    envelope->setMaximumAmplitude(max_amp);

    if (auto ad = std::dynamic_pointer_cast<ADEnvelope>(envelope)) {
        double attack;
        out << "Attack seconds(" << ad->getAttackSeconds() << "): ";
        attack = app_data.getDouble("");
        ad->setAttackSeconds(attack);
    } else if (auto adsr = std::dynamic_pointer_cast<ADSREnvelope>(envelope)) {
        double attack, decay, sustain, release;
        out << "Attack seconds(" << adsr->getAttackSeconds() << "): ";
        attack = app_data.getDouble("");
        out << "Decay seconds(" << adsr->getDecaySeconds() << "): ";
        decay = app_data.getDouble("");
        out << "Sustain amplitude(" << adsr->getSustainAmplitude() << "): ";
        sustain = app_data.getDouble("");
        out << "Release seconds(" << adsr->getReleaseSeconds() << "): ";
        release = app_data.getDouble("");
        adsr->setAttackSeconds(attack);
        adsr->setDecaySeconds(decay);
        adsr->setSustainAmplitude(sustain);
        adsr->setReleaseSeconds(release);
    }
}

void writeScoreUI(ApplicationData& app) {
    std::string filename;
    app.getOutputStream() << "Filename: ";
    filename = app.getString("");
    
    std::ofstream output_file(filename);
    if (!output_file) {
        app.getOutputStream() << "Could not open file: " << filename << std::endl;
        return;
    }
    
    ScoreWriter writer;
    writer.writeScore(output_file, app.getScore());
}

void listScoreInstrumentsUI(ApplicationData& app) {
    const auto& instruments = app.getScore().getInstrumentarium();
    for (auto it = instruments.begin(); it != instruments.end(); ++it) {
        const std::string& key = it->first;
        const std::shared_ptr<Instrument>& instrument = it->second;

        app.getOutputStream() << key << " : " << instrument->getName() << " : ";

        if (instrument->getWaveform()) {
            app.getOutputStream() << instrument->getWaveform()->getName() << " ";
        } else {
            app.getOutputStream() << "(no waveform) ";
        }

        if (instrument->getEnvelope()) {
            app.getOutputStream() << instrument->getEnvelope()->getName();
        } else {
            app.getOutputStream() << "(no envelope)";
        }

        app.getOutputStream() << "\n";
    }
}


void addScoreInstrumentUI(ApplicationData& app) {
    std::ostream& out = app.getOutputStream();
    std::string name, waveform_name, envelope_name;
    
    out << "Instrument name: ";
    name = app.getString("");
    
    out << "Waveform name: ";
    waveform_name = app.getString("");
    
    std::shared_ptr<Waveform> waveform = app.getScore().getWaveforms().getWaveform(waveform_name);
    if (!waveform) {
        out << "Unable to find a waveform with name '" << waveform_name << "'." << std::endl;
        return;
    }
    
    out << "Envelope name: ";
    envelope_name = app.getString("");
    
    std::shared_ptr<Envelope> envelope = app.getScore().getEnvelopes().getEnvelope(envelope_name);
    if (!envelope) {
        out << "Unable to find an envelope with name '" << envelope_name << "'." << std::endl;
        return;
    }
    
    std::shared_ptr<Instrument> instrument = std::make_shared<Instrument>(name, waveform, envelope);
    app.getScore().getInstrumentarium().addInstrument(name, instrument);
}

void editScoreInstrumentUI(ApplicationData& app) {
    std::ostream& out = app.getOutputStream();
    std::string name, waveform_name, envelope_name;
    
    out << "Instrument name: ";
    name = app.getString("");
    
    std::shared_ptr<Instrument> instrument = app.getScore().getInstrumentarium().getInstrument(name);
    if (!instrument) {
        out << "Unable to find an instrument with name '" << name << "'." << std::endl;
        return;
    }
    
    std::string current_waveform = "(none)";
    if (instrument->getWaveform()) {
        current_waveform = instrument->getWaveform()->getName();
    }
    
    out << "Waveform name: ";
    waveform_name = app.getString("");
    
    std::shared_ptr<Waveform> waveform = app.getScore().getWaveforms().getWaveform(waveform_name);
    if (!waveform) {
        out << "Unable to find a waveform with name '" << waveform_name << "'." << std::endl;
        return;
    }
    
    std::string current_envelope = "(none)";
    if (instrument->getEnvelope()) {
        current_envelope = instrument->getEnvelope()->getName();
    }
    
    out << "Envelope name: ";
    envelope_name = app.getString("");
    
    std::shared_ptr<Envelope> envelope = app.getScore().getEnvelopes().getEnvelope(envelope_name);
    if (!envelope) {
        out << "Unable to find an envelope with name '" << envelope_name << "'." << std::endl;
        return;
    }
    
    instrument->setWaveform(waveform);
    instrument->setEnvelope(envelope);
}

void setScoreTimeSignatureUI(ApplicationData& app) {
    std::ostream& out = app.getOutputStream();

    out << "Beats per bar: ";
    int beats = app.getInteger("");

    out << "Beat value: ";
    int value = app.getInteger("");

    app.getScore().getTimeSignature().setBeatsPerBar(beats);
    app.getScore().getTimeSignature().setBeatValue(value);
}

void setScoreTempoUI(ApplicationData& app) {
    std::ostream& out = app.getOutputStream();

    out << "Beats per minute: ";
    double tempo = app.getDouble("");

    app.getScore().setTempo(tempo);
}

void setStaffInstrumentUI(ApplicationData& app) {
    std::ostream& out = app.getOutputStream();

    out << "Staff name: ";
    std::string staff_name = app.getString("");

    out << "Instrument name: ";
    std::string instrument_name = app.getString("");

    std::shared_ptr<Instrument> instr = app.getScore().getInstrumentarium().getInstrument(instrument_name);
    if (!instr) {
        out << "Unknown instrument: " << instrument_name << "\n";
        return;
    }

    app.getScore().getStaff(staff_name).setInstrument(instr);
}

void listScoreStavesUI(ApplicationData& app) {
    for (const auto& [name, staff] : app.getScore().getStaves()) {
        app.getOutputStream() << staff.toString() << "\n";
    }
}

void addStaffUI(ApplicationData& app) {
    std::ostream& out = app.getOutputStream();

    out << "Staff name: ";
    std::string name = app.getString("");

    out << "Instrument name: ";
    std::string instrument_name = app.getString("");

    std::shared_ptr<Instrument> instr = app.getScore().getInstrumentarium().getInstrument(instrument_name);
    if (!instr) {
        out << "Unknown instrument: " << instrument_name << "\n";
        return;
    }

    MusicalStaff staff(name, instr);
    app.getScore().addStaff(staff);
}

void showStaffUI(ApplicationData& app) {
    std::ostream& out = app.getOutputStream();

    out << "Staff name: ";
    std::string name = app.getString("");

    const MusicalStaff& staff = app.getScore().getStaff(name);
    out << staff.toString() << "\n";

    for (const StaffNote& note : staff.getNotes()) {
        out << note.getStart() << " "
            << note.getNote().getDuration() << " "
            << note.getNote().getName() << "\n";
    }

    out << "\n"; 
}


void addStaffNoteUI(ApplicationData& app) {
    std::ostream& out = app.getOutputStream();

    out << "Staff name: ";
    std::string staff_name = app.getString("");

    out << "Start: ";
    double start = app.getDouble("");

    out << "Duration: ";
    std::string duration_str = app.getString("");

    out << "Note: ";
    std::string note_name = app.getString("");

    Note note(note_name, duration_str);
    StaffNote staff_note(note, start);
    app.getScore().getStaff(staff_name).addNote(staff_note);
}



void renderScoreUI(ApplicationData& app) {
    std::ostream& out = app.getOutputStream();

    out << "Filename: ";
    std::string filename = app.getString("");

    out << "Samples per second: ";
    int samples_per_second = app.getInteger("");

    out << "Bits per sample: ";
    int bits_per_sample = app.getInteger("");

    WavWriter writer;
    writer.writeWavFromScore(app.getScore(), samples_per_second, bits_per_sample, filename);
}

// Test 
void buildScoreInstrumentFromWaveformAndEnvelopePair(ApplicationData& app, std::shared_ptr<Waveform> w, std::shared_ptr<Envelope> e) {
    std::string name = w->getName() + "/" + e->getName();
    std::shared_ptr<Instrument> instrument = std::make_shared<Instrument>(name, w, e);
    app.getScore().getInstrumentarium().addInstrument(name, instrument);
}

void buildScoreAllPossibleInstrumentsUI(ApplicationData& app) {
    const Waveforms& waveforms = app.getScore().getWaveforms();
    const Envelopes& envelopes = app.getScore().getEnvelopes();

    for (auto wf_it = waveforms.begin(); wf_it != waveforms.end(); ++wf_it) {
        for (auto env_it = envelopes.begin(); env_it != envelopes.end(); ++env_it) {
            buildScoreInstrumentFromWaveformAndEnvelopePair(app, wf_it->second, env_it->second);
        }
    }
}

void addStaffNoteRunUI(ApplicationData& app) {
    std::ostream& out = app.getOutputStream();

    out << "Staff name: ";
    std::string staff_name = app.getString("");

    out << "Start: ";
    double start_time = app.getDouble("");

    out << "Duration: ";
    std::string duration_str = app.getString("");

    out << "First note: ";
    std::string first_note = app.getString("");

    MusicalScore& score = app.getScore();
    

    MusicalStaff& staff = score.getStaff(staff_name);

    Note base(first_note, duration_str);
    Note second(base.relativeNoteNameFlat(4), duration_str);
    Note third(base.relativeNoteNameFlat(7), duration_str);

    double d = base.getDuration(); 

    staff.addNote(StaffNote(base, start_time));
    staff.addNote(StaffNote(second, start_time + d));
    staff.addNote(StaffNote(third, start_time + 2 * d));
}

void removeStaffUI(ApplicationData& app) {
    std::ostream& out = app.getOutputStream();

    out << "Staff name: ";
    std::string name = app.getString("");

    MusicalStaves& staves = app.getScore().getStaves();

    bool exists = false;
    for (const auto& pair : staves) {
        if (pair.second.getName() == name) {
            exists = true;
            break;
        }
    }

    if (!exists) {
        out << name << " does not name a staff in this application." << std::endl;
        return;
    }

    staves.removeStaff(name);
}

