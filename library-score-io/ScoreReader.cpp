#include "ScoreReader.h"
#include "WaveformFactory.h"
#include "EnvelopeFactory.h"
#include "Instrumentarium.h"

#include <iostream>
#include <stdexcept>
#include <sstream>

ScoreReader::ScoreReader() {}
ScoreReader::~ScoreReader() {}

void ScoreReader::readScore(std::istream& input_stream, MusicalScore& score) const {
    std::string word;

    input_stream >> word;
    if (word != "SCORE") return;

    while (input_stream >> word) {
        if (word == "SCORE-END") {
            return;
        } else if (word == "WAVEFORM") {
            readWaveform(input_stream, score);
        } else if (word == "ENVELOPE") {
            readEnvelope(input_stream, score);
        } else if (word == "INSTRUMENT") {
            readInstrument(input_stream, score);
        } else if (word == "TIME-SIGNATURE") {
            int beats_per_bar, beat_value;
            input_stream >> beats_per_bar >> beat_value;
            score.getTimeSignature().setBeatsPerBar(beats_per_bar);
            score.getTimeSignature().setBeatValue(beat_value);
        } else if (word == "TEMPO") {
            double tempo;
            input_stream >> tempo;
            score.setTempo(tempo);
        } else if (word == "STAFF") {
            MusicalStaff staff;
            readStaff(input_stream, score, staff);
            score.addStaff(staff);
        }

    }
}

std::shared_ptr<Waveform> ScoreReader::readWaveform(std::istream& input_stream, MusicalScore& score) const {
    std::string waveform_name, waveform_type;
    if (!(input_stream >> waveform_name >> waveform_type)) return nullptr;

    Waveforms& waveforms = score.getWaveforms();
    std::shared_ptr<Waveform> waveform_ptr = waveforms.getWaveform(waveform_name);

    if (waveform_ptr) {
        std::string line;
        while (std::getline(input_stream, line)) {
            std::istringstream line_stream(line);
            std::string keyword;
            line_stream >> keyword;
            
            if (keyword == "WAVEFORM-END") {
                return waveform_ptr;
            }
        }
        return nullptr; 
    }

    std::unique_ptr<Waveform> new_waveform = WaveformFactory::create(waveform_type, waveform_name);
    if (!new_waveform) return nullptr;
    waveform_ptr = std::move(new_waveform);
    waveforms.addWaveform(waveform_name, waveform_ptr);

    std::string line;
    while (std::getline(input_stream, line)) {
        std::istringstream line_stream(line);
        std::string keyword;
        line_stream >> keyword;

        if (keyword == "WAVEFORM-END") {
            return waveform_ptr;
        } else if (keyword == "AMPLITUDE") {
            double amp;
            if (!(line_stream >> amp)) return nullptr;
            waveform_ptr->setAmplitude(amp);
        } else if (!keyword.empty()) {
            return nullptr; 
        }
    }

    return nullptr;
}

