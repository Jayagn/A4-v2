#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <iostream>
#include <string>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <stdlib.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <memory>


using namespace std;
using namespace Minisat;

///////////////////////////////////////////////////////////////////////////////////

/*void add_edges(vector<int> adj[], int src, int dest)
{
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}*/

void get_vertex_cover(int vertices,vector < vector<int> > edge_storage){

    for (int k = 1; k <= vertices; ++k){
          Minisat::vec<Minisat::Lit> literals;

          Minisat::Solver solver;
          for (int ver = 0; ver< vertices; ++ver){
            for (int k_value = 0; k_value < k; ++k_value){
              static_cast<void>(solver.newVar());
            }
          }
    //At least one vertex is the ith vertex in the vertex cover
    for (int i = 0; i< k; ++i ){
        for (int j =0; j< vertices; ++j){
            literals.push(Minisat::mkLit(Minisat::Var(k*j + i)));
        }
          solver.addClause(literals);
          literals.clear();

    }
    //No one vertex can appear twice in a vertex cover
    for (int m =0;m<vertices;++m){
        for (int p =0;p<k;++p){
            for (int q =0;q<k;++q){
                if(q<p){
                literals.push(~Minisat::mkLit(Minisat::Var(k*m + q)));
                literals.push(~Minisat::mkLit(Minisat::Var(k*m + p)));
                solver.addClause(literals);
                literals.clear();

            }
    }}}
    //No more than one vertex appears in themth position of the vertex cover.
    for (int m =0;m<k;++m){
        for (int p =0;p<vertices-1;++p){
            for (int q =0;q<vertices;++q){
                if(q<p){
                literals.push(~Minisat::mkLit(Minisat::Var(k*p + m)));
                literals.push(~Minisat::mkLit(Minisat::Var(k*q + m)));
                solver.addClause(literals);
                literals.clear();
            }
    }}}
          for (int j = 0; j < edge_storage.size(); ++j) {
            for (int you = 0; you < k; ++you) {
              literals.push(Minisat::mkLit(Minisat::Var(k*edge_storage[j][0] + you)));
              literals.push(Minisat::mkLit(Minisat::Var(k*edge_storage[j][1] + you)));
            }
            solver.addClause(literals);
            literals.clear();

          }
          auto sat = solver.solve();

          if (sat) {
            for (int i = 0; i < vertices; ++i)
              for (int j = 0; j < k; ++j) {
                if (!(Minisat::toInt(solver.modelValue(i*k + j))))
                  cout << i << " ";
              }
            cout << endl;
            break;
          }

    }
}
//////////////////////////////////////////////////////////////////////////////////

int main(){
// Variables to store user input vertices , source and destination.
    int vertices;
    int nedges = 0, newedges;
    int num_of_edges = 0;
	vector<vector<int>> edge;


    //vector<int>adj[MAX];
    while (!cin.eof()){
        string input;
        getline(cin,input);
        char cmd;
        cmd = input[0];

        string word = "";
        if(cmd == 'V' || cmd == 'E')
        {
            for(auto x : input)
            {
                if(x == ' '){
                    word = "";

                }else{
                    word += x;
                }
            }
        }

        if(cmd == 'V')
        {
            vertices = stoi(word.substr(0));
        }

        if(cmd == 'E')
        {
            string edges = word.substr(0);
            edges.erase(0,1);
            edges.pop_back();
            edges.erase(remove(edges.begin(),edges.end(),'<'),edges.end());
            edges.erase(remove(edges.begin(),edges.end(),'>'),edges.end());
            istringstream f(edges);
            string s;
	    int flag;
            while (getline(f, s, ','))
            {
                if (stoi(s) >= vertices)
                {
			std::cerr<<"Error: Vertex mentioned in edge is greater than number of vertices."<<std::endl;
                    	flag = 1;
			break;
                }
            }
	    if(flag == 1){
		    flag = 0;
		    continue;
	    }
            replace(edges.begin(),edges.end(),',',' ');
            edges += ' ';
            newedges = (edges.length()/4);
            int arr[1300];

	        int index = 0;
            string number;

            for(auto x : edges)
            {
                if(x == ' ')
                {
                    stringstream ss(number);
                    ss>>arr[index];
                    number = "";
                    index++;

                }
                else
                {
                    number += x;

                }
            }

            index = 0;
            for(int i = 0;i<newedges;i++)
            {
	         	vector<int> vt;
                 for (int j=0;j<2;j++){
                    vt.push_back(arr[index]);
					index++;
                }
				edge.push_back(vt);

            }


            for(int i=0;i<newedges;i++)
            {
                for(int j=0;j<2;j++)
                {
                    nedges++;
                    num_of_edges = nedges/2;
                }
            }

            get_vertex_cover(vertices,edge);
        }



    }

    return 0;

}


