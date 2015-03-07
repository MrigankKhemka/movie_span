/*
*Name:Xinyu Qian, Fangfei Huo
*date:2015.3.1
*cse 100 assignment 4
*
*a class for Movie 
*
* Description of its member:
* vector cast: all actors's name who casted in a movie
* weight: each movie has a weight computed by it's released year 
* year:the year of movie released             
* index: a string used to distinguish a movie from other movies, it is composed of movie title and movie year 
* title:the name of the movie
* 
* initialize: set the index,year,weight,title as the input movie's index,year,weight and title
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

            /*the compare operator used in the priority queue of movie
             * the lower weight movie has higher priority
             */
			  bool comp(Movie* one, Movie* other){
				  return (one->weight) < (other->weight);
			  }
			  ~Movie() {  }
		  };

#endif // MOVIE_HPP
