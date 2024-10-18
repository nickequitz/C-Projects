#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Employee {
   string name; //may contain whitespaces
   int nKeysPossessed; //stores the number of keys an employee owns
   string keys[5]; // Each element stores the room that the key can opens, e.g., "AHC201"
};

bool reader(string input_filename, Employee employees[], int& nEmployees) {

    ifstream fin(input_filename);

    if(!fin.is_open()) {
        return false;
    }

    fin >> nEmployees;
    
    fin.ignore();

    //cout << nEmployees << endl;

        for (int i = 0; i < nEmployees; ++i) {
            getline(fin, employees[i].name);

            fin >> employees[i].nKeysPossessed;

            for (int j = 0; j < employees[i].nKeysPossessed; ++j) {
                fin >> employees[i].keys[j];
            }
            fin.ignore();
        }

        return true;
    }

void writer(string output_filename, Employee employees[], int nEmployees) {
    ofstream fout(output_filename);
    
    if (!fout.is_open()) {
        cerr << "Error: Could not open the output file." << endl;
        return;
    }

    fout << nEmployees << endl;  // Write the number of employees once

    for (int i = 0; i < nEmployees; ++i) {
        fout << employees[i].name << endl;
        fout << employees[i].nKeysPossessed << " ";

        // Write all the keys the employee possesses without trailing space
        for (int j = 0; j < employees[i].nKeysPossessed; ++j) {
            fout << employees[i].keys[j];
            if (j != employees[i].nKeysPossessed - 1) {
                fout << " ";  // Add a space after each key except the last one
            }
        }

        fout << endl;  // Move to the next line after writing keys
    }

    fout.close();
}


bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey) {
    // Flag to check if employee is found
    bool employeeFound = false;

    for (int i = 0; i < nEmployees; ++i) {
        if (employees[i].name == emp_name) {
            employeeFound = true;  // Employee is found

            // Check if the employee already has the key
            for (int j = 0; j < employees[i].nKeysPossessed; ++j) {
                if (employees[i].keys[j] == newKey) {
                    cout << "This employee already has this key!" << endl;
                    return false;
                }
            }

            // Check if the employee can have more keys
            if (employees[i].nKeysPossessed >= 5) {
                cout << "This employee already has 5 keys!" << endl;
                return false;
            }

            // Add the new key
            employees[i].keys[employees[i].nKeysPossessed] = newKey;
            employees[i].nKeysPossessed++;
            cout << "Key added successfully." << endl; // << emp_name << "!" << endl; //test case
            return true;  // Key added successfully
        }
    }

    if (!employeeFound) {
        cout << "Cannot find the specified employee!" << endl;
    }

    return false;  // Employee not found or key not added
}

bool returnAKey(Employee employees[], int nEmployees, string emp_name, string returnKey) {
    bool employeeFound = false;
    int keyIdx = -1;

    // Search for the employee
    for (int i = 0; i < nEmployees; ++i) {
        if (employees[i].name == emp_name) {
            employeeFound = true;

            // Search for the key in the employee's keys
            for (int j = 0; j < employees[i].nKeysPossessed; j++) {
                if (employees[i].keys[j] == returnKey) {
                    keyIdx = j;
                    break;  // Key found
                }
            }

            if (keyIdx != -1) {
                // Remove the key by shifting elements to the left
                for (int j = keyIdx; j < employees[i].nKeysPossessed - 1; ++j) {
                    employees[i].keys[j] = employees[i].keys[j + 1];
                }
                
                employees[i].nKeysPossessed--;  // Decrement key count
                cout << "Key returned successfully." << endl;
                return true;  // Key successfully removed
            } 
            else {
                cout << "This employee does not have the specified key!" << endl;
                return false;  // Key not found
            }
        }
    }

    if (!employeeFound) {
        cout << "Cannot find the specified employee!" << endl;
    }

    return false;  // Employee not found
}



int main() {

    int nEmployees = 0;
    const int ARR_VAL = 10;
    Employee empArr[ARR_VAL];

    string inputfile;
    string outputfile;
    
    cout << "Please enter key file name to start: ";
    cin >> inputfile;
    //inputfile = "keys1.txt";
    outputfile = "keysOutput.txt";

    reader(inputfile, empArr, nEmployees);
    if (!reader(inputfile, empArr, nEmployees)) {
        cout << "File not found, exiting the program..." << endl;
        exit(1);
    }
    int option;   
    do {
        cout << "Please select from the following options: " << endl;
        cout << "  1. show all employees and their keys" << endl;
        cout << "  2. show the keys an employee possesses" << endl;
        cout << "  3. show which employees possess a specific key" << endl;
        cout << "  4. add a key to an employee" << endl;
        cout << "  5. return a key by an employee" << endl;
        cout << "  6. save the current key status" << endl;
        cout << "  7. exit the program" << endl;
        cin >> option;
        if (option == 1) {
            for (int i = 0; i < nEmployees; ++i) {
                cout << "Name: " << empArr[i].name << endl;
                cout << "Keys possessed: ";
                for (int j = 0; j < empArr[i].nKeysPossessed; ++j) {
                    cout << empArr[i].keys[j] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        else if (option == 2) {
            string name;
            bool foundName = false;
            cin.ignore();
            cout << "Please enter employee's name: ";
            getline(cin, name);
            for (int i = 0; i < nEmployees; ++i) {
                if (empArr[i].name == name) {
                    foundName = true;
                    cout << empArr[i].name << " possess the following keys: ";
                    for (int j = 0; j < empArr[i].nKeysPossessed; ++j) {
                        cout << empArr[i].keys[j] << " ";
                    }
                    cout << endl;
                    cout << endl;
                }
            }
            if(!foundName) {
                cout << "Cannot find the specified employee!" << endl;
                cout << endl;
            }
        }
        else if (option == 3) {
            bool keyFound = false;
            cout << "Please enter a key: ";
            string key;
            cin.ignore();
            cin >> key;

            for(int i = 0; i < nEmployees; ++i) {
                for (int j = 0; j < empArr[i].nKeysPossessed; ++j) {
                        if (empArr[i].keys[j] == key) {
                            keyFound = true;
                            cout << empArr[i].name << ", ";
                        }
                    }
            }
            if (keyFound) {
                cout << "possess this key." << endl;
                cout << endl;
            }
            else {
                cout << "No one possesses this key." << endl;
                cout << endl;
            }
        }
        else if (option == 4) {
            string name;
            string key;
            cin.ignore();
            cout << "Please enter employee's name: ";
            getline(cin, name);
            cout << "Please enter a new key: ";
            cin >> key;
            addKeyForEmployee(empArr, nEmployees, name, key);
            cout << endl;
        }
        else if (option == 5) {
            string name;
            string key;
            cin.ignore();
            cout << "Please enter employee's name: ";
            getline(cin, name);
            cout << "Please enter the returned key: ";
            cin >> key;
            returnAKey(empArr, nEmployees, name, key);
            cout << endl;
        }
        else if (option == 6) {
            string filename;
            cout << "Please enter output file name: ";
            cin >> filename;
            writer(filename, empArr, nEmployees);
        }
        else if (option == 7) {
            writer("keys_updated.txt", empArr, nEmployees);
            cout << "Thank you for using the system! Goodbye!" << endl;
            exit(1);
        }
        else {
            cout << "Not a valid option. Please try again." << endl;
            cout << endl;
        }
        
    } while(option != 7);

    return 0;
}
