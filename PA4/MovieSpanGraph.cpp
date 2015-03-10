/*
*Name:Xinyu Qian, Fangfei Huo
*date:2015.3.1
*cse 100 assignment 4
*
*Implement the class ActorGraph,which actor are the nodes of the graph, 
*the movies which are casted by actor pairs are the edges between these two actors 
*
* Description of its member:
* createGraph():a function used to build the directed edges between all ActorNodes between every ActorNode pairs who appeared in the same movie , 
* we stored the least weighted movies between actor-pairs to in each ActorNode's adjacent map.
* MakeUpdate(): a function used to update the dist, pre,done of each ActorNode in the ActorGraph after one search for an actor-pair 
*             
*/
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "MovieSpanGraph.hpp"

using namespace std;

MovieSpanGraph::MovieSpanGraph(void) {}


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


               /*check if the read in actor_name has been saved in the actor_map, if not, insert it to the actor_map*/
		if (actor_map.find(actor_name) == actor_map.end()) {
			actor_map.emplace(actor_name, actorIndex);
			actorSet.push_back(actorIndex);
			actorSetSize.push_back(1);
			actorIndex++;
		}

              /*check if the read in movie_index has been saved in the movie_map, if not, insert it to the movie_map*/
		if (movie_map.find(movie_index) == movie_map.end()) {
				movie = new Movie(movie_index, movie_year, 1, movie_title);
				movie_map.emplace(movie_index, movie);
				unincludedMovie.push_back(movie);
		}
		else{  
			movie = movie_map[movie_index];
		}
                /*push movie to the  priority_queue of the ActorNode named in actor_name in the actor_map*/
                /*push actor_name to the cast vector of the Movie named in movie_index in the movie_map*/
		movie_map[movie_index]->cast.push_back(actor_name);
	}
		setNum = actorIndex;
	if (!infile.eof())
	{
		cerr << "Failed to read " << in_filename << "!\n";
		return false;
	}
	infile.close();

	return true;
}

int MovieSpanGraph::getRoot(int a){
  int cur =a;
  while(cur != actorSet[cur]){
    actorSet[cur] = actorSet[actorSet[cur]];
    cur = actorSet[cur];
  }
  return cur;
}

void MovieSpanGraph::unionSet(int a, int b){
  int rootA = getRoot(a);
  int rootB = getRoot(b);
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

