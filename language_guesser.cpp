/*
================================================================================

 Language guessing program expanded from an assignment given in
 a C++ course from Uppsala University. Only the letters A-Z are handled
 and language is guessed based on how the relative frequencies differ from
 normal letter frequencies in respective languages. The normal letter
 frequencies have been collected from the Wikipedia page "Letter frequency".

================================================================================
Programkod:
===========
*/


#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// GLOBAL CONSTANTS
const int NUM_LETTERS = 26;  //A-Z
const int NUM_LANGUAGES = 15;

const string LANGUAGES[NUM_LANGUAGES] = {
    "English", "French", "German", "Spanish", "Portuguese",
    "Esperanto", "Italian", "Turkish", "Swedish", "Polish",
    "Dutch", "Danish", "Icelandic", "Finnish", "Czech"
};

const double LETTER_FREQS[NUM_LETTERS][NUM_LANGUAGES]=

{
    { // A
        8.167, 7.636, 6.516, 11.525, 14.634, 12.117, 11.745, 11.920, 9.383, 8.910, 7.486, 6.025, 10.110, 12.217, 8.421
    },
    { // B
        1.492, 0.901, 1.886, 2.215, 1.043, 0.980, 0.927, 2.844, 1.535, 1.470, 1.584, 2.000, 1.043, 0.281, 0.822
    },
    { // C
        2.782, 3.260, 2.732, 4.019, 3.882, 0.776, 4.501, 0.963, 1.486, 3.960, 1.242, 0.565, 0, 0.281, 0.740
    },
    { // ...
        4.253, 3.669, 5.076, 5.010, 4.992, 3.044, 3.736, 4.706, 4.702, 3.250, 5.933, 5.858, 1.575, 1.043, 3.475
    },
    {
        12.702, 14.715, 16.396, 12.181, 12.570, 8.995, 11.792, 8.912, 10.149, 7.660, 18.91, 15.453, 6.418, 7.968, 7.562
    },
    {
        2.228, 1.066, 1.656, 0.692, 1.023, 1.037, 1.153, 0.461, 2.027, 0.300, 0.805, 2.406, 3.013, 0.194, 0.084
    },
    {
        2.015, 0.866, 3.009, 1.768, 1.303, 1.171, 1.644, 1.253, 2.862, 1.420, 3.403, 4.077, 4.241, 0.392, 0.092
    },
    {
        6.094, 0.737, 4.577, 0.703, 0.781, 0.384, 0.636, 1.212, 2.090, 1.080, 2.380, 1.621, 1.871, 1.851, 1.356
    },
    {
        6.966, 7.529, 6.550, 6.247, 6.186, 10.012, 10.143, 8.600, 5.817, 8.210, 6.499, 6.000, 7.578, 10.817, 6.073
    },
    {
        0.153, 0.613, 0.268, 0.493, 0.397, 3.501, 0.011, 0.034, 0.614, 2.280, 1.46, 0.730, 1.144, 2.042, 1.43
    },
    {
        0.772, 0.074, 1.417, 0.011, 0.015, 4.163, 0.009, 4.683, 3.140, 3.510, 2.248, 3.395, 3.314, 4.973, 2.894
    },
    {
        4.025, 5.456, 3.437, 4.967, 2.779, 6.104, 6.510, 5.922, 5.275, 2.100, 3.568, 5.229, 4.532, 5.761, 3.802
    },
    {
        2.406, 2.968, 2.534, 3.157, 4.738, 2.994, 2.512, 3.752, 3.471, 2.800, 2.213, 3.237, 4.041, 3.202, 2.446
    },
    {
        6.749, 7.095, 9.776, 6.712, 4.446, 7.955, 6.883, 7.487, 8.542, 5.520, 10.032, 7.240, 7.711, 8.826, 6.468
    },
    {
        7.507, 5.796, 2.594, 8.683, 9.735, 8.779, 9.832, 2.476, 4.482, 7.750, 6.063, 4.636, 2.166, 5.614, 6.695
    },
    {
        1.929, 2.521, 0.670, 2.510, 2.523, 2.755, 3.056, 0.886, 1.839, 3.130, 1.57, 1.756, 0.789, 1.842, 1.906
    },
    {
        0.095, 1.362, 0.018, 0.877, 1.204, 0, 0.505, 0, 0.020, 0.140, 0.009, 0.007, 0, 0.013, 0.001
    },
    {
        5.987, 6.693, 7.003, 6.871, 6.530, 5.914, 6.367, 6.722, 8.431, 4.690, 6.411, 8.956, 8.581, 2.872, 4.799
    },
    {
        6.327, 7.948, 7.270, 7.977, 6.805, 6.092, 4.981, 3.014, 6.590, 4.320, 3.73, 5.805, 5.630, 7.862, 5.212
    },
    {
        9.056, 7.244, 6.154, 4.632, 4.336, 5.276, 5.623, 3.314, 7.691, 3.980, 6.79, 6.862, 4.953, 8.750, 5.727
    },
    {
        2.758, 6.311, 4.166, 2.927, 3.639, 3.183, 3.011, 3.235, 1.919, 2.500, 1.99, 1.979, 4.562, 5.008, 2.160
    },
    {
        0.978, 1.838, 0.846, 1.138, 1.575, 1.904, 2.097, 0.959, 2.415, 0.040, 2.85, 2.332, 2.437, 2.250, 5.344
    },
    {
        2.360, 0.049, 1.921, 0.017, 0.037, 0, 0.033, 0, 0.142, 4.650, 1.52, 0.069, 0, 0.094, 0.016
    },
    {
        0.150, 0.427, 0.034, 0.215, 0.253, 0, 0.003, 0, 0.159, 0.020, 0.036, 0.028, 0.046, 0.031, 0.027

    },
    {
        1.974, 0.128, 0.039, 1.008, 0.006, 0, 0.020, 3.336, 0.708, 3.760, 0.035, 0.698, 0.900, 1.745, 1.043
    },
    {
        0.074, 0.326, 1.134, 0.467, 0.470, 0.494, 1.181, 1.500, 0.070, 5.640, 1.39, 0.034, 0, 0.051, 1.503
    }
};



