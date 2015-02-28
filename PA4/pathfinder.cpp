#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ActorGraph.hpp"
using namespace std

int main(int argc, char** argv){
	//string data = argv[1];
	char ifweighted = argv[2];
	string findpair = argv[3];
	string output = argv[4];
	ActorGraph graph;

	if (ifweighted == 'u')
		graph.loadFromFile(argv[1], false);
	else if (ifweighted == 'w')
		graph.loadFromFile(argv[1], false);

	graph.createGraph();


	bool have_header = false;
	ifstream infile(findpair, ios::in);

	// keep reading lines until the end of file is reached
	while (infile)
	{
		string s;

		// get the next line
		if (!getline(infile, s)) break;

		if (!have_header){
			// skip the header
			have_header = true;
			continue;
		}

		istringstream ss(s);
		vector <string> record;

		while (ss){
			string next;

			// get the next string before hitting a tab character and put it in 'next'
			if (!getline(ss, next, '\t')) break;

			record.push_back(next);
		}

		if (record.size() != 2){
			// we should have exactly 2 columns
			continue;
		}

		string actor_name1(record[0]);
		string actor_name2(record[1]);
		// we have an actor/movie relationship, now what?

	}