std::shared_ptr<Envelope> ScoreReader::readEnvelope(std::istream& input_stream, MusicalScore& score) const {
    std::string envelope_name, envelope_type;
    if (!(input_stream >> envelope_name >> envelope_type)) return nullptr;

    Envelopes& envelopes = score.getEnvelopes();
    std::shared_ptr<Envelope> envelope_ptr = envelopes.getEnvelope(envelope_name);

    if (envelope_ptr) {
        std::string line;
        while (std::getline(input_stream, line)) {
            std::istringstream line_stream(line);
            std::string keyword;
            line_stream >> keyword;
            
            if (keyword == "ENVELOPE-END") {
                return envelope_ptr;
            }
        }
        return nullptr; 
    }

    std::unique_ptr<Envelope> new_envelope = EnvelopeFactory::create(envelope_type, envelope_name);
    if (!new_envelope) return nullptr;
    envelope_ptr = std::move(new_envelope);
    envelopes.addEnvelope(envelope_name, envelope_ptr);

    std::string line;
    
    while (std::getline(input_stream, line)) {
        std::istringstream line_stream(line);
        std::string keyword;
        line_stream >> keyword;

        if (keyword == "ENVELOPE-END") {
            return envelope_ptr;
        } else if (keyword == "MAXIMUM-AMPLITUDE") {
            double amp;
            if (!(line_stream >> amp)) return nullptr;
            envelope_ptr->setMaximumAmplitude(amp);
        } else if (keyword == "ATTACK-SECONDS") {
            double a;
            if (!(line_stream >> a)) return nullptr;
            if (auto adsr = dynamic_cast<ADSREnvelope*>(envelope_ptr.get())) {
                adsr->setAttackSeconds(a);
            } else if (auto ad = dynamic_cast<ADEnvelope*>(envelope_ptr.get())) {
                ad->setAttackSeconds(a);
            }
        } else if (keyword == "DECAY-SECONDS") {
            double d;
            if (!(line_stream >> d)) return nullptr;
            if (auto adsr = dynamic_cast<ADSREnvelope*>(envelope_ptr.get())) {
                adsr->setDecaySeconds(d);
            } else if (auto ad = dynamic_cast<ADEnvelope*>(envelope_ptr.get())) {
                ad->setDecaySeconds(d);
            }
        } else if (keyword == "SUSTAIN-AMPLITUDE") {
            double s;
            if (!(line_stream >> s)) return nullptr;
            if (auto adsr = dynamic_cast<ADSREnvelope*>(envelope_ptr.get())) {
                adsr->setSustainAmplitude(s);
            }
        } else if (keyword == "RELEASE-SECONDS") {
            double r;
            if (!(line_stream >> r)) return nullptr;
            if (auto adsr = dynamic_cast<ADSREnvelope*>(envelope_ptr.get())) {
                adsr->setReleaseSeconds(r);
            }
        } else if (!keyword.empty()) {
            return nullptr; 
        }
    }

    return nullptr;
}

