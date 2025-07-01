// student id: 20470614
// Automaton.cpp

#include "Automaton.h"

Automaton::Automaton(size_t num_parents, size_t rule) {
    _num_parents = num_parents;
    _extreme_bit = 0;

    if (!set_rule(rule)) {
        _is_valid = false;
    }

    return;
}

bool Automaton::set_rule(size_t rule) {
    _rules.resize(pow_2(_num_parents));
    size_t max_rule = pow_2(pow_2(_num_parents)) - 1;

    if (_num_parents < 0 || _num_parents > MAX_PARENTS || rule > max_rule) {
        return false;
    }

    for (size_t i = 0; i <= pow_2(_num_parents); i++) {
        _rules[i] = (1 << i) & rule;
    }

    _is_valid = true;
    return true;
}

bool Automaton::equals(const Automaton &that) {
    if (_is_valid == false && that._is_valid == false) {
        return true;
    }

    if (_extreme_bit == that._extreme_bit &&
        _rules == that._rules &&
        _num_parents == that._num_parents &&
        _is_valid == true && that._is_valid == true) {
        return true;
    }

    return false;
}

size_t Automaton::translate_n_bits_starting_at(const vector<int>& bits, size_t pos, size_t n) {
    size_t ans = 0;
    size_t b = 0;

    for (int i = (int)pos + (int)n - 1; i >= (int)pos; i--) {
        if (n == 0 || i > (int)bits.size() - 1)
            return 0;

        ans += bits[i] * pow_2(b);
        b++;
    }

    return ans;
}

bool Automaton::make_next_gen(const vector<int>& current_gen, vector<int>& next_gen) {
    if (current_gen.size() % 2 == 0 && current_gen.size() != 0) {
        return false;
    }

    if (_is_valid == false) {
        return false;
    }

    if (current_gen.size() == 0) {
        next_gen.resize(0);
        next_gen.push_back(1);
        return true;
    }

    vector<int> extremeBitsAdd;
    size_t keepSize = current_gen.size() + _num_parents - 1;

    for (int i = 0; i < (int)_num_parents - 1; i++) {
        extremeBitsAdd.push_back(_extreme_bit);
    }

    for (int i = 0; i < (int)current_gen.size(); i++) {
        extremeBitsAdd.push_back(current_gen[i]);
    }

    for (int i = 0; i < (int)_num_parents - 1; i++) {
        extremeBitsAdd.push_back(_extreme_bit);
    }

    next_gen.resize(keepSize);

    for (int i = 0; i < (int)keepSize; i++) {
        size_t translate = translate_n_bits_starting_at(extremeBitsAdd, i, _num_parents);

        if (_rules[translate] == true) {
            next_gen[i] = 1;
        }
        if (_rules[translate] == false) {
            next_gen[i] = 0;
        }
    }

    if (_extreme_bit == 0) {
        _extreme_bit = _rules[0];
    } else if (_extreme_bit == 1) {
        _extreme_bit = _rules[_rules.size() - 1];
    }

    return true;
}

string Automaton::get_first_n_generations(size_t n, size_t width) {
    string result;

    // Check for validity and odd width
    if (_is_valid && width % 2) {
        // Temporary vector to store generations
        vector<int> temp;

        // Generate the first n generations and concatenate them to the result string
        while (n--) {
            make_next_gen(temp, temp);
            result += generation_to_string(temp, width) + "\n";
        }
    }

    return result;
}

string Automaton::generation_to_string(const vector<int>& gen, size_t width) {
    string result;

    // Check if the Automaton is valid and the width is odd
    if (_is_valid && width % 2) {
        if (gen.size() > width) {
            // If the generation is longer than the width, center the visible part
            size_t start = (gen.size() - width) / 2;
            size_t end = start + width;
            for (size_t i = start; i < end; i++) {
                result += (gen[i] ? '*' : ' ');
            }
        } else {
            // If the generation is shorter than the width, center and pad with extreme bit
            string extreme_bit = _extreme_bit ? "*" : " ";
            size_t padding = (width - gen.size()) / 2;

            result += string(padding, extreme_bit[0]);

            for (int value : gen) {
                result += (value ? "*" : " ");
            }

            result += string(padding, extreme_bit[0]);
        }
    }

    return result;
}