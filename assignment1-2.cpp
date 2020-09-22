#include <iostream>
    #include <cstdlib>
    #include <string>
    #include <algorithm>

    #include <fstream>

using namespace std;

int getCharIndex(char c) {
    if(c == 'A') {
            return 0;
    }
    if(c == 'C') {
            return 1;
    }
    if(c == 'T') {
            return 2;
    }
    if(c == 'G') {
            return 3;
    }
    return -1;
}
char getCharFromIndex(int index) {
    char str[] = {'A', 'C', 'T', 'G'};
    return str[index];
}

void printNucleotide(int counts[4]) {
    for(int i=0; i<4; i++) {
            if(counts[i] != 0) {
                    cout << getCharFromIndex(i) << ": " << counts[i] << endl;
            }
    }
}

void printNucleotideBiagram(int counts[4][4]) {
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            if(counts[i][j] != 0) {
                cout << getCharFromIndex(i) << getCharFromIndex(j);
                cout << ": " << counts[i][j] << endl;
            }
        }
    }
}

int main() {

    string fileName;

    while(true) {

        cout << "Enter input file name: ";
        cin >> fileName;

        ifstream myfile;

        myfile.open(fileName.c_str());

        string line;

        // counts of A, C, T, G
        int counts[4] = {0};

        // counts of
        int biagramCounts[4][4] = {0};

        // total dna strings
        int dnaCount = 0;

        // total sum of dna strings
        int totalDnaLength = 0;

        double avg, variance, standard_deviation;

        cout << "The DNA nucleotides is A,C,T or G" << endl;

        //read each line of the file
        while (getline(myfile, line)) {

            if(line.empty()) {
                continue;
            }

            // convert to uppercase
            transform(line.begin(), line.end(),line.begin(), ::toupper);

            for(int i=0; i<line.size(); i++) {
                int thisChar = getCharIndex(line.at(i));

                // increase count of single DNA char
                counts[thisChar] += 1;

                if(i != 0) {

                    // increase count of biagram
                    int lastChar = getCharIndex(line.at(i-1));
                    biagramCounts[thisChar][lastChar] += 1;
                }
            }

            totalDnaLength += line.size();
            dnaCount += 1;
        }

        myfile.close();

        avg = totalDnaLength / dnaCount;

        // for finding variance, we need to again read file:
        myfile.open("mydna.txt");

        //read each line of the file
        while (getline(myfile, line)) {
              variance += pow(line.size() - avg, 2);
      }

        variance = variance / dnaCount;

        standard_deviation = sqrt(variance);

        //output
        cout << "The sum is " << totalDnaLength << endl;
        cout << "The count is " << dnaCount << endl;
        cout << "The average is " << avg << endl;
        cout << "The variance is " << variance << endl;
        cout << "The Standard Deviation is: " << standard_deviation << endl;

        printNucleotide(counts);
        printNucleotideBiagram(biagramCounts);

        char command;
        cout << "Do you want to process another list(y/n) ?" << endl;
        cin >> command;

        if(command == 'n' || command == 'N') {
                break;
        }

    }
    return 0;

}
