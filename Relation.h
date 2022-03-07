#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Relation {

    private:
        string name;
        Scheme mainScheme;
        set<Tuple> tuples;

    public:

        Relation();

        Relation(string inputName, Scheme inputScheme) {
            name = inputName;
            mainScheme = inputScheme;
        }

        Relation(string inputName, Scheme inputScheme, set<Tuple> listTuple) {
            name = inputName;
            mainScheme = inputScheme;
            tuples = listTuple;
        }

        string getName() {
            return name;
        }

        void addTuple(const Tuple& tuple) {
            tuples.insert(tuple);
        }

        int getNumberTuples() {
            return tuples.size();
        }

        string toString() const {
            stringstream out;
            set<Tuple>::iterator itr;
            for (itr = tuples.begin(); itr != tuples.end(); itr++) {
                out << "  " << (*itr).toString(mainScheme) << endl;
            }
            return out.str();
        }

        Relation select(int index, const string& value) const {
            Relation result(name, mainScheme);
            set<Tuple>::iterator itr;
            for (itr = tuples.begin(); itr != tuples.end(); itr++) {
                if ((*itr).at(index) == value) {
                    result.addTuple((*itr));
                }
            }    
            return result;    
        }

        Relation select(int index1, int index2) const {
            Relation result(name, mainScheme);
            set<Tuple>::iterator itr;
            for (itr = tuples.begin(); itr != tuples.end(); itr++) {
                if ((*itr).at(index1) == (*itr).at(index2)) {
                    result.addTuple((*itr));
                }
            }
            return result;
        }

        Relation project(vector<int> indexes) const {

            Scheme newestScheme = mainScheme;
            newestScheme.rearrangeName(indexes);
            Relation result(name, newestScheme);

            set<Tuple>::iterator itr;
            for (itr = tuples.begin(); itr != tuples.end(); itr++) {
                vector<string> newestTuple;
                for (unsigned i = 0; i < indexes.size(); i++) {
                    newestTuple.push_back((*itr).at(indexes[i]));
                }
                Tuple newTuple(newestTuple);
                result.addTuple(newTuple);
            }
            return result;
        }

        Relation rename(vector<string> newNames) const {
            Scheme newScheme(newNames);
            Relation result(name, newScheme, tuples);
            return result;          
        }



};