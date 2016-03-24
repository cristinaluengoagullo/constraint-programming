#include <gecode/int.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>

using namespace Gecode;
using namespace std;

class Queens : public Space {

protected:

  BoolVarArray m;
  int n;

public:

  Queens(int _n) : n(_n), m(*this,_n*_n,0,1) {
    BoolVarArray row(*this,n), column(*this,n);
    rel(*this, sum(m) == n);
    for(int i = 0; i < n; i++) {
      BoolVarArray leftDiagonal1(*this,n-i), rightDiagonal1(*this,n-i);
      for(int j = 0; j < n; j++) {
	row[j] = m[i*n+j];
	column[j] = m[j*n+i];
      }
      // Two queens can't be placed in the same row.
      rel(*this,sum(row) <= 1);
      // Two queens can't be placed in the same column.
      rel(*this,sum(column) <= 1);
      for(int k = i; k < n; k++) {
	leftDiagonal1[k-i] = m[k*n+k-i];
	rightDiagonal1[k-i] = m[(n-k-1)*n+(n-k-1)+i];
      }
      // Two queens can't be placed in the same bottom left diagonal (\\).
      rel(*this,sum(leftDiagonal1) <= 1);
      // Two queens can't be placed in the same top right diagonal.
      rel(*this,sum(rightDiagonal1) <= 1);
      if(i == 0) {
	for(int j = 0; j < n; j++) {
	  BoolVarArray leftDiagonal2(*this,j+1), rightDiagonal2(*this,j+1);
	  for(int k = 0; k <= j; k++) {
	    leftDiagonal2[j-k] = m[k*n+j-k];
	    rightDiagonal2[j-k] = m[(n-k-1)*n+(n-j-1)+k];
	  }
	  // Two queens can't be placed in the same top left diagonal (//).
	  rel(*this,sum(leftDiagonal2) <= 1);
	  // Two queens can't be placed in the same bottom right diagonal.
	  rel(*this,sum(rightDiagonal2) <= 1);
	}
      }
    }
    // Policy: first unassigned and largest value.
    branch(*this, m, INT_VAR_NONE(), INT_VAL_MAX());
  }
  
  // Copy constructor.
  Queens(bool share, Queens& q) : Space(share, q) {
    m.update(*this, share, q.m);
    n = q.n;
  }

  // Copy function.
  virtual Space* copy(bool share) {
    return new Queens(share,*this);
  }

  void print(void) const {
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
	if(m[i*n+j].one()) cout << "X ";
	else cout << ". ";
      }
      cout << endl;
    }
  }
};

int main(int argc, char* argv[]) {
  try {
    Queens* q = new Queens(atoi(argv[1]));
    // 'Depth first search' search engine.
    DFS<Queens> e(q);
    delete q;
    while(Queens* s = e.next()) {
      s->print(); delete s;
      cout << endl << "----------------" << endl;
    }
  } catch (Exception e) {
    cerr << "Gecode exception: " << e.what() << endl;
    return 1;
  }
  return 0;
}
