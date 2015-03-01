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
                pathfinder(actor_name1,actor_name2,ActorGraph G);
		// we have an actor/movie relationship, now what?
               
            
   

void pathfinder(string &actor_name1,string &actor_name2,ActorGraph G){

     string from = actor_name1;
     string to = actor_name2;
      queue<ActorNode*> q;
      ActorNode* start;
      ActorNode* head;
      //unordered_map<ActorNode*, Movie*> adjacent
      start->name = actor_name1;
      start-dist = 0;
      start->pre = -1;
      q.push(start);
 while(!q.empty()){
     head = q.top();
     q.pop();
   if(head->done){
    continue;}
   else{
    head->done = true;
    //adjacent_map = head->adjacent;
    for (auto it = head->adjacent.begin();it!=head->adjacent.end();++it){
        new_dist = head->dist + (it->second->weight);
        if(new_dist < it->first->dist){
          it->first->dist = new_dist; 
          it->first->pre = head;
          q.push(it);
          if(it->first->name==to&&it->first->done==true){ 
          writepath(string &from, string &to,ofstream& out);
           }


        }
     }
   }
 }
}

int writepath(string &from, string &to,ofstream& out){
    ActorNode *cur;
    ActorNode *start;
    cur->name = to;
    start->name = from;
    vector<unsigned char> v;
       while(cur!=start){
           v.push_back(cur->name);
           for(auto it = cur->adjacent.begin();it->first!=cur->prev;++it){
           if(it->first=cur->prev)
             v.push_back(it->second);
              cur = cur->prev;
           }
          }
         v.push_back(cur->name);

    for(int i=v.size()-1;i>=0;i--){
      out.put(v[i]);
      }
        
  }



   




