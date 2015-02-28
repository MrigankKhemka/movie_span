#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <vector>

protected:using namespace std;

		  class Movie {

		  public:

			  vector<ActorNode*> cast;
			  int weight;
			  int year;
			  string title;

			  Movie(string title, int year) : title(title), weight(2015 - year + 1), year(year){ }

			  bool comp(Movie* one, Movie* other){
				  return (one->weight) < (other->weight);
			  }



		  };
#endif // MOVIE_HPP