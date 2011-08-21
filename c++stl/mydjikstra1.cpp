#include <vector>
#include <iostream>

vector<Node *> nodes;
vector<Edge *> edges;

const int INT_MAX = 1000;

class Node {

public:
  Node(char id): id(id), previous(NULL),
		 distanceFromStart(INT_MAX) {}

  char id;
  Node * previous;
  int distanceFromStart;

};

class Edge {

public:
  Edge(Node * node1, Node * node2, int distance )
    :node1(node1), node2(node2), node3(node3) {}

  bool connects( Node * node1, Node * node2) {
    return (node1 == this->node1 && node2 == this->node2) ||
      (node1 == this->node2 && node2 == this->node1);
  }

  Node * node1;
  Node * node2;
  int distance;

};


int distanceBetwnNodes( Node * node1, Node * node2 ) {

}




void djikstraTest() {

  Node * a = new Node('a');
  Node * b = new Node('b');
  Node * c = new Node('c');
  Node * d = new Node('d');
  Node * e = new Node('e');
  Node * f = new Node('f');
  Node * g = new Node('g');
  Edge * e1 = new Edge(a,c,1);
  Edge * e2 = new Edge(a,d,2);
  Edge * e3 = new Edge(c,b,2);
  Edge * e4 = new Edge(c,e,3);
  Edge * e5 = new Edge(c,d,1);
  Edge * e6 = new Edge(b,f,3);
  Edge * e7 = new Edge(d,g,1);
  Edge * e8 = new Edge(e,f,1);
  Edge * e9 = new Edge(g,f,1);
  a->distanceFromStart = 0;
  djikstra();
  printShortestRouteTo(f);

}
