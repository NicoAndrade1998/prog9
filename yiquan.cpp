#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;
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

void parse_city(ifstream &f_cities, unordered_map<string, city> &cities) {
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

int main(int argc, char** argv){
    // string from_city = argv[1];
    // string to_city = argv[2];
    string from_city = "AN";
    string to_city = "BK";

    ifstream f_cities("city.txt");
    ifstream f_roads("road.txt");

    unordered_map<string, city> cities;
    parse_city(f_cities, cities);

    print_city(cities, from_city);
    print_city(cities, to_city);

    return 0;
}
