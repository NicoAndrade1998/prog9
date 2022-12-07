using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <limits.h>

struct city{
    int ID;
    string City_Code;
    string City_Code;
    int population;
    int elevation;
};

struct road{
    int From_City;
    int To_City;
    int distance;
};

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

        int *visited=new int[V]=0;
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
      for(int i=0;i<visits<i++)
      {
        //call to a method to print the names of the visited cities;
      }
    }
    else
    {
      //print statement for if no route exits
    }
}

int main(int argc, char** argv){
    //parsing user input
    char* From_City = argv[0];
    char* To_City = argv[1];


    //reading input files
    ifstream cities("city.txt");
    ifstream roads("road.txt");


    return 0;
}
