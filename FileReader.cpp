#include <stdio.h>
#include <string>
#include "FileReader.h"

using namespace std;

FileReader::FileReader(string filePath) {
    file.open(filePath);
    if (file.fail()) {
        throw string("File cannot be read.");
    }

}

string FileReader::readNextLine() {
    if (!file.eof()) {
        string line;
        getline(file, line);
        return line;
    }
    file.close();
    throw string("End of file");
}
