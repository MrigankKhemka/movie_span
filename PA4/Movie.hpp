/*
*Name:Xinyu Qian, Fangfei Huo
*date:2015.3.1
*cse 100 assignment 4
*/
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
			  string index;
                          string title;

			  Movie(string index, int year, int weight,string title) : index(index), weight(weight), year(year),title(title){ }

			  bool comp(Movie* one, Movie* other){
				  return (one->weight) < (other->weight);
			  }
		  };
#endif // MOVIE_HPP
