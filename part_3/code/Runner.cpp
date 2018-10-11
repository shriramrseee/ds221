/**
 * Created by: Shriram R.
 * Roll No: 06-02-01-10-51-18-1-15763
 */

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <list>
#include <queue>
#include <sstream>
#include"DictImpl.cpp"

using namespace std;

// Load an input file into a dictionary
double insert_dict(char *input_file, IDictionary *dic, int &count) {
    ifstream input;
    string t;
    int key;
    char *value;
    struct timespec start, end;
    double insert_time = 0;
    // Open the file
    input.open(input_file);
    if (!input.is_open()) {
        throw invalid_argument(string("Input file does not exist!"));
    }
    // Load data into the dictionary
    try {
        while(!input.eof()) {
            input >> t;
            key = stoi(t); // Get the key
            count++;
            t = "";
            getline(input, t);
            t.replace(0,1,"");
            value = new char[t.length() + 1];
            strcpy(value, t.c_str());
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); // Start timer
            dic->insert(key, value); // Insert the Key value pair
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); // End timer
            insert_time += (end.tv_nsec - start.tv_nsec) / 1000000.0 + (end.tv_sec - start.tv_sec) * 1000;
        }            
    }        
    catch (const invalid_argument &ia) {
        if(!input.eof())
            throw invalid_argument(string("Input file has invalid characters or format!"));
    }
    // Close the file
    input.close();
    return insert_time;
}

// Initialize an hash based dictionary
IDictionary *init_hash(int capacity) {
    IDictionary *dic = new HashTableImpl(capacity);
    return dic;
}

// Initialize an array based dictionary
IDictionary *init_arr(int capacity) {
    IDictionary *dic = new ArrayDictImpl(capacity);
    return dic;
}

// Initialize an hash based dictionary
IDictionary *init_bin(int capacity) {
    IDictionary *dic = new BSearchDictImpl(capacity);
    return dic;
}

// Lookup values in the dictionary and write it to a file
double lookup_dict(char *lookup_file, IDictionary *dic, char *output_file, int &count) {
    ifstream lookup;
    ofstream output;
    struct timespec start, end;
    double lookup_time = 0;
    int key;
    string t;
    char *value;
    // Open the lokkup and output files
    lookup.open(lookup_file);
    if (!lookup.is_open()) {
        throw invalid_argument(string("Lookup file does not exist!"));
    }
    output.open(output_file);
    if (!output.is_open()) {
        throw invalid_argument(string("Output file does not exist!"));
    }
    // Lookup and Write the data to the file
    try {
        while(!lookup.eof()) {
            t = "";
            lookup >> t;
            key = stoi(t); // Get the key
            count++;
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); // Start timer
            value = dic->lookup(key);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); // End timer
            lookup_time += (end.tv_nsec - start.tv_nsec) / 1000000.0 + (end.tv_sec - start.tv_sec) * 1000;
            output << key << "\t" << value << "\n"; 
        }
    }
    catch (const invalid_argument &ia) {
        if(!lookup.eof())
            throw invalid_argument(string("Lookup file has invalid characters or format!"));
    }
    // Close the files
    lookup.close();
    output.close();

    return lookup_time;
}

// Loads a dictionary with the input data, searches for different keys and writes the output to a file
void load(char *dic_type, char *capacity, char *input_file, char* lookup_file, char *output_file) {

    IDictionary *dic;
    double insert_time, lookup_time;
    char *value;
    int insert_count = 0;
    int lookup_count = 0;
    struct timespec start, end;

    if (strcmp("hash", dic_type) == 0) {        
        dic = init_hash(atoi(capacity));        
    } else if (strcmp("array", dic_type) == 0) {        
        dic = init_arr(atoi(capacity));        
    } else if (strcmp("bsearch", dic_type) == 0) {        
        dic = init_bin(atoi(capacity));        
    } else
        cout << "[load] invalid dictionary type input seen: " << dic_type << endl;
    
    insert_time = insert_dict(input_file, dic, insert_count); 

    if (strcmp("bsearch", dic_type) == 0) {        
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); // Start timer
        ((BSearchDictImpl *)dic)->sort();
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); // End timer
        insert_time += (end.tv_nsec - start.tv_nsec) / 1000000.0 + (end.tv_sec - start.tv_sec) * 1000;
    }   

    lookup_time = lookup_dict(lookup_file, dic, output_file, lookup_count);

    // Print time taken in milliseconds to stdout
    cout << dic_type << "," << insert_count << "," << insert_time << "," << lookup_count << "," << lookup_time << "\n";
    return;
}

int main(int n, char *argv[]) {
    
    load(argv[1], argv[2], argv[3], argv[4], argv[5]);
    return 0;

}



