#include <iostream>
#include <vector>
#include <list>
#include <utility>

#define MAX 1000

typedef std::pair<int, int> intPair;

class PriorityQ;

class ssShortestPath {
public :
	friend class PriorityQ;
	ssShortestPath(int n);
	void addEdge(int start, int end, int weight);
	void Dijkstra(PriorityQ& q,  ssShortestPath& s, int root);
	void printEdge();
	void printParent();
private :
	int num_node;
	std::vector< std::list<intPair> > adjList;
	std::vector<int> parent;
}; 

class PriorityQ {
public :
	friend class ssShortestPath;
	PriorityQ(int n);
	void initializeNode(ssShortestPath& s);
	void buildMinHeap();
	void swapNode(intPair* a, intPair* b);
	void minHeapify(int index);
	intPair extractMin();	
	int findPos(int index);
	void decreaseKey(int node_idx, int key);
	bool heapEmpty() { return heapSize == 0; };
	void printCost();
private :
	// fisrt : end; second : cost
	std::vector<intPair> cal;
	int heapSize;
};

PriorityQ::PriorityQ(int n)
{
	heapSize = n;
	cal.resize(heapSize+1);
}

void PriorityQ::initializeNode(ssShortestPath& s)
{
	for(int i = 1; i < cal.size(); ++i) {
		cal[i].first = i-1;
		cal[i].second = MAX;
	}
}

void PriorityQ::printCost()
{
	std::cout << "node_index ";
	for(int i = cal.size()-1; i > 0 ; --i) {
		std::cout << cal[i].first << "  ";
	}
	std::cout << std::endl;
	
	std::cout << "min cost   ";
	for(int i = cal.size()-1; i > 0 ; --i) {
		std::cout << cal[i].second << " ";
	}
	std::cout << std::endl << std::endl;			
}

void PriorityQ::buildMinHeap() 
{
	for(int i = (cal.size()-1)/2; i > 0; --i) {
		minHeapify(i);
	}
}

void PriorityQ::swapNode(intPair* a, intPair* b)
{
	intPair temp = *a;
	*a = *b;
	*b = temp;
}

void PriorityQ::minHeapify(int index)
{
	while(1) {
		int left = index*2;
		int right = index*2 +1;
		int smallest;
		
		if(left <= heapSize && cal[left].second < cal[index].second) {
			smallest = left;
		} else {
			smallest = index;
		}
		if(right <= heapSize && cal[right].second < cal[smallest].second) {
			smallest = right;
		}
		if(smallest != index) {
			swapNode(&cal[smallest], &cal[index]);
			index = smallest;
		} else {
			return;
		}
	}
}

// find actual index of each node in cal vector
int PriorityQ::findPos(int index)
{
	for(int i = 1; i <= heapSize; ++i) {
		if(cal[i].first == index) {
			return i;
		}
	}
	return -1;	
}

void PriorityQ::decreaseKey(int index, int key)
{	
	if(key >= cal[index].second) {
		std::cout << "new key should be smaller" << std::endl;
		return;
	}		
	cal[index].second = key;
	for(index /= 2; index > 0; --index) { 
		minHeapify(index);
	}
}

intPair PriorityQ::extractMin()
{
	intPair min = cal[1];
	swapNode(&cal[1], &cal[heapSize]);
	--heapSize;
	
	minHeapify(1);	
	return min;
}

ssShortestPath::ssShortestPath(int n)
{
	num_node = n;
	adjList.resize(num_node);
	parent.resize(num_node, -1);
}

void ssShortestPath::addEdge(int start, int end, int weight)
{
	adjList[start].push_back(std::make_pair(end, weight));
}

void ssShortestPath::Dijkstra(PriorityQ& q, ssShortestPath& s, int root)
{
	std::list< std::pair<int,int> >::iterator it;
	it = adjList[root].begin();
		
	q.initializeNode(s);	
	// maintain previous-node table
	parent[root] = -1;
	// set cost of root to 0 
	int node_pos = q.findPos(root);
	q.decreaseKey(node_pos, 0);
		
	intPair prev_node;
	while(!q.heapEmpty()) {
		prev_node = q.extractMin();			
		it = adjList[prev_node.first].begin();		
		// check each edge connetcted with the latest selected node
		while(it != adjList[prev_node.first].end()) {
			node_pos = q.findPos(it->first);
			// node_pos > 0 : this node is still in the priority queue
			if(node_pos > 0) {
				// relaxing & maintain previous-node table
				int new_cost = prev_node.second + it->second;
				if(q.cal[node_pos].second > new_cost) {
					q.decreaseKey(node_pos, new_cost);
					parent[it->first] = prev_node.first;
				}
			}
			++it;
		}
	}
}

void ssShortestPath::printEdge()
{
	std::list<std::pair<int, int> >::iterator it;
	for(int i = 0; i < num_node; ++i) {
		it = adjList[i].begin();
		std::cout << i << " ";
		while(it != adjList[i].end()) {
			std::cout << "(" << it->first << ", " << it->second << ")  ";
			++it;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void ssShortestPath::printParent()
{
	std::cout << "node_index ";
	for(int idx = 0; idx < parent.size(); ++idx) {
		std::cout << idx << " ";
	}
	std::cout << std::endl;
	
	std::cout << "parent    "; 
	for(int idx = 0; idx < parent.size(); ++idx) {
		std::cout << parent[idx] << " ";	
	}
	std::cout << std::endl;
}

int main() {
	int node_num = 8;
	ssShortestPath k(node_num);
	
	k.addEdge(0, 1, 20);
	k.addEdge(0, 3, 80);
	k.addEdge(0, 6, 90);
	k.addEdge(1, 5, 10);
	k.addEdge(2, 3, 10);
	k.addEdge(2, 5, 50);
	k.addEdge(2, 7, 20);
	k.addEdge(3, 2, 10);
	k.addEdge(3, 6, 20);
	k.addEdge(4, 1, 50);
	k.addEdge(4, 6, 30);
	k.addEdge(5, 2, 10);
	k.addEdge(5, 3, 40);
	k.addEdge(6, 0, 20);
	
	k.printEdge();
	
	PriorityQ q(node_num);
	int root = 0;
	k.Dijkstra(q, k, root);
	
	std::cout << "start from node " << root << std::endl;
	q.printCost();
	k.printParent();
	
	return 0;
}
