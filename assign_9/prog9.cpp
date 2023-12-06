#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "graph.h"
using namespace std;

void printHeader() {
    cout << "Author: Jeremiah Shue and Mitchell Karan" << endl
    << "Date: 12/04/2023" << endl
    << "Course: CS311 (Data structures and Algorithms)" << endl     
    << "Description : Program to find the shortest route between cities" << endl
    << "----------------------------------------------------------------" << endl;
}

void loadCities(Graph& g) {
    fstream cityin;
    cityin.open("city.txt", ios::in);

    string line, word;
    vector<string> citydata;
    string id, city_code, name, pop, elev;
    while (cityin >> id >> city_code >> name >> pop >> elev) {
        //cout << id << city_code << name << pop << elev << endl;
        g.addVertex(Vertex(stoi(id), city_code, name, pop, elev));
    }
}

void loadRoads(Graph& g) {
    fstream in;
    in.open("road.txt", ios::in);

    string line, word;
    vector<string> citydata;
    string from, to, weight;
    while (in >> from >> to >> weight) {
        //cout << from << to << weight << endl;
        g.addDirectedEdge(stoi(from), stoi(to), stof(weight));
    }
}

void displayShortestPath(Graph& g, const string& fromCode, const string& toCode) {
    //convert city codes to vertex IDs
    int fromId = g.getIdFromCode(fromCode);
    int toId = g.getIdFromCode(toCode);

    //check if city codes are valid
    if (fromId == -1) {
        cout << "Invalid city code: " << fromCode << endl;
        return;
    } else if (toId == -1){
        cout << "Invalid city code: " << toCode << endl;
        return;
    }

    //display city information
    cout << "From City: " << g.vertices[fromId].name << ", population " << g.vertices[fromId].pop;
    cout << ", elevation " << g.vertices[fromId].elev << endl;
    cout << "To City: " << g.vertices[toId].name << ", population " << g.vertices[toId].pop;
    cout << ", elevation " << g.vertices[toId].elev << endl;

    //get the shortest path
    vector<Edge> path = g.findShortestRoute(fromCode, toCode);

    //check if a path exists
    if (path.empty()) {
        cout << "No route from " << fromCode << " to " << toCode << endl;
        return;
    }

    //get the total distance
    float totalDistance = 0;
    for (const Edge& edge : path) {
        totalDistance += edge.weight;
    }

    //display the total distance
    cout << "The shortest distance from " << g.vertices[fromId].name << " to " << g.vertices[toId].name;
    cout << " is " << totalDistance << endl;

    //display the route
    cout << "through the route: ";
    for (size_t i = 0; i < path.size(); i++) {
        if (i > 0) cout << "->";
        cout << g.vertices[path[i].from_vertex].name;
    }
    cout << "->" << g.vertices[toId].name << endl;
}

int main(int argc, char *argv[]) {
    cout << endl; //buffer
    printHeader();
    Graph g;
    loadCities(g);
    loadRoads(g);
    if (argc == 3) {
        string fromCityCode = argv[1];
        string toCityCode = argv[2];

        displayShortestPath(g, fromCityCode, toCityCode);
    } else {
        cout << "Usage: " << argv[0] << " [from_city_code] [to_city_code]" << endl;
    }

    cout << endl; //buffer
    return 0;
}

