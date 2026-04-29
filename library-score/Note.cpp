#include "Note.h"
#include <iomanip>
#include <sstream>
#include <vector>

// Test Global constant
static const std::vector<std::string> g_names_flat = {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};

// Constructors
Note::Note() : name(""), duration(0.0) {}

Note::Note(const std::string& full_note) : name(""), duration(0.0) {
    set(full_note);
}

Note::Note(const std::string& name, const double& duration)
    : name(""), duration(0.0) {
    setName(name);
    setDuration(duration);
}

Note::Note(const std::string& name, const std::string& duration_str)
    : name(""), duration(0.0) {
    setName(name);
    setDuration(duration_str);
}

// Getters
const std::string& Note::getName() const {
    return name;
}

const double& Note::getDuration() const {
    return duration;
}

double Note::getFrequency() const {
    return Frequency::getFrequency(name);
}

// Setters
void Note::setName(const std::string& name_input) {
    if (Frequency::getFrequency(name_input) > 0.0) {
        name = name_input;
    }
}

void Note::setDuration(const double dur) {
    if (dur > 0.0) {
        duration = dur;
    }
}

void Note::setDuration(const std::string& dur_str) {
    if (dur_str.empty()) return;

    char base = dur_str[0];
    double base_val = 0.0;

    switch (base) {
        case 'w': base_val = WHOLE_NOTE; break;
        case 'h': base_val = HALF_NOTE; break;
        case 'q': base_val = QUARTER_NOTE; break;
        case 'e': base_val = EIGHTH_NOTE; break;
        case 's': base_val = SIXTEENTH_NOTE; break;
        default: return;
    }

    if (dur_str.length() == 1) {
        duration = base_val;
    } else if (dur_str.length() == 2) {
        char modifier = dur_str[1];
        if (modifier == '.') {
            duration = base_val * 1.5;
        } else if (modifier == 't') {
            duration = base_val / 3.0;
        }
    }
}

void Note::set(const std::string& full_note) {
    std::string name_part, dur_part;
    splitString(full_note, name_part, dur_part);
    setName(name_part);
    setDuration(dur_part);
}

// Helper
void Note::splitString(const std::string& full_note, std::string& name_out, std::string& duration_out) {
    duration_out.clear();
    name_out.clear();

    if (full_note.empty()) return;

    duration_out += full_note[0];
    if (full_note.length() >= 2 && (full_note[1] == '.' || full_note[1] == 't')) {
        duration_out += full_note[1];
        name_out = full_note.substr(2);
    } else {
        name_out = full_note.substr(1);
    }
}

// Free function
std::ostream& operator<<(std::ostream& output_stream, const Note& note) {
    output_stream << note.getDuration() << " " << note.getName()
                  << "(" << note.getFrequency() << ")";
    return output_stream;
}

// Test 
std::string Note::keyName() const {
    std::string result = name;
    result.pop_back(); 
    return result;
}

int Note::octaveNumber() const {
    char octave_char = name.back();
    return octave_char - '0';
}

unsigned int Note::findKeyPositionFlat() const {
    std::string key = keyName();
    for (unsigned int i = 0; i < g_names_flat.size(); ++i) {
        if (g_names_flat[i] == key) {
            return i;
        }
    }
    return g_names_flat.size() + 1;
}

std::string Note::relativeNoteNameFlat(unsigned int semitones) const {
    unsigned int start_pos = findKeyPositionFlat();
    if (start_pos >= g_names_flat.size()) {
        return "INVALID";
    }

    unsigned int total_pos = start_pos + semitones;
    int octave = octaveNumber() + (total_pos / g_names_flat.size());
    std::string key = g_names_flat[total_pos % g_names_flat.size()];

    std::ostringstream oss;
    oss << key << octave;
    return oss.str();
}
