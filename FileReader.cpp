#include <stdio.h>
#include "FileReader.h"

FileReader::FileReader(string filePath) {
    file.open(filePath);
    if (file.fail()) {
        throw "File cannot be read.";
    }

}

string FileReader::readNextLine() {
    if (!file.eof()) {
        string line;
        getline(file, line);
        return line;
    }
    file.close();
    throw "End of file";
}
