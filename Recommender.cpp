#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include "treemm.h"
#include <unordered_set>
#include <iostream>
#include "utility.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    j = &user_database;
    k = &movie_database;
    
    possible_movies = new TreeMultimap<string, int>;
    totalMovies = new unordered_set<Movie*>;
    
}

Recommender::~Recommender(){
    delete possible_movies;
    delete totalMovies;
}


struct MovieUpdate{ //struct declared for easier management of titles, ratings, and compatibility scores
    
    MovieUpdate(const std::string title, float rating, int score, string id):m_title(title), m_rating(rating), m_score(score), m_id(id){}
    
    string m_title;
    float m_rating;
    int m_score;
    string m_id;
};

bool compareMovies(const MovieUpdate m1, const MovieUpdate m2){ //helper function to compare MovieUpdate Objects
    
    if (m1.m_score == m2.m_score){
        if (m1.m_rating == m2.m_rating)
            return m1.m_title > m2.m_title;
        
        return m1.m_rating > m2.m_rating;
    }
    
    return m1.m_score > m2.m_score;
    
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    
    if (movie_count < 0) //If we are provided a negative movie count return an empty vector
        return vector<MovieAndRank>();
    
    
    User* user = j->get_user_from_email(user_email); //get the user from the email provided
    if (user == nullptr) //check if the user isn't in the file.
        return vector<MovieAndRank>();
    
    
    vector<string> watchHist = user->get_watch_history();
    
    
    vector<string> d;
    vector<string> g;
    vector<string> a;
    
    
    
    for (string s: watchHist){
        
        Movie* currM = k->get_movie_from_id(strToLower(s));
        
        g = currM->get_genres();
        
        for (string possG : g){
            vector<Movie*> genres = k->get_movies_with_genre(possG);
            
            for (Movie* pM : genres){
                
                if (pM != currM){
                    totalMovies->insert(pM);
                    possible_movies->insert(pM->get_id(), 1);
                }
            }
        }
        
        
        
        a = currM->get_actors();
        
        for (string possA : a){
            vector<Movie*> actors = k->get_movies_with_actor(possA);
            
            for (Movie* pM : actors){
                
                if (pM != currM){
                    totalMovies->insert(pM);
                    possible_movies->insert(pM->get_id(), 30);
                }
            }
        }
        
        d = currM->get_directors();
        
        for (string possD : d){
            vector<Movie*> directors = k->get_movies_with_director(possD);
            
            for (Movie* pM : directors){
                
                if (pM != currM){
                    totalMovies->insert(pM);
                    possible_movies->insert(pM->get_id(), 20);
                }
            }
        }
    }
    
    
    
    vector<MovieUpdate> m_mov;
    
    for (Movie* m : *totalMovies){
        
        TreeMultimap<string, int>::Iterator it = possible_movies->find(strToLower(m->get_id()));
        int compScore = 0;
        while (it.is_valid()){
            compScore += it.get_value();
            it.advance();
        }
        
        m_mov.push_back(MovieUpdate(m->get_title(), m->get_rating(), compScore, m->get_id()));
    }
    
    
    sort(m_mov.begin(), m_mov.end(), compareMovies);
    
    
    vector<MovieAndRank> m_movies;
    for (MovieUpdate m: m_mov){
        
        if (m.m_score > 1){
            MovieAndRank newM(m.m_id, m.m_score);
            m_movies.push_back(newM);
        }
    }
    
    vector<MovieAndRank> finalV;
    for (int i = 0; i < movie_count; i++){
        finalV.push_back(m_movies[i]);
        
    }
    
    return finalV;
    
}
