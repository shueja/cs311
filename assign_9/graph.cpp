#include "graph.h"

// @brief Construct a Graph with the given number of vertices.
// @param nV The number of vertices in the graph.
Graph::Graph(int nV)
{
    numVerts = 0;
    for (int i = 0; i < nV; i++) {
        addVertex(Vertex(i, "", "", "", ""));
    }
    cout<<numVerts<<endl;
}

// @brief destructor
Graph::~Graph()
{
    
    // : Add your code here
}

// @brief add a vertex to the graph
void Graph::addVertex(Vertex v)
{
    vertices.push_back(v);
    adjList.push_back(vector<Edge>(0));
    numVerts++;
    // : Add a vertex to the vertex vector
    // : Add an empty list to the adjacency list
}

// @brief add a directed edge v1->v2 to the graph
void Graph::addDirectedEdge(int v1, int v2, float weight)
{
    adjList[v1].push_back(Edge(v1, v2, weight));
    // : Add an edge to the adjacency list of v1
}

// @brief add an undirected edge to the graph
void Graph::addUndirectedEdge(int v1, int v2, float weight)
{
    adjList[v1].push_back(Edge(v1, v2, weight));
    adjList[v2].push_back(Edge(v2, v1, weight));
    // : Add edge v1->v2
    // : Add edge v2->v1
}

// @brief the number of outgoing edges from a vertex
int Graph::outDegree(int v)
{
    // : Add code here
    return adjList[v].size();
}

// @brief depth first search from vertex v
vector<int> Graph::DepthFirstSearch(int v)
{
   vector<int> stack;
   vector<int> visited;
   stack.push_back(v);

   while ( stack.size() > 0 ) {
      auto currentV = *(stack.rbegin());
      cout<<currentV;
      stack.pop_back();
      bool wasVisited = false;
      for (auto it = visited.begin(); it != visited.end(); it++) {
        if (*it == currentV) {
            wasVisited = true;
            break;}
      }
      if (!wasVisited) {
        visited.push_back(currentV);
        cout<<" was added" <<endl;
        for (auto adj = adjList[currentV].rbegin(); adj != adjList[currentV].rend(); adj++) {

            stack.push_back((*adj).to_vertex);
            
        }
      }else {
        cout << " was visited"<<endl;
      }

}
    return visited;
    // : Implement the depth first search algorithm
    // Add the vertex ID to a vector when it is visited
}

// @brief breadth first search from a vertex
vector<int> Graph::BreadthFirstSearch(int v)
{
    vector<int> visited;
    queue<int> frontierQueue;
    vector<bool> discovered;
    discovered.resize(numVerts);
    frontierQueue.push(v);
    discovered[v] = true;

   while ( frontierQueue.size() > 0 ) {
      auto currentV = frontierQueue.front();
      frontierQueue.pop();
      visited.push_back(currentV);
    for (auto adj = adjList[currentV].begin(); adj != adjList[currentV].end(); adj++) {
            int adjV = (*adj).to_vertex;
            if (!discovered[adjV]) {
                frontierQueue.push(adjV);
                discovered[adjV] = true;
            }
            
     }
   }
   return visited;
}


bool Graph::checkCycleInternal(int v, vector<bool>& visited, int parent)
{
 
    // Mark the current node as visited
    visited[v] = true;
    for (auto i = adjList[v].begin(); i != adjList[v].end(); ++i) {
        int adj = (*i).to_vertex;
        cout << "  Checking from " << v << " to " << adj << endl;
        // If an adjacent vertex is not visited,
        // then recur for that adjacent
        if (!visited[adj]) {
            if (checkCycleInternal(adj, visited, v))
                return true;
        }
 
        // If an adjacent vertex is visited and
        // is not parent of current vertex,
        // then there exists a cycle in the graph.
        else if (adj != parent)
            return true;
    }
    return false;
}
/**
 * @brief Check if the graph has cycles
 * @return true if the graph has cycles
 */
bool Graph::checkCycle()
{
    if (numVerts == 0 || numVerts == 1) {return false;}

    vector<bool> visited;
    visited.resize(numVerts);
    // Call the recursive helper
    // function to detect cycle in different
    // DFS trees
    for (int u = 0; u < numVerts; u++) {
        cout<< "Checking cycles for " << u <<endl;
        // Don't recur for u if
        // it is already visited
        if (!visited[u]) {
            if (checkCycleInternal(u, visited, -1)) {
                return true;
            }
        }
    }
    return false;
}


// @brief print the graph
void Graph::printGraph()
{
    cout << "Graph:" << endl;
    for (int i = 0; i < numVerts; i++)
    {
        cout << i << ": ";
        for(auto j = adjList[i].begin(); j != adjList[i].end(); ++j)
        {
            cout << (*j).to_vertex << " " ;
        }
        cout << endl;
    }
    cout << endl;
}
