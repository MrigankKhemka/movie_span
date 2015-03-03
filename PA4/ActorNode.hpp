/*
*Name:Xinyu Qian, Fangfei Huo
*date:2015.3.1
*cse 100 assignment 4
*a class for actor and node and edge
*since actor and node have a one-to-one correspondence so use a single class to describe them both
*we give every node a hash table to contain its adjacent nodes and the movie representing the node
*so edge is also represented in this class
*
* Description of its member:
* name: actor's name
* priority_queue movie: all movies which the actor took part in, which are 
*                       placed in a priority queue in which the lower weight has higher priority
* unordered_map adjacent(edges): a hash table contains all its adjacent nodes and the edge(movie) connecting them, 
*                         the key for hash table is ActorNode*, and the content is Movie*
* dist,done,pre: the distance,done flag and previous node pointer used in Dijkstra's algorithm
* compMovie: the compare operator used in the priority queue of movie
* 
* initialize: set the name as the input actor name 
*             set dist=60000, done=false, pre=NULL to meet Dijkstra's algorithm's requirement
*/
#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include "Movie.hpp"

using namespace std;
/*the compare operator used in the priority queue of movie
* the lower weight movie has higher priority
*/
		  class compMovie{
		    public: 
		          bool operator()(Movie*& one, Movie*& other){
				  return (one->weight) > (other->weight);
			  }
		  };
		  
		  class ActorNode {

		  public:
		      /*the actor's name*/
			  string name;
			  
			  /*all movies which the actor took part in, which are 
               *placed in a priority queue in which the lower weight has higher priority
			   */
			  priority_queue<Movie*, vector<Movie*>, compMovie> movie;
			  
			  /*a hash table contains all its adjacent nodes and the edge(movie) connecting them, 
               *the key for hash table is ActorNode*, and the content is Movie*
			   */
			  unordered_map<ActorNode*, Movie*> adjacent;
			  
			  /*the distance,done flag and previous node pointer used in Dijkstra's algorithm			  
			  */
			  int dist;
			  bool done;
			  ActorNode* pre;

			  /* initialize: set the name as the input actor name 
              *set dist=60000, done=false, pre=NULL to meet Dijkstra's algorithm's requirement
              */
			  ActorNode(string name) :name(name), dist(60000), done(false),pre(NULL){};
		  };
#endif // ACTORNODE_HPP
