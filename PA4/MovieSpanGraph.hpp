/*
*Name:Xinyu Qian, Fangfei Huo
*date:2015.3.9
*cse 100 assignment 4
*
* a class for moviespan containing all the disjoint sets and movie-actor relationships
*
* Description of its member:
* unordered_map actor_map: a hash table contains maps all the actors to its index
* unordered_map movie_map: a hash table contains all names of movies appeared in the input file and the pointers to Movie, 
*                         the key for hash table is movie name, and the content is Movie*
* vector<int>actorSet: the vector representing the disjoint set of actors
* vector<int>actorSetSize: the vector indicating the size(weight) of each disjoint set
* vector<Movie*>unincludedMovie: the vector of all the movies that are not selected for the movie cover
* int setNum: the total number of disjoint actor sets
*
* bool loadFromFile: load data from input files, return true if successfully loaded, otherwise return false
* int getRoot(int a): return the root of an actor,path compression included, i.e. return which disjoint set the actor is in
* void unionSet(int a, int b): union two disjoint sets
*             
*/
#ifndef MOVIESPANGRAPH_HPP
#define MOVIESPANGRAPH_HPP
#include <string>
#include <iostream>
#include "Movie.hpp"
#include <unordered_map>
#include <vector>

using namespace std;

class MovieSpanGraph {
public:
  MovieSpanGraph(void);

  unordered_map<string,int> actor_map;
  unordered_map<string,Movie*> movie_map;
  vector<int>actorSet;
  vector<int>actorSetSize;
  vector<Movie*>unincludedMovie;
  int setNum = 0;
    
  //load data from input files, return true if successfully loaded, otherwise return false
  bool loadFromFile(const char* in_filename);
  
  //return the root of an actor, path compression included, i.e. return which disjoint set the actor is in like find()
  int getRoot(int a);
  
  //union two disjoint sets
  void unionSet(int a, int b);
  
  ~MovieSpanGraph() { 
    for (auto it = movie_map.begin(); it != movie_map.end(); ++it){
		delete it->second;
	}
  }
  
};


#endif // MOVIESPANGRAPH_HPP
