using namespace std;
#include <iostream>
#include <string>
#include <fstream>


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

int main(int argc, char** argv){
    //parsing user input
    char* From_City = argv[0];
    char* To_City = argv[1];

    
    //reading input files
    ifstream cities("city.txt");
    ifstream roads("road.txt");


    return 0;
}