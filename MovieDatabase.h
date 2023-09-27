#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    TreeMultimap<std::string, Movie*> directorM;
    TreeMultimap<std::string, Movie*> actorM;
    TreeMultimap<std::string, Movie*> genreM;
    TreeMultimap<std::string, Movie*> idM;
    
    std::vector<Movie*> totalM;
    
};

#endif // MOVIEDATABASE_INCLUDED

