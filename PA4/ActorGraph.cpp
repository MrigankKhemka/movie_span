/*
 * ActorGraph.cpp
 * Author: Adrian Guthals
 * Date: 2/24/2015
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "Movie.hpp"

using namespace std;

ActorGraph::ActorGraph(void) {}


bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges)
{

	// Initialize the file stream
	ifstream infile(in_filename);

	bool have_header = false;

	// keep reading lines until the end of file is reached
	while (infile)
	{
		string s;
		Movie* movie;
		// get the next line
		if (!getline(infile, s)) break;

		if (!have_header)
		{
			// skip the header
			have_header = true;
			continue;
		}

		istringstream ss(s);
		vector <string> record;

		while (ss)
		{
			string next;

			// get the next string before hitting a tab character and put it in 'next'
			if (!getline(ss, next, '\t')) break;

			record.push_back(next);
		}

		if (record.size() != 3)
		{
			// we should have exactly 3 columns
			continue;
		}

		string actor_name(record[0]);
		string movie_title(record[1]);
		int movie_year = stoi(record[2]);

		// we have an actor/movie relationship, now what?
		if (actor_map.find(actor_name) == actor_map.end()) {
			ActorNode* actor = new ActorNode(actor_name);
			actor_map.emplace(actor_name, actor);
		}
		if (movie_map.find(movie_title) == movie_map.end()) {
			if (use_weighted_edges){
				movie = new Movie(movie_title, movie_year, 2015 - movie_year + 1);
				movie_map.emplace(movie_title, movie);
			}
			else{
				movie = new Movie(movie_title, movie_year, 1);
				movie_map.emplace(movie_title, movie);
			}
		}

		actor_map[actor_name]->movie.push(movie);
		movie_map[movie_title]->cast.push_back(actor_name);
	}

	if (!infile.eof())
	{
		cerr << "Failed to read " << in_filename << "!\n";
		return false;
	}
	infile.close();

	return true;
}

void ActorGraph::createGraph(){
	for (auto& x : actor_map){
		Movie* movie_cur;
		movie_cur = x.second->movie.top();
		x.second->movie.pop();

		for (int i = 0; i < (movie_cur->cast.size()); i++){
			if (x.second->adjacent.find(actor_map[movie_cur->cast[i]]) == x.second->adjacent.end()
				&& actor_map[movie_cur->cast[i]] != x.second){
				x.second->adjacent[actor_map[movie_cur->cast[i]]] = movie_cur;
			}
		}
	}
}
