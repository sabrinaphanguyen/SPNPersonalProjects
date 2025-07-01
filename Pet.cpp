// Student ID: 20470614
//  Pet.cpp
//  2a-Lab-06-Pets
//
#include <iostream>
#include <sstream>
#include <vector>
#include "Pet.h"
using namespace std;
// This is a way to properly initialize (out-of-line) a static variable.
size_t Pet::_population = 0;
Pet::Pet(string name, long id, int num_limbs) {
    _name = name;
    _id = id;
    _num_limbs = num_limbs;
    _population++; // increments population on object creation
}
Pet::~Pet() {
    _population--; // decrements population on object destruction
}
string Pet::get_name() const { 
    return _name; 
}
long Pet::get_id() const { // getter- returns the requested value while leaving it untouched. 
    return _id;
}
int Pet::get_num_limbs() const {
    return _num_limbs;
}
bool Pet::set_name(string name) { // setters- returns a boolean value if the input is a valid answer
    if(name.empty()) {
        return false; 
    }
    _name = name;
    return true;
}
bool Pet::set_id(long id) {
    if(id < 0) {
        return false;
    }
    _id = id;
    return true; 
}
bool Pet::set_num_limbs(int num_limbs) {
    if(num_limbs < 0) {
        return false;
    }
    _num_limbs = num_limbs;
    return true; 
}
string Pet::to_string() const {
    stringstream ss;
    ss << "(Name: " << _name << ", ID: " << _id << ", Limb Count: " << _num_limbs << ")"; 
    return ss.str(); 
}
// Fill in the supplied pets vector with n pets whose
// properties are chosen randomly.
// Don't mess with this method more than necessary.
void Pet::get_n_pets(size_t n, std::vector<Pet>& pets, int name_len) {
    pets.resize(n);

    long prev_id = 0;
    for (size_t i = 0; i < n; i++) {
        long id = prev_id + 1 + rand() % 10;
        pets[i].set_id(id);
        pets[i].set_num_limbs(rand() % 9); // up to arachnids
        pets[i].set_name(make_a_name(name_len));

        prev_id = id;
    }
}
// ---------------------------------------------------------------------
string Pet::make_a_name(int len) {
    
string vowels = "aeiou";
string consonants = "bcdfghjklmnpqrstvwxyz";
string name = "";

int flag = rand()%2; // sets random flag value

for(int i=0; i<len; i++) {
    if(flag==0)
       name += consonants[rand() % consonants.length()];
    else
        name += vowels[rand() % vowels.length()]; // if flag is 0 it produces a random vowel from string

    flag = (flag+1)%2; // ensures that the flag values are alternated between 1 and 0. creates alternate pattern between vowel and consonant
    }
return name;
}

// Optional EC points
// Global helpers
bool operator==(const Pet& pet1, const Pet& pet2) {
    return (pet1.get_name() == pet2.get_name()) && (pet1.get_id() == pet2.get_id()) && (pet1.get_num_limbs() == pet2.get_num_limbs());
}
bool operator!=(const Pet& pet1, const Pet& pet2) {
    return (pet1.get_name() != pet2.get_name()) && (pet1.get_id() != pet2.get_id()) && (pet1.get_num_limbs() != pet2.get_num_limbs());
}
ostream& operator<<(ostream& os, const Pet& pet) {
    os << pet.to_string();
    return os;
}