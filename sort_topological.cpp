#include <iostream>
#include <vector>
#include <list>
#include <stack>


class Topo {
public :
	Topo();
	void addEdge(int start, int end, int flag);
	void DFS(int temp);
	void PrintVec();
private :
	// adjList.first : vetex index
	// adjList.second : visited or not
	std::vector< std::list< std::pair<int, int> > > adjList;
	std::stack<int> dfs;
	std::vector<int> finish;
	int v_num;
};

Topo::Topo()
{
	v_num = 7;
	adjList.resize(v_num);
	finish.resize(v_num);
}

void Topo::addEdge(int start, int end, int flag)
{
	adjList[start].push_back(std::make_pair(end, flag));
}

void Topo::DFS(int temp)
{
	int time = 1;
	int cnt = 0;
	std::list< std::pair<int, int> >::iterator it;
	dfs.push(temp);
	it = adjList[temp].begin();
	
	while(cnt != v_num) {
		if(!dfs.empty()) {
			temp = dfs.top();
		}
		if(it != adjList[temp].end()) {
			// unvisited
			if(it->second == 0) {
				it->second = 1;
				dfs.push(it->first);
				temp = dfs.top();
				it = adjList[temp].begin();
			// visited once
			} else if(it->second == 1) {
				it->second = 2;
				++it;
			// visited twice : finished
			} else if(it->second == 2) {
				++it;
			}
		} else {
			if(finish[temp] == 0) {
				finish[temp] = time++;
				++cnt;
			}			
			dfs.pop();
			if(!dfs.empty()) {
				temp = dfs.top();
				it = adjList[temp].begin();
			} else {
				for(int i = 0; i < finish.size(); ++i) {
					if(finish[i] == 0) {
						temp = i;
						dfs.push(temp);
						it = adjList[temp].begin();	
						break;
					} 
				}
			}
		}		
	}
}

void Topo::PrintVec()
{
	for(int i = 0; i < finish.size(); ++i) {
		std::cout << finish[i] << " ";
	}
	std::cout << std::endl;
}

int main() {
	Topo t;
	t.addEdge(0, 1, 0);
	t.addEdge(0, 2, 0);
	t.addEdge(1, 3, 0);
	t.addEdge(1, 4, 0);
	t.addEdge(4, 6, 0);
	t.addEdge(2, 5, 0);
	
	t.DFS(3);
	t.PrintVec();
	
	return 0;
}
