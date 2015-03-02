#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include "Movie.hpp"

using namespace std;
		  class compMovie{
		    public: 
		          bool operator()(Movie*& one, Movie*& other){
				  return (one->weight) < (other->weight);
			  }
		  };
		  
		  class ActorNode {

		  public:
			  string name;
			  priority_queue<Movie*, vector<Movie*>, compMovie> movie;
			  unordered_map<ActorNode*, Movie*> adjacent;
			  int dist;
			  bool done;
			  ActorNode* pre;

			  ActorNode(string name) :name(name), dist(60000), done(false),pre(NULL){};
		  };
#endif // ACTORNODE_HPP