std::shared_ptr<Instrument> ScoreReader::readInstrument(std::istream& is, MusicalScore& score) const {
    std::string name;
    if (!(is >> name)) return nullptr;

    Instrumentarium& instruments = score.getInstrumentarium();
    
    std::shared_ptr<Instrument> existing_instrument = instruments.getInstrument(name);
    if (existing_instrument) {
        std::string line;
        while (std::getline(is, line)) {
            std::istringstream linestream(line);
            std::string keyword;
            linestream >> keyword;
            
            if (keyword.empty()) continue;
            if (keyword == "INSTRUMENT-END") {
                return existing_instrument;
            }
        }
        return nullptr;
    }
    
    std::shared_ptr<Waveform> waveform_ptr = nullptr;
    std::shared_ptr<Envelope> envelope_ptr = nullptr;

    std::string line;
    while (std::getline(is, line)) {
        std::istringstream linestream(line);
        std::string keyword;
        linestream >> keyword;

        if (keyword.empty()) continue;

        if (keyword == "INSTRUMENT-END") {
            if (waveform_ptr && envelope_ptr) {
                auto instr = std::make_shared<Instrument>(name, waveform_ptr, envelope_ptr);
                instruments.addInstrument(name, instr);
                return instr;
            }
            return nullptr;
        } else if (keyword == "WAVEFORM") {
            std::string wf_name, wf_type;
            linestream >> wf_name >> wf_type;
            
            waveform_ptr = score.getWaveforms().getWaveform(wf_name);
            
            if (waveform_ptr) {
                while (std::getline(is, line)) {
                    std::istringstream ws(line);
                    std::string wfKeyword;
                    ws >> wfKeyword;
                    if (wfKeyword == "WAVEFORM-END") break;
                }
            } else {
                std::unique_ptr<Waveform> new_waveform = WaveformFactory::create(wf_type, wf_name);
                if (!new_waveform) return nullptr;
                
                waveform_ptr = std::move(new_waveform);
                score.getWaveforms().addWaveform(wf_name, waveform_ptr);
                
                while (std::getline(is, line)) {
                    std::istringstream ws(line);
                    std::string wfParam;
                    ws >> wfParam;
                    
                    if (wfParam == "WAVEFORM-END") {
                        break;
                    } else if (wfParam == "AMPLITUDE") {
                        double amp;
                        if (!(ws >> amp)) return nullptr;
                        waveform_ptr->setAmplitude(amp);
                    } else if (!wfParam.empty()) {
                        return nullptr; 
                    }
                }
            }
        } else if (keyword == "ENVELOPE") {
            std::string env_name, env_type;
            linestream >> env_name >> env_type;
            
            envelope_ptr = score.getEnvelopes().getEnvelope(env_name);
            
            if (envelope_ptr) {
                while (std::getline(is, line)) {
                    std::istringstream es(line);
                    std::string envKeyword;
                    es >> envKeyword;
                    if (envKeyword == "ENVELOPE-END") break;
                }
            } else {
                std::unique_ptr<Envelope> new_envelope = EnvelopeFactory::create(env_type, env_name);
                if (!new_envelope) return nullptr;
                
                envelope_ptr = std::move(new_envelope);
                score.getEnvelopes().addEnvelope(env_name, envelope_ptr);
                
                while (std::getline(is, line)) {
                    std::istringstream es(line);
                    std::string envParam;
                    es >> envParam;
                    
                    if (envParam == "ENVELOPE-END") {
                        break;
                    } else if (envParam == "MAXIMUM-AMPLITUDE") {
                        double amp;
                        if (!(es >> amp)) return nullptr;
                        envelope_ptr->setMaximumAmplitude(amp);
                    } else if (envParam == "ATTACK-SECONDS") {
                        double a;
                        if (!(es >> a)) return nullptr;
                        if (auto adsr = dynamic_cast<ADSREnvelope*>(envelope_ptr.get())) {
                            adsr->setAttackSeconds(a);
                        } else if (auto ad = dynamic_cast<ADEnvelope*>(envelope_ptr.get())) {
                            ad->setAttackSeconds(a);
                        }
                    } else if (envParam == "DECAY-SECONDS") {
                        double d;
                        if (!(es >> d)) return nullptr;
                        if (auto adsr = dynamic_cast<ADSREnvelope*>(envelope_ptr.get())) {
                            adsr->setDecaySeconds(d);
                        } else if (auto ad = dynamic_cast<ADEnvelope*>(envelope_ptr.get())) {
                            ad->setDecaySeconds(d);
                        }
                    } else if (envParam == "SUSTAIN-AMPLITUDE") {
                        double s;
                        if (!(es >> s)) return nullptr;
                        if (auto adsr = dynamic_cast<ADSREnvelope*>(envelope_ptr.get())) {
                            adsr->setSustainAmplitude(s);
                        }
                    } else if (envParam == "RELEASE-SECONDS") {
                        double r;
                        if (!(es >> r)) return nullptr;
                        if (auto adsr = dynamic_cast<ADSREnvelope*>(envelope_ptr.get())) {
                            adsr->setReleaseSeconds(r);
                        }
                    } else if (!envParam.empty()) {
                        return nullptr;
                    }
                }
            }
        } else if (!keyword.empty()) {
            return nullptr;
        }
    }

    return nullptr;
}


void ScoreReader::readStaff(std::istream& is, MusicalScore& score, MusicalStaff& staff) const {
    std::string staff_name, instrument_name;
    if (!(is >> staff_name >> instrument_name)) return;

    std::shared_ptr<Instrument> instr = score.getInstrumentarium().getInstrument(instrument_name);
    if (!instr) return;

    staff.setName(staff_name);
    staff.setInstrument(instr);

    std::string token;
    while (is >> token) {
        if (token == "END-STAFF") {
            return;
        }

        try {
            double start = std::stod(token); 
            std::string note_text;
            is >> note_text;

            Note note;
            note.set(note_text);

            StaffNote staff_note(note, start);
            staff.addNote(staff_note);
        } catch (const std::invalid_argument&) {
            return;
        }
    }
}
