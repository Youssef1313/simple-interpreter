#include <iostream>
#include <string>
#include "Evaluation/ExpressionEvaluator.h"

using namespace std;

int main() {
//    FileReader reader("Src.txt");
//    Interpretation compilation;
//    string line;
//    while (line = reader.readLine()) {
//        Variable variable = compilation.process(line);
//        /*
//         * Internally, the process method will parse the instruction, evaluate the expression, and
//         * return the variable name and its value (Variable can be a struct).
//         */
//        // TODO: Add the variable to BST and heap.
//
//    }
    while (true) {
        cout << "> ";
        string line;
        getline(cin, line);
        unordered_map<string, double> map;
        ExpressionEvaluator eval(line, map);
        try {
            double result = eval.evaluate();
            cout << "The result is: " << result << endl << endl;
        } catch (const char *e) {
            cout << e << endl;
        } catch (string e) {
            cout << e << endl;
        }


    }

    return 0;
}
