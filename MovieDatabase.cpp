#include "MovieDatabase.h"
#include "Movie.h"
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <sstream>
#include "utility.h"


using namespace std;

MovieDatabase::MovieDatabase()
{}

MovieDatabase::~MovieDatabase(){
    for (Movie* m: totalM)
        delete m;
}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);
    
    if (infile){
        
        string movieId;
        string year;
        string title;
        vector<string> directors;
        vector<string> actors;
        vector<string> genres;
        float rating = 0;
        
        
        string line;
        
        int count = 1;
        
        
        while (getline(infile, line)){
            
            if (line.empty()){
                count = 1;
                directors.clear();
                actors.clear();
                genres.clear();
                continue;
            }

            
            if (count == 1){
               movieId = strToLower(line);
            }
            
            else if (count == 2){
                title = line;
            }

            
            else if (count == 3){
                year = line;
            }
            
            else if (count == 4){
                
                stringstream ss(line); //While the stringstream is valid
                
                while (ss){
                    
                    if (!getline(ss, line, ',')) //If we reach the end of the line break the loop
                        break;
                    
                    string temp = strToLower(line); //make a lower string of the line
                    
                    directors.push_back(temp); //Add it to our map
                }
            }
            
            //ALL CODE BELOW FOLLOWS ABOVE LOGIC
            
            else if (count == 5){
                
                stringstream dd(line);
                
                while (dd){
                    
                    if (!getline(dd, line, ','))
                        break;
                    
                    string temp = strToLower(line);
                    
                    actors.push_back(temp);
                }
            }
            
            else if (count == 6){
                
                stringstream gg(line);
                
                
                while (gg){
                    
                    if (!getline(gg, line, ','))
                        break;
                    
                    string temp = strToLower(line);
                    
                    genres.push_back(temp); 
                }
            }
            
            else{
                
                //If we reach the rating:
                rating = stof(line);
                
                //Get the movie object and insert it into every map
                Movie* m = new Movie(movieId, title, year, directors, actors, genres, rating);
                
                for (string s : genres){
                    genreM.insert(s, m);
                }
                
                for (string d : directors){
                    directorM.insert(d, m);
                }
                
                for (string a : actors){
                    actorM.insert(a, m);
                    
                }
        
                //Insert it into the IDMap and into the total map of movies for deletion later
                idM.insert(movieId, m);
                totalM.push_back(m);
                
                
            }
            
            count++;
        }
    }
    else
        return false;
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    //Find the movie from the id
    TreeMultimap<string, Movie*>::Iterator j =  idM.find(id);
    
    //return the movie
    if (j.is_valid())
        return j.get_value();
    
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    
    TreeMultimap<string, Movie*> ::Iterator j = directorM.find(director);
    vector<Movie*> movies;

    while (j.is_valid()){
        movies.push_back(j.get_value());
        j.advance();
    }
    
    return movies; 
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    TreeMultimap<string, Movie*> ::Iterator j = actorM.find(actor);
    vector<Movie*> movies;
    
    
    while (j.is_valid()){
        movies.push_back(j.get_value());
        j.advance();
    }
    
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    TreeMultimap<string, Movie*> ::Iterator j = genreM.find(genre);
    vector<Movie*> movies;
    
    while (j.is_valid()){
        movies.push_back(j.get_value());
        j.advance();
    }
    
    return movies;
}
