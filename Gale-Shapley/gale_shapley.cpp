#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <queue>
#include <chrono>

int main() {
    std::cout << "Inserire la dimensione del problema n = ";
    int n;
    std::cin >> n;
    std::vector<int> base_permutation;
    for (int i=0; i<n; i++)
        base_permutation.push_back(i);
    // Preferences list for boys
    std::vector<std::vector<int>> boys_preferences;
    // Preferences list for girls
    std::vector<std::vector<int>> girls_preferences;
    // Boys' ranking for the girls: girls_rankings[g][b] is the position
    // of boy b in the preferences list of girl g
    std::vector<std::vector<int>> girls_rankings;
    // For each boy, it gives the next girl to propose to
    std::vector<int> next_girl_to_propose;
    // For each girl, it gives the current boy matched to the girl
    std::vector<int> current_boy;
    // Queue of the boys that haven't been matched yet
    std::queue<int> free_boys;
    auto start = std::chrono::steady_clock::now();
    for (int i=0; i<n; i++) {
        std::vector<int> preferences_boy_i = base_permutation;
        std::shuffle(preferences_boy_i.begin(), preferences_boy_i.end(), std::default_random_engine(i));
        boys_preferences.push_back(preferences_boy_i);
        next_girl_to_propose.push_back(0);
        std::vector<int> preferences_girl_i = base_permutation;
        std::shuffle(preferences_girl_i.begin(), preferences_girl_i.end(), std::default_random_engine(i * i));
        girls_preferences.push_back(preferences_girl_i);
        std::vector<int> ranking_girl_i(n);
        for (int j=0; j<n; j++)
            ranking_girl_i.at(preferences_girl_i.at(j)) = j;
        girls_rankings.push_back(ranking_girl_i);
        current_boy.push_back(-1);
        free_boys.push(i);
    }
    // Inizio dell'algoritmo di Gale-Shapley
    while (!free_boys.empty()) {
        int boy = free_boys.front();
        int girl = boys_preferences.at(boy).at(next_girl_to_propose.at(boy));
        next_girl_to_propose.at(boy) = next_girl_to_propose.at(boy) + 1;
        if (current_boy.at(girl) < 0) {
            current_boy.at(girl) = boy;
            free_boys.pop();
        }
        else if (girls_rankings.at(girl).at(boy) < girls_rankings.at(girl).at(current_boy.at(girl))) {
            free_boys.push(current_boy.at(girl));
            current_boy.at(girl) = boy;
            free_boys.pop();
        }
        
    }
    /*
    for (int i=0; i<n; i++) {
        std::cout << "Girl " << i << " has been matched with boy " << current_boy.at(i) << std::endl;
    }
    */
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    // Usare la durata per verificare che il running time è O(n^2)
    std::cout << "Running Time: " << std::chrono::duration <double, std::milli> (diff).count() << std::endl;
    return 0;
}