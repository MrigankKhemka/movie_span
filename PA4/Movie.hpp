#ifndef MOVIE_HPP
#define MOVIE_HPP
#include <string>
#include <vector>

using namespace std;

		  class Movie {
			  //friend bool comp(Movie* one, Movie* other);
		  public:

			  vector<string> cast;
			  int weight;
			  int year;
			  string title;

			  Movie(string title, int year, int weight) : title(title), weight(weight), year(year){ }

			  bool comp(Movie* one, Movie* other){
				  return (one->weight) < (other->weight);
			  }
		  };
#endif // MOVIE_HPP