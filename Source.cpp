using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <limits.h>
#include <vector>
#include <unordered_map>
#include <sstream>
#define V 20 //the amount of cities

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(int dist[], bool sptSet[])
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}


void dijkstra(int graph[V][V], int src, int goal)
{
    int dist[V]; // The output array.  dist[i] will hold the
                 // shortest
    // distance from src to i

    bool sptSet[V]; // sptSet[i] will be true if vertex i is
                    // included in shortest
    // path tree or shortest distance from src to i is
    // finalized

    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    int visits=0;
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        int *visited= new int[V];
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)
        {
          // Update dist[v] only if is not in sptSet,
          // there is an edge from u to v, and total
          // weight of path from src to  v through u is
          // smaller than current value of dist[v]
          if (!sptSet[v] && graph[u][v]  && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
          {
            dist[v] = dist[u] + graph[u][v];
            if(v==goal)
            {
              visited[visits]=v;
              visits++;
            }
          }
        }


    }
    if(dist[goal])
    {
      //print statement of cities called for
      for(int i=0;i<visits; i++)
      {
        //call to a method to print the names of the visited cities;
      }
    }
    else
    {
      //print statement for if no route exits
    }
}


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
    string from_city = argv[1];
    string to_city = argv[2];
    //string from_city = "AN";
    //string to_city = "BK";

    ifstream f_cities("city.txt");
    ifstream f_roads("road.txt");

    unordered_map<string, city> cities;
    parse_city(f_cities, cities);

    print_city(cities, from_city);
    print_city(cities, to_city);

    
    //creating adjacency list
    int adj_list[20][20];
    int i, x, y; //x and y are indexes, i is input
    while(!f_roads.eof()){
      f_roads >> i;
      f_roads >> x;
      f_roads >> y;
      //cout << i << " "<< x << " " << y << endl; //for testing
      adj_list[x][y] = i;
    }

    //convert input code to ID and calls dijkstra
    int to, from;
    auto tmp1 = cities.at(from_city);
    auto tmp2 = cities.at(to_city);
    dijkstra(adj_list, tmp1.id, tmp2.id);




    return 0;
}
