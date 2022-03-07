#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include "DatalogProgram.h"
#include "Relation.h"

using namespace std;


class Database {

    private:
        DatalogProgram data;
        vector<Relation> relations;

    public:

        Database(DatalogProgram dataInput, vector<Relation> relationInput) {
            data = dataInput;
            relations = relationInput;
        }  

        void evaluateSchemes() {
            vector<Predicate> schemes = data.getSchemeList();
            for (unsigned i = 0; i < schemes.size(); i++) {
                string name = schemes[i].getName();
                vector<string> inputNames;
                inputNames = schemes[i].getStringVector();
                Relation newestRelation(name, inputNames);
                relations.push_back(newestRelation);
            }
        }

        void evaluateFacts() {
            vector<Predicate> facts = data.getFactList();
            for (unsigned i = 0; i < facts.size(); i++) {
                string name = facts[i].getName();
                vector<string> inputFact;
                inputFact = facts[i].getStringVector();
                Tuple newestTuple(inputFact);
                for (unsigned k = 0; k < relations.size(); k++ ) {
                    if (name == relations[k].getName()) {
                        relations[k].addTuple(newestTuple);
                    }
                }
            }
        }



        void evaluateQueries() {
            vector<Predicate> queries = data.getQueryList();
            for (unsigned i = 0; i < queries.size(); i++) {
                string schemeName = queries[i].getName();
                for (unsigned k = 0; k < relations.size(); k++) {
                    if (schemeName == relations[k].getName()) {
                        vector<Parameter> parameters = queries[i].getVector();
                        Relation newRelation = relations[k];
                        vector<int> projectionIndexes;
                        vector<string> newNames;
                        bool moreThanOne = false;
                        map <string, int> constants;
                        for (unsigned p = 0; p < queries[i].getVector().size(); p ++) {
                            char newChar = '\'';
                            if (parameters[p].toString().at(0) == newChar) {
                                newRelation = newRelation.select(p, parameters[p].toString());
                            } else {
                                bool found = false;
                                map<string, int>::iterator itr;
                                for (itr = constants.begin(); itr != constants.end(); itr++) {
                                    if (parameters[p].toString() == itr->first) {
                                        found = true;
                                        newRelation = newRelation.select(p, itr->second);
                                    }
                                }
                                if (found == false) {
                                    projectionIndexes.push_back(p);
                                    newNames.push_back(parameters[p].toString());
                                    constants.insert(pair<string, int>(parameters[p].toString(), p));
                                    moreThanOne = true;
                                }
                            }
                        }
                        newRelation = newRelation.project(projectionIndexes);
                        newRelation = newRelation.rename(newNames);
                        printOutQuery(newRelation, queries[i], moreThanOne);
                    }
                }
            }
        }

         void printOutQuery(Relation relate, Predicate localQuery, bool moreThanOne) {
            if (relate.getNumberTuples() == 0) {
                cout << localQuery.toString() << "? " << "No" << endl;
            } else {
                cout << localQuery.toString() << "? "  << "Yes(" << relate.getNumberTuples() << ")" << endl;
                if (moreThanOne)
                    cout << relate.toString();
            }
        }


};