#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

#define num_city 20
#define int_max 10000
class city {
public:
    int id;
    string city_code;
    string city_name;
    int population;
    int elevation;

    city(vector<string> tokens) {
        id = stoi(tokens[0]);
        city_code = tokens[1];
        city_name = tokens[2];
        population = stoi(tokens[3]);
        elevation = stoi(tokens[4]);
    }
};

void parse_city(ifstream &f_cities, unordered_map<string, city> &cities, unordered_map<int, city> &cities_id) {
    string line;
    while (getline(f_cities, line)) {
        vector<string> tokens;
        istringstream iss(line);
        string token;

        while (getline(iss, token, '\t')) {
            tokens.push_back(token);
        }

        city tmp(tokens);
        cities.insert({tmp.city_code, tmp});
        cities_id.insert({tmp.id, tmp});
    }
}

void print_city(unordered_map<string, city> &cities, string city) {
    cout << "city code: " << city << endl;
    auto tmp = cities.at(city);
    cout << tmp.id << " ";
    cout << tmp.city_code << " ";
    cout << tmp.city_name << " ";
    cout << tmp.population << " ";
    cout << tmp.elevation << " " << endl;
}

class road {
public:
    vector<vector<int>> matrix;

    road() {
        matrix = vector<vector<int>>(num_city, vector<int>(num_city, -1));
    };

    void add_road(int from, int to, int distance) {
        matrix[from][to] = distance;
    }
};

void parse_road(ifstream &f_roads, road &roads) {
    string line;
    while (getline(f_roads, line)) {
        vector<string> tokens;
        istringstream iss(line);
        string token;

        while (getline(iss, token, '\t')) {
            tokens.push_back(token);
        }
        roads.add_road(stoi(tokens[0]), stoi(tokens[1]), stoi(tokens[2]));
    }
}

int min_distance(vector<int> &distance, vector<bool> &visited) {
    int minimum = int_max;
    int index;
    
    for (int i = 0; i < num_city; i++) {
        if (visited[i] == false && distance[i] <= minimum) {
            minimum = distance[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(unordered_map<int, city> &cities_id, vector<vector<int>> &matrix, int from_city, int to_city) {
    vector<int> distance(num_city, int_max);
    vector<bool> visited(num_city, false);
    vector<int> path;

    distance[from_city] = 0;
    bool found = false;
    int shortest = -1;

    for (int i = 0; i < num_city; i++) {
        int u = min_distance(distance, visited);
        visited[u] = true;
        if (u == to_city) {
            found = true;
            shortest = distance[u];
            break;
        }
        path.push_back(u);

        for (int v = 0; v < num_city; v++) {
            if ((visited[v] == false) && (matrix[u][v] != -1) && (distance[u] != int_max) && (distance[u] + matrix[u][v] < distance[v])) {
                distance[v] = distance[u] + matrix[u][v];
            }
        }
    }

    if (found) {
        cout << "\nThe shortest distance from " << cities_id.at(from_city).city_name << " to " << cities_id.at(to_city).city_name << " is " << shortest << endl;
        for (int i = 0; i < path.size(); i++) {
            cout << cities_id.at(path[i]).city_name << "->";
        }
        cout << cities_id.at(to_city).city_name << endl;
    } else {
        cout << "\nNo route from " << cities_id.at(from_city).city_name << " to " << cities_id.at(to_city).city_name << endl;
    }
}


int main(int argc, char** argv){

    if (argc != 3) {
        cout << "Please input two city code. Example: ./prog9 AN BK" << endl;
        return -1;
    }

    string from_city = argv[1];
    string to_city = argv[2];
    // string from_city = "AN";
    // string to_city = "BK";

    ifstream f_cities("city.txt");
    unordered_map<string, city> cities;
    unordered_map<int, city> cities_id;
    parse_city(f_cities, cities, cities_id);
    if (cities.find(from_city) == cities.end()) {
        cout << "Invalid city code: " << from_city << endl;
        return -1;
    }

    if (cities.find(to_city) == cities.end()) {
        cout << "Invalid city code: " << to_city << endl;
        return -1;
    }

    ifstream f_roads("road.txt");
    road roads;
    parse_road(f_roads, roads);

    int from_city_id = cities.at(from_city).id;
    int to_city_id = cities.at(to_city).id;

    dijkstra(cities_id, roads.matrix, from_city_id, to_city_id);

    return 0;
}
