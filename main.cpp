#include <iostream>
#include <string>
#include "Interpretation.h"
#include "FileReader.h"
#include "SortVariables.h"
#include "Statements/IfStatement.h"

using namespace std;

int main() {
    Interpretation interpretation;
//    unordered_map<string, Value> myMap;
//    try {
//        IfStatement ifStatement("if 2 < 3: x = 5", &myMap);
//    } catch (string ex) {
//        cout << "Shouldn't be printed: " << ex << endl;
//    }
    try {
        FileReader reader("file.txt");
        while (true){
            string line = reader.readNextLine();
            interpretation.process(line);
        }
    } catch (string ex) {
        if (ex != "End of file")
            cout << ex << endl;
        else
            sortVariables(interpretation.getVariables());
    } catch (char const *ex) {
        cout << ex << endl;
    }

    return 0;
}


