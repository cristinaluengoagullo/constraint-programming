#include <gecode/int.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>
#include<fstream>
#include<map>
#include<set>

using namespace Gecode;
using namespace std;

class GraphColoring : public Space {

protected:

  // 'k' represents the number of colors. 
  IntVar k;
  // 'l' represents the color assigned to each vertex. 
  IntVarArray l;

public:

  GraphColoring(int n, const map<int,set<int> >& graph) : k(*this,0,n), l(*this,n,1,n) {
    for(map<int,set<int> >::const_iterator it = graph.begin(); it != graph.end(); it++) {
      int v = it->first;
      for(set<int>::const_iterator sit = it->second.begin(); sit != it->second.end(); sit++) {
	int u = *sit;
	rel(*this,l[v-1] != l[u-1]);
      }
    }
    rel(*this,max(l) == k);
    branch(*this, l, INT_VAR_NONE(), INT_VAL_MIN());
  }

  GraphColoring(bool share, GraphColoring& s) : Space(share, s) {
    k.update(*this, share, s.k);
    l.update(*this, share, s.l);
  }

  virtual Space* copy(bool share) {
    return new GraphColoring(share,*this);
  }

  void print(void) const {
    cout << k.val() << endl;
    for(int i = 0; i < l.size(); i++) 
      cout << i+1 << " " << l[i].val() << endl;
  }

  // constrain function
  virtual void constrain(const Space& _b) {
    const GraphColoring& b = static_cast<const GraphColoring&>(_b);
    rel(*this,k > b.k);
  }
};

int main(int argc, char* argv[]) {
  ifstream infile;
  map<int,set<int> > graph;
  int n;
  bool firstLine = true;
  infile.open(argv[1]);
  while(!infile.eof()) {
    string line;
    getline(infile,line);
    string buf; 
    stringstream ss(line); 
    vector<string> tokens; 
    while (ss >> buf)
      tokens.push_back(buf);
    if(tokens.size()) {
      if(firstLine) {
	n = atoi(tokens[0].c_str());
	firstLine = false;
      }
      else graph[atoi(tokens[0].c_str())].insert(atoi(tokens[1].c_str()));
    }
  }
  infile.close();
  GraphColoring* m = new GraphColoring(n,graph);
  BAB<GraphColoring> e(m);
  delete m;
  if(GraphColoring* s = e.next()) {
    s->print(); delete s;
    cout << "------" << endl;
  }
  return 0;
}
