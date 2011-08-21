#include <list>
#include <map>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef int vertex_t;
typedef double weight_t;

struct edge {

  vertex_t target;
  weight_t weight;
  edge( vertex_t arg_target, weight_t arg_weight ): target(arg_target), weight( arg_weight ) {}
};

typedef map<vertex_t, list<edge> > adjacency_map_t;

template<typename T1, typename T2>
struct pair_first_less {

  bool operator() (pair<T1,T2> p1 const, pair<T1,T2>p2 const ) {
    if( p1.first == p2.first ) {
      return p1.second < p2.second;
    }
    return p1.first < p2.first;
  }
};

set<pair<weight_t, vertex_t>,pair_first_less<weight_t,vertex_t> > vertex_queue;

void shortestPath( vertex_t v, 

void printShortestPath() {

  for( adjacency_map_t::iterator vertex_iter = adj_map.begin();
       vertex_iter != adj_map.end(); vertex_iter++ ) {
    vertex_t v = vertex_iter->first;
    cout << "Distance to " << vertex_names[v] << ":" << min_distance[v] << endl;
    list<vertex_t> path = shortestPath(v, previous);
    list<vertex_t> iterator path_iter = path.begin();

    cout << "Path: ";
    for( ; path_iter != path.end(); path_iter++ ) {
      cout << vertex_names[*path_iter] << " ";
    }
    cout << endl;
  }
}

int main() {

  //ifstream file("/home/debnathsinha/Documents/code/puzzles/spellcheck/big.txt");
  //istream_iterator<string> it(file);
  //cout << *(it++) << endl << *(it++) << endl;

  adjacency_map_t adj_map;
  vector<string> vertex_names;

  vertex_names.push_back("Harrisburg");
  vertex_names.push_back("Baltimore");
  vertex_names.push_back("Washington");
  vertex_names.push_back("Philadelphia");
  vertex_names.push_back("Binghamton");
  vertex_names.push_back("Allentown");
  vertex_names.push_back("New York");

  adj_map[0].push_back(edge(1, 79.83));
  adj_map[0].push_back(edge(5, 81.15));
  adj_map[1].push_back(edge(0, 79.75));
  adj_map[1].push_back(edge(2, 39.42));
  adj_map[1].push_back(edge(3, 103.00));
  adj_map[2].push_back(edge(1,  38.65));
  adj_map[3].push_back(edge(1, 102.53));
  adj_map[3].push_back(edge(5,  61.44));
  adj_map[3].push_back(edge(6,  96.79));
  adj_map[4].push_back(edge(5, 133.04));
  adj_map[5].push_back(edge(0,  81.77));
  adj_map[5].push_back(edge(3,  62.05));
  adj_map[5].push_back(edge(4, 134.47));
  adj_map[5].push_back(edge(6,  91.63));
  adj_map[6].push_back(edge(3,  97.24));
  adj_map[6].push_back(edge(5,  87.94));
  
  
}
