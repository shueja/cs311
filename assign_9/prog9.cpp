#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "graph.h"
using namespace std;

void printHeader() {
    cout << "Author: Jeremiah Shue and Mitchell Karam" << endl
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
        cout << id << city_code << name << pop << elev << endl;
        g.addVertex(Vertex(stoi(id), city_code, name, pop, elev));
    }
    g.printGraph();
}

void loadRoads(Graph& g) {
    fstream in;
    in.open("road.txt", ios::in);

    string line, word;
    vector<string> citydata;
    string from, to, weight;
    while (in >> from >> to >> weight) {
        cout << from << to << weight << endl;
        g.addDirectedEdge(stoi(from), stoi(to), stof(weight));
    }
    g.printGraph();
}

int fromCityCode(string code) {
    
}

vector<Edge> shortestPath(int from, int to) {
    return vector<Edge>();
}

int main(int argc, char *argv[]) {
    printHeader();
    Graph g;
    loadCities(g);
    loadRoads(g);
    if (argc == 3) {

    }

}

