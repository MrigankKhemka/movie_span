/*
*Name:Xinyu Qian, Fangfei Huo
*date:2015.3.1
*cse 100 assignment 4
*
*a class for ActorGraph,which actor are the nodes of the graph, 
*the movies which are casted by actor pairs are the edges between these two actors 
*
* Description of its member:
* unordered_map actor_map: a hash table contains all names of actors appeared in the input file and the pointers to those ActorNodes, 
*                         the key for hash table is actor name, and the content is ActorNode*
* unordered_map movie_map: a hash table contains all names of movies appeared in the input file and the pointers to Movie, 
*                         the key for hash table is movie name, and the content is Movie*
* createGraph():a function used to build the directed edges between all ActorNodes between every ActorNode pairs who appeared in the same movie
* we stored the least weighted movies between actor-pairs to in each ActorNode's adjacent map.
* MakeUpdate(): a function used to update the dist, pre of each ActorNode in the ActorGraph after one search for an actor-pair 
*             
*/
#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP
#include <string>
#include <iostream>
#include "ActorNode.hpp"
#include "Movie.hpp"
#include <unordered_map>

// Maybe include some data structures here

using namespace std;

class ActorGraph {
public:
  ActorGraph(void);

  // Maybe add some more methods here
  unordered_map<string,ActorNode*> actor_map;
  unordered_map<string,Movie*> movie_map;
  
  /** You can modify this method definition as you wish
   *
   * Load the graph from a tab-delimited file of actor->movie relationships.
   *
   * in_filename - input filename
   * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
   *
   * return true if file was loaded sucessfully, false otherwise
   */
  bool loadFromFile(const char* in_filename, bool use_weighted_edges);
  
  //used to build the directed edges between all ActorNodes 
  //between every ActorNode pairs who appeared in the same movie
  void createGraph();
  
  // a function used to update the dist, pre of each ActorNode 
  //in the ActorGraph after one search for an actor-pair 
  void MakeUpdate();
  
  ~ActorGraph() { 
      for (auto it = actor_map.begin(); it != actor_map.end(); ++it){
		delete it->second;
	}
      for (auto it = movie_map.begin(); it != movie_map.end(); ++it){
		delete it->second;
	}
  }
  
};


#endif // ACTORGRAPH_HPP
