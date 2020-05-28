#include <iostream>
#include <string>
#include "Interpretation.h"
#include "FileReader.h"
#include "SortVariables.h"

using namespace std;

int main() {
    Interpretation interpretation;

    try {
        FileReader reader("Src.txt");
        while (true){
            interpretation.process(reader.readNextLine());
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


