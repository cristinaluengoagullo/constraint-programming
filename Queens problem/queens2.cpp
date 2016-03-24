#include <gecode/int.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>

using namespace Gecode;
using namespace std;

class Queens : public Space {

protected:

  // There can only be one queen per row, so for each row, 'm' determines at which column its queen is placed.
  IntVarArray m;
  int n;

public:

  Queens(int _n) : n(_n), m(*this,_n,0,_n-1) {
    // Two queens can't be placed in the same column.
    distinct(*this,m);
    // Two queens can't be placed in the same diagonal.
    for(int i = 0; i < n; i++) {
      for(int j = i+1; j < n; j++) {
	// The horizontal distance must be different than the vertical distance.
	rel(*this,abs(m[j]-m[i]) != (j-i));
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
	if(m[i].val() == j) cout << "X ";
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
