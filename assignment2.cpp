#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Movie {
    string title;
    double imdbRating;
    int releaseYear;
    long watchTime; // popularity measure (minutes watched)
};

//  QuickSort Implementation 
int partition(vector<Movie>& movies, int low, int high, string key) {
    // Choose pivot (last element)
    Movie pivot = movies[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        bool condition = false;

        if (key == "rating")
            condition = movies[j].imdbRating > pivot.imdbRating;
        else if (key == "year")
            condition = movies[j].releaseYear > pivot.releaseYear;
        else if (key == "popularity")
            condition = movies[j].watchTime > pivot.watchTime;

        if (condition) {
            i++;
            swap(movies[i], movies[j]);
        }
    }
    swap(movies[i + 1], movies[high]);
    return (i + 1);
}

void quickSort(vector<Movie>& movies, int low, int high, string key) {
    if (low < high) {
        int pi = partition(movies, low, high, key);
        quickSort(movies, low, pi - 1, key);
        quickSort(movies, pi + 1, high, key);
    }
}

//  Display Function 
void displayMovies(const vector<Movie>& movies) {
    cout << "\nSorted Movies:\n";
    cout << "---------------------------------------------\n";
    for (const auto& m : movies) {
        cout << m.title << " | Rating: " << m.imdbRating
             << " | Year: " << m.releaseYear
             << " | WatchTime: " << m.watchTime << " mins\n";
    }
}

//  Main
int main() {
    vector<Movie> movies = {
        {"Avatar: The Way of Water", 7.8, 2022, 5300000},
        {"Spider-Man: No Way Home", 8.2, 2021, 6100000},
        {"The Batman", 7.9, 2022, 4500000},
        {"Parasite", 8.6, 2019, 5200000},
        {"Avengers: Endgame", 8.4, 2019, 8500000},
        {"Joker", 8.5, 2019, 6400000}
    };

    cout << "Sort movies by (rating/year/popularity): ";
    string key;
    cin >> key;

    // Validate user input
    if (key != "rating" && key != "year" && key != "popularity") {
        cout << "Invalid choice! Defaulting to rating.\n";
        key = "rating";
    }

    quickSort(movies, 0, movies.size() - 1, key);
    displayMovies(movies);

    return 0;
}
