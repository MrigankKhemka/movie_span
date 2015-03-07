
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "MovieSpanGraph.hpp"
#include <unordered_set>

using namespace std;

/*use to write the path between two nodes
* use a vector track to temporary store the path
*/
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

	int setNumber = graph.actorNum;

	/*for(int i= 0;i<graph.actorSet.size();i++){
		 cout<<i<<": "<<graph.actorSet[i] <<endl;
		 }*/

	while (setNumber > 1){
		int setcount = 0;
		int selectedMovieIndex;

		for (int i = 0; i < graph.unincludedMovie.size(); i++){
			int curSetcount = 0;
			unordered_set<int> actorSetInMovie;

			for (int j = 0; j < graph.unincludedMovie[i]->cast.size(); j++) {
				int actorIndex = graph.actor_map[graph.unincludedMovie[i]->cast[j]];
				actorSetInMovie.emplace(graph.getRoot(actorIndex));
			}
			curSetcount = actorSetInMovie.size();

			//cout << "movie" << graph.unincludedMovie[i]->title << endl;
			//cout << "current setcount " << curSetcount << endl;
			if (curSetcount > setcount){
				selectedMovieIndex = i;
				setcount = curSetcount;
			}
		}

		Movie* selectedMovie = graph.unincludedMovie[selectedMovieIndex];
		movieOut.push_back(selectedMovie);

		//cout <<"selected movie = "<< selectedMovie->title << endl;

		graph.unincludedMovie.erase(graph.unincludedMovie.begin() + selectedMovieIndex);

		for (int i = 0; i < selectedMovie->cast.size() - 1; i++) {
			int actorIndex1 = graph.actor_map[selectedMovie->cast[i]];
			int actorIndex2 = graph.actor_map[selectedMovie->cast[i + 1]];
			graph.unionSet(actorIndex1, actorIndex2);
		}

		setNumber = 0;
		for (int i = 0; i < graph.actorSet.size(); i++){
			if (graph.getRoot(i) == i)
				setNumber++;
		}

		//cout << setNumber << endl;
	}

	writeMovieSpan(outfile, movieOut);
	cout << movieOut.size()<< endl;
}
