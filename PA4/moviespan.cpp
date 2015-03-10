/*
*Name:Xinyu Qian, Fangfei Huo
*date:2015.3.8
*cse 100 assignment 4
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "MovieSpanGraph.hpp"
#include <unordered_set>

using namespace std;

/*output moviespan*/
void writeMovieSpan(ofstream &outfile, vector<Movie*> &movieOut){

	for (int i = 0; i < movieOut.size(); i++) {
		for (int j = 0; j < movieOut[i]->cast.size(); j++)
			outfile << movieOut[i]->cast[j] << "	" << movieOut[i]->title << "	" << movieOut[i]->year << endl;
	}
}

int main(int argc, char** argv){

	string output = argv[2];

	MovieSpanGraph graph;
	vector<Movie*> movieOut;

	//load actor-movie data

	if (graph.loadFromFile(argv[1])); else cout << "error in reading data" << endl;

	ofstream outfile(output, ios::out);

	if (outfile.is_open());
	else cout << "error in opening outfile" << endl;

	outfile << "Actor/Actress	Movie	Year" << endl;

	while (graph.setNum > 1){
		int setcount = 0;
		int selectedMovieIndex;
		
		//choose the movie for the each greedy algorithm's iteration
		for (int i = 0; i < graph.unincludedMovie.size(); i++){
			int curSetcount = 0;
			unordered_set<int> actorSetInMovie;

			for (int j = 0; j < graph.unincludedMovie[i]->cast.size(); j++) {
				int actorIndex = graph.actor_map[graph.unincludedMovie[i]->cast[j]];
				actorSetInMovie.emplace(graph.getRoot(actorIndex));
			}
			curSetcount = actorSetInMovie.size();

			if (curSetcount > setcount){
				selectedMovieIndex = i;
				setcount = curSetcount;
			}
		}
		
		//put the selected movie into the movieOut vector and erase it from unincludedMovie vector
		Movie* selectedMovie = graph.unincludedMovie[selectedMovieIndex];
		movieOut.push_back(selectedMovie);
    	graph.unincludedMovie.erase(graph.unincludedMovie.begin() + selectedMovieIndex);

		//union all the actor in the selected movie
		for (int i = 0; i < selectedMovie->cast.size() - 1; i++) {
			int actorIndex1 = graph.actor_map[selectedMovie->cast[i]];
			int actorIndex2 = graph.actor_map[selectedMovie->cast[i + 1]];
			graph.unionSet(actorIndex1, actorIndex2);
		}

	}

	writeMovieSpan(outfile, movieOut);
	
	//out put the size of moviespan
	cout << movieOut.size()<< endl;
	
	outfile.close();
}
