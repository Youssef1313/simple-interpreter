#include <iostream>
#include <string>
#include "Interpretation.h"
#include "FileReader.h"

using namespace std;

int main() {
    Interpretation interpretation;
    try {
        FileReader reader("D:\\Src.txt");
        while (true)
            interpretation.process(reader.readNextLine());
    } catch (string ex) {
        if (ex != "End of file") cout << ex << endl;
    }
    auto map = interpretation.getVariables();
    for (auto variable : map) {
        cout << variable.first << " = " << to_string(variable.second) << endl;
    }
    return 0;
}
