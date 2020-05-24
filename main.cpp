#include <iostream>
#include <string>
#include "Interpretation.h"
#include "FileReader.h"
#include "Statements/IfStatement.h"

using namespace std;

int main() {

    Interpretation interpretation;
    try {
        FileReader reader("D:\\Src.txt");
        while (true)
            interpretation.process(reader.readNextLine());
    } catch (string ex) {
        if (ex != "End of file") cout << ex << endl;
    } catch (char const* ex) {
        cout << ex << endl;
    }
    auto map = interpretation.getVariables();
    for (auto variable : map) {
        cout << variable.first << " = " << variable.second.toString() << endl;
    }

    return 0;
}
