//
// Created by Youssef on 16/05/2020.
//

#ifndef SIMPLE_INTERPRETER_FILEREADER_H
#define SIMPLE_INTERPRETER_FILEREADER_H

#include <string>

using namespace std;

/*
 * The caller must be allowed to do:
 *
 * FileReader reader("Src.txt");
 * string line;
 * while ((line = reader.readNextLine()) != NULL) {
 *     // Do whatever with the line.
 * }
 */
class FileReader {
private:
    // TODO: some field to track where we're on the file. (Perhaps, a file pointer?)
public:
    FileReader(string filePath);
    string readNextLine();
};


#endif //SIMPLE_INTERPRETER_FILEREADER_H
