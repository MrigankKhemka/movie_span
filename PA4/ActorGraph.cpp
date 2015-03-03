/*
*Name:Xinyu Qian, Fangfei Huo
*date:2015.3.1
*cse 100 assignment 4
*Implement the class ActorGraph,which actor are the nodes of the graph, 
*the movies which are casted by actor pairs are the edges between these two actors 
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
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "Movie.hpp"
#include <unordered_map>

using namespace std;

ActorGraph::ActorGraph(void) {}

void ActorGraph::MakeUpdate(){
 for (auto it = actor_map.begin(); it != actor_map.end(); ++it){
       it->second->dist=60000;
       it->second->pre=NULL;
       it->second->done=false;
   }
}

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
			continue;
		}

		string actor_name(record[0]);
		string movie_index(record[1]+record[2]);
		int movie_year = stoi(record[2]);
                string movie_title = record[1];


               /*check if the read in actor_name has been saved in the actor_map, if not, insert it to the actor_map*/
		if (actor_map.find(actor_name) == actor_map.end()) {
			ActorNode* actor = new ActorNode(actor_name);
			actor_map.emplace(actor_name, actor);
		}

  
              /*check if the read in movie_index has been saved in the movie_map, if not, insert it to the movie_map*/
		if (movie_map.find(movie_index) == movie_map.end()) {
			if (use_weighted_edges){
				movie = new Movie(movie_index, movie_year, 2015 - movie_year + 1, movie_title);
                               
				movie_map.emplace(movie_index, movie);
			}
			else{
				movie = new Movie(movie_index, movie_year, 1, movie_title);
                        
				movie_map.emplace(movie_index, movie);
			}
		}
		else{  
			movie = movie_map[movie_index];
		}
                /*push movie to the  priority_queue of the ActorNode named in actor_name in the actor_map*/
                /*push actor_name to the cast vector of the Movie named in movie_index in the movie_map*/
		actor_map[actor_name]->movie.push(movie);
		movie_map[movie_index]->cast.push_back(actor_name);
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
		while (x.second->movie.size()>=1){
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
}
