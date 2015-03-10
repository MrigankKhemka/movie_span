/*
*Name:Xinyu Qian, Fangfei Huo
*date:2015.3.8
*cse 100 assignment 4
*
* a class for moviespan containing all the disjoint sets and movie-actor relationships
*
* bool loadFromFile: load data from input files, return true if successfully loaded, otherwise return false
* int getRoot(int a): return the root of an actor,path compression included, i.e. return which disjoint set the actor is in
* void unionSet(int a, int b): union two disjoint sets
*    
*/
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "MovieSpanGraph.hpp"

using namespace std;

MovieSpanGraph::MovieSpanGraph(void) {}

//load data from input files, return true if successfully loaded, otherwise return false
bool MovieSpanGraph::loadFromFile(const char* in_filename)
{
	// Initialize the file stream
	ifstream infile(in_filename);

	bool have_header = false;

	int actorIndex = 0;
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
			continue;
		}

		string actor_name(record[0]);
		string movie_index(record[1]+record[2]);
		int movie_year = stoi(record[2]);
        string movie_title = record[1];


        /*check if the read-in actor_name has been saved in the actor_map, if not, insert it to the actor_map
		   set the initial size of each set as 1*/
		if (actor_map.find(actor_name) == actor_map.end()) {
			actor_map.emplace(actor_name, actorIndex);
			actorSet.push_back(actorIndex);
			actorSetSize.push_back(1);
			actorIndex++;
		}

         /*check if the read-in movie_index has been saved in the movie_map, if not, insert it to the movie_map
		 and the unincludedMovie*/
		if (movie_map.find(movie_index) == movie_map.end()) {
				movie = new Movie(movie_index, movie_year, 1, movie_title);
				movie_map.emplace(movie_index, movie);
				unincludedMovie.push_back(movie);
		}
		else{  
			movie = movie_map[movie_index];
		}
             
        /*push actor_name to the cast vector of the Movie named in movie_index in the movie_map*/
		movie_map[movie_index]->cast.push_back(actor_name);
	}
	
	//set the initial total set number
	setNum = actorIndex;
	if (!infile.eof())
	{
		cerr << "Failed to read " << in_filename << "!\n";
		return false;
	}
	infile.close();

	return true;
}

//return the root of an actor,path compression included, i.e. return which disjoint set the actor is in
int MovieSpanGraph::getRoot(int a){
  int cur =a;
  
  
  while(cur != actorSet[cur]){
    cur = actorSet[cur];
	
	// if the root of an actor is not the actor itself set its root as it's grandparent
	actorSet[cur] = actorSet[actorSet[cur]];
  }
  return cur;
}

//union two disjoint sets
void MovieSpanGraph::unionSet(int a, int b){
  int rootA = getRoot(a);
  int rootB = getRoot(b);
  
  //do nothing if two actors are in the same set
  if (rootA == rootB);
  else if(actorSetSize[rootA]<actorSetSize[rootB]){
    actorSet[rootA] = rootB;
    actorSetSize[rootB]+= actorSetSize[rootA];
	setNum--;
  }
  else{
    actorSet[rootB] = rootA;
    actorSetSize[rootA]+=actorSetSize[rootB];
	setNum--;
  }
}

