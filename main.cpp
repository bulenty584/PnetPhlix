//
//  main.cpp
//  PnetPhlix
//
//  Created by Bulent  Yesilyurt on 3/28/23.
//

#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "treemm.h"
#include "Movie.h"
#include "User.h"

using namespace std;
#include <iostream>
#include <string>

void findMatches(const Recommender& r,
 const MovieDatabase& md,
 const string& user_email,
                 int num_recommendations) {
    // get up to ten movie recommendations for the user
    vector<MovieAndRank> recommendations =
    r.recommend_movies(user_email, num_recommendations);
    if (recommendations.empty())
        cout << "We found no movies to recommend :(.\n";
    else {
        for (int i = 0; i < recommendations.size(); i++) {
            const MovieAndRank& mr = recommendations[i];
            Movie* m = md.get_movie_from_id(mr.movie_id);
            cout << i + 1 << ". " << m->get_title() << " ("
            << m->get_release_year() << ")\n Rating: "
            << m->get_rating() << "\n Compatibility Score: "
            << mr.compatibility_score << "\n"
            << endl;
        }
    }
}

int main(){
    
    UserDatabase j;
    MovieDatabase k;
    
    j.load("/Users/bulentyesilyurt/Desktop/users.txt");
    k.load("/Users/bulentyesilyurt/Desktop/movies.txt");
    
    Recommender r(j, k);
    
    string userE;
    int numR;
    cout << "Please Input email: ";
    
    cin >> userE;
    
    if (j.get_user_from_email(userE) == NULL){
        cout << "\nNo email found\n";
        exit(1);
    }
    cout << endl;
    
    
    cout << "How many movies would you like? ";
    
    cin >> numR;
    
    cout << endl;
    
    findMatches(r, k, userE, numR);
    
}
