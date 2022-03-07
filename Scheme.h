#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Scheme {

    private:
        vector<string> names;

    public:
        Scheme() {}
        Scheme(vector<string> inputNames) {
            names = inputNames;
        }

        void changeName(int position, string name) {
            if (position < names.size()) {
                names[position] = name;
            }
        }

        void rearrangeName(vector<int> inputVainas) {
            vector<string> newNameVector;

            for (int i = 0; i < inputVainas.size(); i++) {
                newNameVector.push_back(names[inputVainas[i]]);
            }
            names = newNameVector;
        }

        unsigned const getSize() {
            return names.size();
        }
        const string& at(int index) const {
            return names[index];
        }
};
