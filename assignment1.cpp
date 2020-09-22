#include <algorithm>  // std::transform - toUpperCase for string
#include <fstream>    // file I/O
#include <iostream>
#include <string>
#include <cmath>    // std::round - rounding floats
#include <sstream>  // std::stringstream - convert string to int
using namespace std;

int main(int argc, char ** argv) {
        // initializing variables.
        const double twoPi = 2.0 * 3.141592653;
        bool condition = true;
        char command;
        float inFileLineCount = 0;
        float totalNumberofNucleotiede = 0;
        float dnaVariance = 0;
        float dnaMean = 0;
        float dnaStandardDev = 0;
        int y = 0, progCount = 0, difference = 0;
        string currentLine = "", inFileLineLengths = "", inFileNucleotideChars = "", userPath = "";

        do {
                // Determine whether to use commandline args path or user input path
                if (progCount < 1) {
                        userPath = argv[1];
                }
                // Opening the input file.
                ifstream inFile(userPath);
                // Opening the output file.
                ofstream outFile("danielnaryshev.txt");
                outFile << "~~~~~ Daniel Naryshev | 2327209 | Assignment 1 ~~~~~ " << endl;
                // If the input file contains data read line by line
                if (inFile) {
                        while (inFile >> currentLine) {
                                // while input file contains lines to read from
                                inFileLineCount++;
                                // Handling odd number strings
                                if (currentLine.size() % 2 != 0) {
                                        // if currentline size is odd add the first nucleotide to the end of
                                        // the string.
                                        currentLine = currentLine + currentLine.at(0);
                                }

                                inFileLineLengths +=
                                        to_string(currentLine.size()); // String containing the lengths of
                                // the input file lines.
                                totalNumberofNucleotiede += currentLine.size();
                                inFileNucleotideChars += currentLine; // String containing all the
                                // nucleotides from input file.
                        }
                        inFile.close();
                        dnaMean = totalNumberofNucleotiede /
                                  inFileLineCount; // calculate mean of dna nu
                        for (size_t i = 0; i < inFileLineLengths.size(); i++) {
                                stringstream ss; // String stream converts string to int. Converting
                                // the line lengths back to int.
                                ss << inFileLineLengths[i];
                                ss >> difference;
                                dnaVariance += pow(difference - dnaMean, 2); // compute squared
                                // differences from the
                                // mean and find sum of
                                // square differences
                        }

                        dnaVariance = dnaVariance /
                                      inFileLineLengths.size(); // Variance of dna nucleotides
                        dnaStandardDev = sqrt(dnaVariance); // Sandard Deviation of nucleotides

                        outFile << "The Sum of the length of the DNA strings is: " <<
                                totalNumberofNucleotiede << endl;
                        outFile << "The Mean of the length of the DNA strings is: " << dnaMean <<
                                endl;
                        outFile << "The Variance of the length of the DNA strings is: " <<
                                dnaVariance << endl;
                        outFile << "The Standard Deviation of the length of the DNA strings is: " <<
                                dnaStandardDev << endl;

                        // Calculating nucleotide relative frequency...

                        transform(inFileNucleotideChars.begin(), inFileNucleotideChars.end(),
                                  inFileNucleotideChars.begin(), ::toupper); // Transform characters to uppercase.
                        double aCount = 0, cCount = 0, tCount = 0, gCount = 0;
                        for (size_t i = 0; i < inFileNucleotideChars.size(); i++) {
                                switch (inFileNucleotideChars[i]) {
                                case 'A':
                                        aCount++;
                                        break;
                                case 'C':
                                        cCount++;
                                        break;
                                case 'T':
                                        tCount++;
                                        break;
                                case 'G':
                                        gCount++;
                                        break;
                                }
                        }

                        float relativeProbabilityA = aCount / inFileNucleotideChars.size();
                        float relativeProbabilityC = cCount / inFileNucleotideChars.size();
                        float relativeProbabilityT = tCount / inFileNucleotideChars.size();
                        float relativeProbabilityG = gCount / inFileNucleotideChars.size();

                        // Print nucleotide relative probability
                        outFile << "Here is the relative probability of each nucleotide: " <<
                                endl;
                        outFile << "A : " << relativeProbabilityA << endl;
                        outFile << "C : " << relativeProbabilityC << endl;
                        outFile << "T : " << relativeProbabilityT << endl;
                        outFile << "G : " << relativeProbabilityG << endl;

                        // Calculating nucleotide Bigram relative frequency...

                        double aaCount = 0, acCount = 0, atCount = 0, agCount = 0;
                        double caCount = 0, ccCount = 0, ctCount = 0, cgCount = 0;
                        double taCount = 0, tcCount = 0, ttCount = 0, tgCount = 0;
                        double gaCount = 0, gcCount = 0, gtCount = 0, ggCount = 0;

                        for (size_t i = 0; i < inFileNucleotideChars.size(); i += 2) {
                                switch (inFileNucleotideChars[i]) {
                                case 'A':
                                        switch (inFileNucleotideChars[i + 1]) {
                                        case 'A':
                                                aaCount++;
                                                break;
                                        case 'C':
                                                acCount++;
                                                break;
                                        case 'T':
                                                atCount++;
                                                break;
                                        case 'G':
                                                agCount++;
                                                break;
                                        }
                                        break;
                                case 'C':
                                        switch (inFileNucleotideChars[i + 1]) {
                                        case 'A':
                                                caCount++;
                                                break;
                                        case 'C':
                                                ccCount++;
                                                break;
                                        case 'T':
                                                ctCount++;
                                                break;
                                        case 'G':
                                                cgCount++;
                                                break;
                                        }
                                        break;
                                case 'T':
                                        switch (inFileNucleotideChars[i + 1]) {
                                        case 'A':
                                                taCount++;
                                                break;
                                        case 'C':
                                                tcCount++;
                                                break;
                                        case 'T':
                                                ttCount++;
                                                break;
                                        case 'G':
                                                tgCount++;
                                                break;
                                        }
                                        break;
                                case 'G':
                                        switch (inFileNucleotideChars[i + 1]) {
                                        case 'A':
                                                gaCount++;
                                                break;
                                        case 'C':
                                                gcCount++;
                                                break;
                                        case 'T':
                                                gtCount++;
                                                break;
                                        case 'G':
                                                ggCount++;
                                                break;
                                        }
                                        break;
                                }
                        }
                        // Output bigram relative probability
                        int bigramCount = inFileNucleotideChars.size() / 2;
                        outFile << "Here is the relative probability of each nucleotide bigram: " <<
                                endl;
                        outFile << "AA : " << aaCount / bigramCount << endl;
                        outFile << "AC : " << acCount / bigramCount << endl;
                        outFile << "AT : " << atCount / bigramCount << endl;
                        outFile << "AG : " << agCount / bigramCount << endl;
                        outFile << "CA : " << caCount / bigramCount << endl;
                        outFile << "CC : " << ccCount / bigramCount << endl;
                        outFile << "CT : " << ctCount / bigramCount << endl;
                        outFile << "CG : " << cgCount / bigramCount << endl;
                        outFile << "TA : " << taCount / bigramCount << endl;
                        outFile << "TC : " << tcCount / bigramCount << endl;
                        outFile << "TT : " << ttCount / bigramCount << endl;
                        outFile << "TG : " << tgCount / bigramCount << endl;
                        outFile << "GA : " << gaCount / bigramCount << endl;
                        outFile << "GC : " << gcCount / bigramCount << endl;
                        outFile << "GT : " << gtCount / bigramCount << endl;
                        outFile << "GG : " << ggCount / bigramCount << endl;

                        outFile << "1000 Lines of DNA : " << endl;

                        // initializing variables for gaussian distribution
                        string generatedDNA = "";
                        float a = 0, b = 0, c = 0, d = 0;

                        srand(time(NULL)); // seeding the random number generator
                        for (size_t i = 0; i < 1000; i++) {
                                // calculate d 1000 times
                                a = (float) rand() * (1.0 / RAND_MAX); // generate a between 0-1
                                b = (float) rand() * (1.0 / RAND_MAX); // generate b between 0-1
                                c = sqrt(-2 * log(a)) * cos(twoPi * b); // find C
                                d = (dnaStandardDev * c) + dnaMean; // find D
                                string random;
                                d = round(d);
                                // For size d, print dna string based on relative probability of
                                // nucleotides.
                                for (size_t i = 0; i < d; i++) {
                                        double val = (double) rand() * (1.0 / RAND_MAX);
                                        if (val < relativeProbabilityA) {
                                                random += "A";
                                        } else if (val < relativeProbabilityA + relativeProbabilityC) {
                                                random += "C";
                                        } else if (val < relativeProbabilityA + relativeProbabilityC +
                                                   relativeProbabilityG) {
                                                random += "T";
                                        } else {
                                                random += "G";
                                        }
                                        generatedDNA = random;
                                }

                                outFile << generatedDNA << endl;
                        }
                } else {
                        cout << "Failed to open file..." << userPath << endl;
                }

                cout << "Do you want to process another list(y/n) ?" << endl;
                cin >> command;

                if (command == 'n' || command == 'N') {
                        condition = false;
                        break;
                } else {
                        condition = true;
                        std::cout << "Please enter new File Name... : " << endl;
                        cin >> userPath;
                }
                progCount++;
        } while (condition);
        return 0;
}
