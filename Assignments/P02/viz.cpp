      ///////////////////////////////////////////////////////////////////////////////
      //                   
      // Author:           Trevor Amann
      // Email:            trevor.amann9@gmail.com
      // Label:            P02
      // Title:            Graphviz Class 
      // Course:           CMPS 2143
      // Semester:         Spring 2021
      //
      // Description:
      //    This program takes a list of nodes and egdes and turns them into the graphviz format so we can create 
      //    nice graphs.   
      //
      // Usage:
      //       Run the program with your input file to get graphviz format.  
      //
      // Files:   viz.cpp input.dat (or whatever your input file is)
      /////////////////////////////////////////////////////////////////////////////////



      #include <iostream> 
      #include <string>
      #include <vector>
      #include <sstream>
      #include <fstream> 

      using namespace std;

      //This is my Node class. It gets and sets the label, name, and shape. It also puts the node into graphviz format. 
      class Node{
        private:
            string label;
            string name;
            string shape;
        public:
            Node(){
                label = "Default";
                name = "Default";
                shape = "ellipse";
            }
            Node(string n, string l){
                name = n;
                label = l;
            }
            string dot(){
                return name + " [label=\"" + label + "\" shape=\"" + shape + "\"]"; 
                //returns string of graphviz format
            } 
            void setName(string n){
                name = n; 
            }
            string getName(){
                return name;
            }
            void setShape(string s){
                shape = s;
            }
            string getShape(){
                return shape;
            }
            void setLabel(string l){
                label = l;
            }
            string getLabel(){
                return label;
            }

      };
      //This is the edge class, it sets and gets the arrow type, name, and the label for the edge. 
      class Edge{
        private:
            string arrow;
            string start_name;
            string end_name; 
            string label;

        public:
            Edge() {
                string label = "Default";
                string arrow = "diamond";
                string start_name = "Default";
                string end_name = "Default";

            }
            Edge(string s, string e, string l){
                start_name = s;
                end_name = e;
                label = l;
            }
            string dot(string type){
                string edge_op;
                if(type == "digraph"){
                    edge_op = "->";
                }
                else{
                    edge_op = "--";
                }
                return start_name + edge_op + end_name + " [label=\"" + label + "\" arrow=\"" + arrow + "\"]"; 
                    //returns string of graphviz format
            }
            void setArrow(string s){
                arrow = s;
            }
            string getArrow(){
                return arrow; 
            }
            void setLabel(string l){
                label = l;
            }
            string getLabel(){
                return label;
            }
            void setStart(string start){
                start_name = start;
            }
            string getStart(){
                return start_name;
            }
            void setEnd(string end){
                end_name = end;
            }
            string getEnd(){
                return end_name;
            }
      };
      //This is my graph class. This class sets the type, name, and the output format. 
      class Graph{
        private:
            string name;
            string type;


        public:

        Graph() {
            type = "digraph";
            name = "P02";

        }
        Graph(string t, string n){
            type = t;
            name = n;

        }
        string dotStart(){
            return type + " " + name + " {"; 
        }
        string dotEnd(){
            return "}";
        }
        void setName(string n){
            name = n;
        }
        string getName(){
            return name;
        }
        void setType(string t){
            type = t;
        }
        string getType(){
            return type; 
        }
      };

      /**
      * THIS FUNCTION IS FROM PROFESSOR TERRY GRIFFIN. Borrowed it to help me with the program. 
      * Crappy function to clean leading and trailing spaces from 
      * a string. 
      */
      string trim(string stuff){
        int start = 0;
        int end = stuff.size();
        for(int i=0;i<stuff.size();i++,start++){
            if(stuff[i] != ' '){
                break;
            }
        }
        for(int i=stuff.size()-1;i>=0;i--,end--){
            if(stuff[i] != ' '){
                break;
            }
        }
        cerr << "Stuff: [" << stuff << "]" << endl; 
        cerr << start <<  " " << end << endl;
        return stuff.substr(start,end-start); 
      }

      /**
      * THIS CODE IS FROM PROFESSOR TERRY GRIFFIN. Borrowed it to help me with the program. 
      * Splits a string on a given delimiter and returns a vector
      * with each individual token.
      * 
      * Example:
      * 
      *      string test = "  one, two  , three, four,    five   ";
      *      test = splitString(test,',');
      *      
      *      would result in a vector with: ["one","two","three","four","five"]
      * 
      */
      vector< string > splitString(string the_string, char delimiter) {
        vector< string > result;
        stringstream     s_stream(the_string);  //create string stream from the string
        cerr << "String: " << the_string << endl;
        while (s_stream.good()) {
            string substr;
            getline(s_stream, substr, delimiter);  //get first string delimited by comma
            cerr << "substring: " << substr << endl;
            result.push_back(trim(substr));
        }
        return result;
      }

      //main file that searches through and splits the string then sends the proper stuff 
      //through their functions to output in graphviz format. 
      int main() {
        ifstream fin;
        fin.open("input.dat");
        string line;
        vector<string> result;
        int numLines;
        Graph g;


        getline(fin, line);
        g.setType(trim(line));
        g.setName("G1");
        ofstream fout;
        fout.open("Test");
        fout << g.dotStart() << endl;
        getline(fin, line);
        numLines = stoi(line);
        for(int i = 0; !fin.eof() && (i < numLines); i++){
            result.clear();
            getline(fin,line);
            result = splitString(line,',');
            for(int j = 0; j < result.size(); j++){
                cerr << "Result: " << result.at(j) << endl;
            }
            if(result.size() > 1){
                Node n(result.at(0), result.at(1));    
                fout << n.dot() << endl;
            }
        }
        getline(fin, line);
        numLines = stoi(line);
        for (int i = 0; !fin.eof() && (i < numLines); i++){
            result.clear();
            getline(fin, line);
            result = splitString(line, ',');
            if(result.size() > 2){
                Edge e(result.at(0), result.at(1), result.at(2));
                fout << e.dot(g.getType()) << endl;
            }
        }
        fout << g.dotEnd() << endl;




        return 0;
      }
