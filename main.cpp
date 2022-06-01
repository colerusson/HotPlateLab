#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int main() {
    const int VALUE_PRECISION = 3;
    const int VALUE_WIDTH = 9;
    const int NUM_ROWS = 10;
    const int NUM_COLUMNS = 10;
    const double ONE_HUNDRED = 100.0;
    const double VALUE_DIFF = 0.1;
    double zeroValue = 0.0;
    const double CONST_ZERO = 0.0;
    const double NUMBER_FOUR = 4.0;
    double oldHotPlateValues[NUM_ROWS][NUM_COLUMNS];
    double newHotPlateValues[NUM_ROWS][NUM_COLUMNS];
    unsigned int i = 0;
    unsigned int j = 0;
    int iterationCounter = 0;
    bool bigDifference = true;
    ofstream outFile;
    ifstream inFile;


    for (i = 0; i < NUM_ROWS; ++i) {
        for (j = 0; j < NUM_COLUMNS; ++j) {
            if (((i == 0) || (i == 9)) && ((j != 0) && (j != 9))) {
                oldHotPlateValues[i][j] = ONE_HUNDRED;
            } else if (((i == 0) || (i == 9)) && ((j == 0) || (j == 9))) {
                oldHotPlateValues[i][j] = CONST_ZERO;
            } else {
                oldHotPlateValues[i][j] = zeroValue;
            }
        }
    }

    cout << "Hotplate simulator\n\n" << "Printing the initial plate values..." << endl;

    for (i = 0; i < NUM_ROWS; ++i) {
        for (j = 0; j < NUM_COLUMNS; ++j) {
            if (j != 9) {
                cout << setw(VALUE_WIDTH) << fixed << setprecision(VALUE_PRECISION) << oldHotPlateValues[i][j] << ",";
            } else {
                cout << setw(VALUE_WIDTH) << fixed << setprecision(VALUE_PRECISION) << oldHotPlateValues[i][j];
            }
        }
        cout << endl;
    }

    for (i = 0; i < NUM_ROWS; ++i) {
        for (j = 0; j < NUM_COLUMNS; ++j) {
            newHotPlateValues[i][j] = oldHotPlateValues[i][j];
        }
    }
    cout << "Printing plate after one iteration..." << endl;
    for (i = 1; i < NUM_ROWS - 1; ++i) {
        for (j = 1; j < NUM_COLUMNS - 1; ++j) {
            newHotPlateValues[i][j] =
                    ((oldHotPlateValues[i - 1][j]) + (oldHotPlateValues[i][j - 1]) + (oldHotPlateValues[i][j + 1]) +
                     (oldHotPlateValues[i + 1][j])) / NUMBER_FOUR;
        }
    }

    for (i = 0; i < NUM_ROWS; ++i) {
        for (j = 0; j < NUM_COLUMNS; ++j) {
            if (j != 9) {
                cout << setw(VALUE_WIDTH) << fixed << setprecision(VALUE_PRECISION) << newHotPlateValues[i][j] << ",";
            } else {
                cout << setw(VALUE_WIDTH) << fixed << setprecision(VALUE_PRECISION) << newHotPlateValues[i][j];
            }
        }
        cout << endl;
    }

    while (bigDifference) {
        bigDifference = false;
        for (i = 1; i < NUM_ROWS - 1; ++i) {
            for (j = 1; j < NUM_COLUMNS - 1; ++j) {
                newHotPlateValues[i][j] =
                        ((oldHotPlateValues[i - 1][j]) + (oldHotPlateValues[i][j - 1]) + (oldHotPlateValues[i][j + 1]) +
                         (oldHotPlateValues[i + 1][j])) / NUMBER_FOUR;
            }
        }
        for (i = 1; i < NUM_ROWS - 1; ++i) {
            for (j = 1; j < NUM_COLUMNS - 1; ++j) {
                if (abs(newHotPlateValues[i][j] - oldHotPlateValues[i][j]) >= VALUE_DIFF) {
                    bigDifference = true;
                }
                oldHotPlateValues[i][j] = newHotPlateValues[i][j];
            }
        }
    }

    cout << "Printing final plate..." << endl;
    for (i = 0; i < NUM_ROWS; ++i) {
        for (j = 0; j < NUM_COLUMNS; ++j) {
            if (j != 9) {
                cout << setw(VALUE_WIDTH) << fixed << setprecision(VALUE_PRECISION) << newHotPlateValues[i][j] << ",";
            } else {
                cout << setw(VALUE_WIDTH) << fixed << setprecision(VALUE_PRECISION) << newHotPlateValues[i][j];
            }
        }
        cout << endl;
    }

    cout << "Writing final plate to \"Hotplate.csv\"..." << endl;
    outFile.open("Hotplate.csv");
    if (!outFile.is_open()) {
        cout << "Couldn't open file. Exiting" << endl;

        return 1;
    }

    for (i = 0; i < NUM_ROWS; ++i) {
        for (j = 0; j < NUM_COLUMNS; ++j) {
            if (j != 9) {
                outFile << setw(VALUE_WIDTH) << fixed << setprecision(VALUE_PRECISION) << newHotPlateValues[i][j]
                        << ",";
            } else {
                outFile << setw(VALUE_WIDTH) << fixed << setprecision(VALUE_PRECISION) << newHotPlateValues[i][j];
            }
        }
        outFile << endl;
    }
    outFile.close();

    inFile.open("Inputplate.txt");
    if (!inFile.is_open()) {
        cout << "Couldn't open file. Exiting" << endl;

        return 1;
    }
    for (i = 0; i < NUM_ROWS; ++i) {
        for (j = 0; j < NUM_COLUMNS; ++j) {
            inFile >> newHotPlateValues[i][j];
        }
    }
    inFile.close();

    for (i = 0; i < NUM_ROWS; ++i) {
        for (j = 0; j < NUM_COLUMNS; ++j) {
            oldHotPlateValues[i][j] = newHotPlateValues[i][j];
        }
    }
    while (iterationCounter < 3) {
        for (i = 1; i < NUM_ROWS - 1; ++i) {
            for (j = 1; j < NUM_COLUMNS - 1; ++j) {
                newHotPlateValues[i][j] =
                        ((oldHotPlateValues[i - 1][j]) + (oldHotPlateValues[i][j - 1]) + (oldHotPlateValues[i][j + 1]) +
                         (oldHotPlateValues[i + 1][j])) / NUMBER_FOUR;
            }
        }
        for (i = 0; i < NUM_ROWS; ++i) {
            for (j = 0; j < NUM_COLUMNS; ++j) {
                oldHotPlateValues[i][j] = newHotPlateValues[i][j];
            }
        }
        ++iterationCounter;
    }


    cout << endl << "Printing final plate after 3 updates..." << endl;

    for (i = 0; i < NUM_ROWS; ++i) {
        for (j = 0; j < NUM_COLUMNS; ++j) {
            if (j != 9) {
                cout << setw(VALUE_WIDTH) << fixed << setprecision(VALUE_PRECISION) << newHotPlateValues[i][j] << ",";
            } else {
                cout << setw(VALUE_WIDTH) << fixed << setprecision(VALUE_PRECISION) << newHotPlateValues[i][j];
            }
        }
        cout << endl;
    }


    return 0;
}
