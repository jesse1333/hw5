#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void findCombinations(const std::string& in, const std::string& floating, int index, int count, std::string current, std::set<std::string>& combinations, const std::set<std::string>& dict, int numOfDashes);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    std::set<std::string> validWords;
    int numOfDashes = 0;
    for (int i = 0; i < in.size(); i++) {
        if (in[i] == '-') {
            numOfDashes++;
        }
    }

    findCombinations(in, floating, 0, 0, in, validWords, dict, numOfDashes);
    return validWords;
}

// Define any helper functions here
void findCombinations(const std::string& in, const std::string& floating, int index, int count, std::string current, std::set<std::string>& combinations, const std::set<std::string>& dict, int numOfDashes) {
    if (index == in.size()) {
        // if not all characters are filled in, return
        if (floating.size() != 0) {
            return;
        }

        // if character is found in dictionary, we add it
        else if (dict.find(current) != dict.end()) {
            combinations.insert(current);
            return;
        }
        return;
    }

    if (in[index] == '-') {

        // if is a dash, iterate through every character in floating and call function recursively
        if (numOfDashes == floating.size()) {
            // if all the dashes are filled with floating characters
            for (int i = 0; i < floating.size(); i++) {
                current[index] = floating[i];
                string floatingCopy = floating;
                floatingCopy.erase(i, 1);

                // put in the new string (update the floating)
                findCombinations(in, floatingCopy, index + 1, count + 1, current, combinations, dict, numOfDashes - 1);
            }
        }
        else {
            // fills the rest of the - with non-floating characters
            char letter = 'a';
            for (int i = 0; i < 26; i++) {
                bool copy = false;
                string floatingCopy = floating;
                // if the letter is the random one we want to update the floating

                if (floating.find(letter) != string::npos) {
                    copy = true;
                    floatingCopy.erase(floating.find(letter), 1);
                }

                current[index] = letter;

                if (copy) {
                    findCombinations(in, floatingCopy, index + 1, count, current, combinations, dict, numOfDashes - 1);
                }
                else {
                    findCombinations(in, floating, index + 1, count, current, combinations, dict, numOfDashes - 1);
                }

                ++letter;
            }
            current[index] = '-';
        }

    }
    else {
        // if not a dash, we just add the character to the current string being constructed & iterate the index
        findCombinations(in, floating, index + 1, count, current, combinations, dict, numOfDashes);
    }
}