//--------------------------------------------------------
// DECLARATIONS

void calc_histogram_abs(string &text, int freq[], int &num_of_characters);
void abs_to_relative(int freq[], int &num_of_characters, double rel_freqs[]);
void plot_histogram(const double rel_freqs[]);
void interpret(const double rel_freqs[]);
void terminal_line();

string file_name();
string read(string &filename);

//--------------------------------------------------------
// MAIN PROGRAM:

int main() {
    
    int total_num_letters, freq[NUM_LETTERS] = {};
    double rel_freqs[NUM_LETTERS] = {};
    
    string filename = file_name();
    string read_text = read(filename);
    
    if (read_text.length() == 0) {
        cout << endl << "There's no file named " << filename << endl;
    } else {
        cout << endl << "Result for letters A-Z" << endl;
        terminal_line();
        calc_histogram_abs(read_text, freq, total_num_letters);
        cout << "Total number of letters: " << total_num_letters << endl;
        
        abs_to_relative(freq, total_num_letters, rel_freqs);
        interpret(rel_freqs);
        terminal_line();
        plot_histogram(rel_freqs);
        
    }

    return 0;

}

//--------------------------------------------------------
// DEFINITIONS:

/**
 Calculates and summarizes frequencies for letters in the text. Not case sensitive.
 @param text the text to analyse
 @param freq array for letter frequencies
 @param num_of_characters counter for total numbers of found letters
 */
void calc_histogram_abs(string &text, int freq[], int &num_of_characters) {
    
    for (int i = 0; i < text.length(); i++) {
        char letter = toupper(text[i]);
        if(letter >= 'A' && letter <= 'Z') {
            freq[letter - 'A']++;
            num_of_characters++;
        }
    }

}

/**
 Converts absolute numbers in the histogram to relative frequency.
 @param freq array with absolute frequencies
 @param num_of_characters total number of characters
 @param rel_freqs array with relative frequencies
 */
void abs_to_relative(int freq[], int &num_of_characters, double rel_freqs[]) {
    for (int i = 0; i < NUM_LETTERS; i++) {
        rel_freqs[i] = 100 * (double) freq[i] / num_of_characters;
    }
}

/**
 Prints the histogrm with relative frequencies with one star per 0.5% (rounded, not truncated).
 @param rel_freqs relative letter frequencies
 */
void plot_histogram(const double rel_freqs[]) {
    cout << "Letter split:" << endl << endl;
    for (int i = 0; i < NUM_LETTERS; i++) {
        cout << char(65 + i) << ": ";
        
        for (double j = 0; j < round(rel_freqs[i] * 2) / 2.0; j += 0.5) {
            cout << "* ";
        }
        
        cout << endl;
        
    }
}

/**
 Calculates the difference between the measured relative frequencies and each language.
 Prints the result and which language is most likely, based on the letter frequencies.
 @param rel_freqs relative letter frequencies
 */
void interpret(const double rel_freqs[]) {
    double quadratic_sum[NUM_LANGUAGES], min = 10000.0;
    int min_index = -1;
    
    for (int i = 0; i < NUM_LANGUAGES; i++) {
        quadratic_sum[i] = 0;
        
        for (int j = 0; j < NUM_LETTERS; j++) {
            quadratic_sum[i] += pow(rel_freqs[j] - LETTER_FREQS[j][i], 2);
        }
        
        if(quadratic_sum[i] < min) {
            min = quadratic_sum[i];
            min_index = i;
        }
        
        cout << LANGUAGES[i] << " has the quadratic sum: " << quadratic_sum[i] << endl;
        
    }
    
    // lowercased first letter in language name
    cout << "\nThe language is most likely " << (char) tolower(LANGUAGES[min_index][0]) << LANGUAGES[min_index].substr(1,8) << endl;

}

/**
 Prints a line to the terminal for readability.
 */
void terminal_line() {
    cout << endl;
    for (int i = 0; i < 40; i++) {
        cout << '-';
    }
    cout << endl << endl;
}

/**
 Reads a filename and adds .txt if needed.
 @return a correct .txt file name
 */
string file_name() {
    string filename;
    cout << "Name of the file:" << endl;
    getline(cin, filename);
    
    if(filename.length() < 4) {
        filename.append(".txt");
    } else if (filename.find(".txt") == -1) {
        filename.append(".txt");
    }
    
    return filename;
    
}

/**
 Reads the text from a file with given name and saves it in a string.
 @param filename name of the file to read from
 @return read text, empty if no file with the name exists
 */
string read(string &filename) {
    string readtext = "";
    char c;

    ifstream fin(filename.c_str());
    
    if (fin) {
        while (fin.get(c)) {
            readtext += c;
        }
    }
    
    return readtext;
    
}
