/*
*Name:Xinyu Qian, Fangfei Huo
*date:2015.3.1
*cse 100 assignment 4
*
*use Dijkstra Algorithm to compute the shortest path between to nodes
*after each compute initial the dist,pre,done to make the graph get ready for the next search
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ActorGraph.hpp"
using namespace std;

/*to tell the priority queue how the priority is computed
* for each node the lower the distance the higher the priorty 
*/
class compNode{
  public:
	bool operator()(ActorNode*& one, ActorNode*& other){
		return (one->dist) > (other->dist);
	}
};

/*the Dijkstra Algorithm
* the only difference from the general Dijkstra Algorithm is
* we stop the algorithm once we get the end-node from the prority queue
*/
void pathfinder(string &actor_name1, string &actor_name2, ActorGraph &graph){
	string from = actor_name1;
	string to = actor_name2;
	priority_queue<ActorNode*, vector<ActorNode*>, compNode> q;
	ActorNode* head;
	int new_dist;
	
	graph.actor_map[from]->dist = 0;
	//graph.actor_map[from]->pre = -1;
	q.push(graph.actor_map[from]);

	while (!q.empty()){
		head = q.top();
		q.pop();

		if (head->name.compare(to)==0) return;
		if (head->done){
			continue;
		}
		else{
			head->done = true;
			for (auto it = head->adjacent.begin(); it != head->adjacent.end(); ++it){
				new_dist = head->dist + (it->second->weight);
				
				if (new_dist < it->first->dist){
					it->first->dist = new_dist;
					it->first->pre = head;
					q.push(it->first);
				}
			}
		}
	}
}

/*use to write the path between two nodes
* use a vector track to temporary store the path
*/
void writepath(string &from, string &to, ofstream& out, ActorGraph &graph){
	ActorNode *end;
	ActorNode *start;

	end = graph.actor_map[to];
	start = graph.actor_map[from];
	vector<ActorNode*> track;
	
	while (end != start){
	        track.push_back(end);
		end = end->pre;
	}
	track.push_back(end);
	
	for (int i = track.size() - 1; i > 0; i--) {
		out <<'('<< track[i] -> name<<")--[" <<track[i] -> adjacent[track[i-1]]->title<< "#@"
		<<track[i] -> adjacent[track[i-1]]->year << "]-->";
	}
	out <<'('<<track[0]->name<<')'<<endl;
}



int main(int argc, char** argv){
	char ifweighted = *argv[2];
	string findpair = argv[3];
	string output = argv[4];
	ActorGraph graph;

	//load actor-movie data
	if (ifweighted == 'u')
		if (graph.loadFromFile(argv[1], false)); else cout << "error in reading data" << endl;
	else if (ifweighted == 'w')
		if (graph.loadFromFile(argv[1], true)); else cout << "error in reading data" << endl;
	
	//create the graph by link all the nodes
	graph.createGraph();

	bool have_header = false;
	ifstream infile(findpair, ios::in);
	ofstream outfile(output, ios::out);

	if (infile.is_open());
	else cout << "error in opening infile" << endl;
	if (outfile.is_open());
	else cout << "error in opening outfile" << endl;
	
	outfile<<"(actor)--[movie#@year]-->(actor)--..."<<endl;
	
	// read pair file and do a Dijkstra algorithm to search for the shortest distance for every pair
	//and write the result to the output file
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
                        
			//get the next string before hitting a tab character and put it in 'next'
			if (!getline(ss, next, '\t')) break;
                           
			record.push_back(next);
                      
                       // cout<<next<<endl;
		}
                
		if (record.size() != 2){
			// we should have exactly 2 columns
			continue;
		}

		string actor_name1(record[0]);
		string actor_name2(record[1]);

		// we have an actor/movie relationship
		pathfinder(actor_name1, actor_name2, graph);
		writepath(actor_name1, actor_name2, outfile, graph);
                graph.MakeUpdate();
                
	}
         if (!infile.eof())
	{
		cerr << "Failed to read " << argv[1] << "!\n";
		return false;
	}
	infile.close();
        outfile.close();
}
