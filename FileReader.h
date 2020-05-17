#ifndef SIMPLE_INTERPRETER_FILEREADER_H
#define SIMPLE_INTERPRETER_FILEREADER_H

#include <string>
#include <fstream>

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
    ifstream file;
public:
    FileReader(string filePath);
    string readNextLine();
};


#endif //SIMPLE_INTERPRETER_FILEREADER_H
