#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <queue>
#include <vector>
#include <unordered_map>

protected:using namespace std;

class ActorNode {
  
public:
  string name;
  priority_queue<Movie*, vector<Movie*>, comp> movie;
  unordered_map<ActorNode*,Movie*> adjacent;
  int dist;
  bool done;
  Node* pre;
  
  ActorNode(string name):name(name),dist(0),done(false){};

  
};
#endif // ACTORNODE_HPP