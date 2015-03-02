#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ActorGraph.hpp"
using namespace std;

class compNode{
  public:
	bool operator()(ActorNode*& one, ActorNode*& other){
		return (one->dist) < (other->dist);
	}
};

void pathfinder(string &actor_name1, string &actor_name2, ActorGraph graph){

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
                 cout<<"head name:"<<head->name<<endl;
		q.pop();

		if (head->name.compare(to)==0) {
		 cout<<"head == end"<<endl;		
		return;//string == ??????
		}
		if (head->done){
			cout<<"headdone"<<endl;
			continue;
		}
		else{
			head->done = true;
			//adjacent_map = head->adjacent;
                       for (auto it = head->adjacent.begin(); it != head->adjacent.end(); ++it){
                                    cout<<"adjacent node of "<<head->name<<":"<<it->first->name<<endl;
                       }
			for (auto it = head->adjacent.begin(); it != head->adjacent.end(); ++it){
				new_dist = it->second->weight + head->dist;
                               // cout<<"adjacent node:"<<it->first->name<<endl;
                               // cout<<"new_dist:"<<new_dist<<endl;
				if (new_dist < it->first->dist){
					it->first->dist = new_dist;
                                  //   cout<<"updated_dist:"<<it->first->dist<<endl;
					it->first->pre = head;
					q.push(it->first);
				}
			}
		}

		//for (auto it = head->adjacent.begin(); it != head->adjacent.end(); ++it){//sure?
		//	new_dist = head->dist + (it->second->weight);
		//	if (new_dist < it->first->dist){
		//		it->first->dist = new_dist;
		//		it->first->pre = head;
		//		q.push(it);
		//		if (it->first->name == to&&it->first->done == true){
		//			writepath(string &from, string &to, ofstream& out);
		//		}


		//	}
		//}

		//}
	}
}

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
		out <<'('<< track[i] -> name<<")--[" <<track[i] -> adjacent[track[i-1]]-> title<< "#@"
		<<track[i] -> adjacent[track[i-1]]->year << "]-->";
	}
	out <<'('<<track[0]->name<<')'<<endl;
	
	
	/*while (end != start){
		v.push_back(cur->name);
		for (auto it = cur->adjacent.begin(); it->first != cur->prev; ++it){
			if (it->first = cur->prev)
				v.push_back(it->second);
			cur = cur->prev;
		}
	}
	v.push_back(cur->name);

	for (int i = v.size() - 1; i >= 0; i--){
		out.put(v[i]);
	}
*/
}

int main(int argc, char** argv){
	//string data = argv[1];
	char ifweighted = *argv[2];
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
	ofstream outfile(output, ios::out);

	if (infile.is_open());
	else cout << "error in opening infile" << endl;
	if (outfile.is_open());
	else cout << "error in opening outfile" << endl;
	
	outfile<<"(actor)--[movie#@year]-->(actor)--..."<<endl;
	// keep reading lines until the end of file is reached
	int j=1;//for debug
	while (infile)
	{		
		string s;
		//ActorGraph graphtemp;
		//graphtemp = graph;
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

		// we have an actor/movie relationship, now what?
		pathfinder(actor_name1, actor_name2, graph);
		cout << j << " pathfinder passed" << endl;
		writepath(actor_name1, actor_name2, outfile, graph);
                graph.MakeUpdate();
		cout << j << " writepath passed" << endl;
		j++;
	}
}








