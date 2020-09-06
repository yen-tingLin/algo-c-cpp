#include <iostream>
#include <vector>

#define for_each(i,x) for(int i = 0; i < x; ++i)

class Queens {
public :
	Queens(int n);
	void backTracking();
	bool queenFound(int row);
	void printQueens();
private :
	int size;
	std::vector<int> chosen; 
};

Queens::Queens(int n)
{
	size = n;
	chosen.resize(size);
}

void Queens::backTracking()
{
	int row = 0;
	bool solved = queenFound(row);
	if(solved) {
		printQueens();
	} else {
		std::cout << "no solutions" << std::endl;
	}
}

bool Queens::queenFound(int row)
{
	if(row == size) return true;
		
	for_each(col, size) {
		bool promising = true;
		for_each(queen, row) {
			if(col == chosen[queen] || row + col == queen + chosen[queen] || row - col == queen - chosen[queen]) {
				promising = false;
				break;
			}
		}
		if(promising) {
			chosen[row] = col;
			if(queenFound(row+1)) return true;
		}
	}
	return false;
}

void Queens::printQueens()
{
	for_each(i, size) std::cout << "(" << i << ", " << chosen[i] << ") ";
	std::cout << std::endl;
}

int main() {
	Queens q(5);
	q.backTracking();
	
	return 0;
}
