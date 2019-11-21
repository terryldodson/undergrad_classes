#include <stdlib.h>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include <set>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <limits.h>
#include <limits>
#include <stack>
#include <map>

const static double ER = 3982; //earth radius in miles

using namespace std;

typedef enum {WHITE, BLACK} vcolor_t;

class city {
	private:
		string name;
		string type;
		int zone;
		float latitude;
		float longitude;
		int population;
	public:
		string get_name();
		string get_type();
		int get_zone();
		float get_latitude();
		float get_longitude();
		int get_population();

		friend istream &operator>>(istream &, city &);
		friend ostream &operator<<(ostream &, const city &);
};

class travelcost {
	public:
		float HaversineDistance(city &, city &);
		float &operator()(int , int , int );
		void fill_vector(vector<city>&);
		void dijkstra(int ,int, int, vector<city> &, travelcost &, vector<vector<int> > &);
	private:
		vector<float> dist_table;
		vector<float> time_table;
};

istream &operator>>(istream &in, city &c) { 
	in >> c.zone >> c.name >> c.type >> c.latitude >> c.longitude >> c.population;

	return in;	
}

ostream &operator<<(ostream &out, const city &c) { 
	out << setw(18) << c.name << setw(12) << c.type << setw(2) << c.zone << setw(8) << fixed << setprecision(2) << c.latitude << setw(8) << setprecision(2) << c.longitude << setw(10) << c.population;

	return out;
}


void read_cityinfo(map<string, int> &bs, vector<city> &cities) {
	// write this to read data object data
	ifstream fp;
	string s;
	city temp;
	int i = 0;

	fp.open("city_list.txt");

	while(getline(fp, s)) {
		if(s.empty()) {

		}

		else if(s.find('#') != string::npos) {

		}

		else {
			istringstream is(s);
			is >> temp;
			cities.push_back(temp);
			bs.insert(make_pair(temp.get_name(), i));
			i++;
		}
	}
}

void write_cityinfo(vector<city> &cities) {
	vector<city>::iterator it;

	for(it = cities.begin(); it != cities.end(); ++it) {
		cout << *it << endl;
	}
}

string city::get_name() {
	return name; 
}

string city::get_type() {
	return type;
}

int city::get_zone() {
	return zone;
}

float city::get_latitude() {
	return latitude;
}

float city::get_longitude() {
	return longitude;
}

int city::get_population() {
	return population;
}

void travelcost::fill_vector(vector<city> &cities) {
	//resize vectors then fill the vectors
	dist_table.resize(cities.size() * (cities.size() + 1) / 2);
	time_table.resize(cities.size() * (cities.size() + 1) / 2);

	for(int i = 1; i < cities.size(); i++) {
		for(int j = 0; j < i; j++) {
			float dist = HaversineDistance(cities[i], cities[j]); //from one city to every other city
			(*this)(0,i,j) = 25.0 * round(dist/25.0);

			if(cities[i].get_zone() == cities[j].get_zone() && cities[i].get_type() == "REGIONAL" && cities[j].get_type() == "REGIONAL")
				(*this)(1,i,j) = ((*this)(0,i,j))/65.0f;

			else if(cities[i].get_zone() == cities[j].get_zone() && ((cities[i].get_type() == "REGIONAL" && cities[j].get_type() == "GATEWAY") || (cities[i].get_type() == "GATEWAY" && cities[j].get_type() == "REGIONAL")))
				(*this)(1,i,j) = ((*this)(0,i,j))/520.0f;

			else if(cities[i].get_type() == "GATEWAY" && cities[j].get_type() == "GATEWAY")
				(*this)(1,i,j) = ((*this)(0,i,j))/520.0f;

			else
				(*this)(1,i,j) = ((*this)(0,i,j))/520.0f;
		}
	}
}

void write_travelcost(travelcost tc, vector<city> &cities) {
	for(int i = 1; i < cities.size(); i++) {
		for(int j = 0; j < i; j++) {
			cout << cities[i].get_name() << " to " << cities[j].get_name() << "........." << tc(0,i,j) << " miles" <<  endl;
			cout << cities[i].get_name() << " to " << cities[j].get_name() << "........." << setprecision(1) << fixed << tc(1,i,j) << " hours" <<  endl;
		}

		cout << endl;
	}
}

float &travelcost::operator()(int m, int i, int j) {
	//i and j is city1 and city2 in integers
	if(i < j)
		swap(i, j);

	if(m == 0)
		return dist_table[((i * (i + 1)) / 2) + j];
	else
		return time_table[((i * (i + 1)) / 2) + j];
}

float deg_to_rad(float angle) { //degrees to radians
	return angle * M_PI/180.0;
}

float travelcost::HaversineDistance(city &city1, city &city2) {
	float latitudeRad1 = deg_to_rad(city1.get_latitude());
	float longitudeRad1 = deg_to_rad(city1.get_longitude());
	float latitudeRad2 = deg_to_rad(city2.get_latitude());
	float longitudeRad2 = deg_to_rad(city2.get_longitude());

	float diffLa = fabsf(latitudeRad2 - latitudeRad1);
	float diffLo = fabsf(longitudeRad2 - longitudeRad1);

	float computation = asin(sqrt(pow(sin(diffLa / 2), 2) + cos(latitudeRad1) * cos(latitudeRad2) * pow(sin(diffLo / 2), 2)));

	return 2 * ER * computation;
}

void create_citygraph(vector<city> &cities, travelcost &tc, vector< vector<int> > &graph) { 
	graph.resize(cities.size());

	int k = -1;

	for(int i = 0; i < cities.size(); i++) {

		if(cities[i].get_type() == "REGIONAL") {	
			int mini_gate = -1;
			float mini_distance = 50000.0f;

			for(int j = 0; j < cities.size(); j++) { 
				float tmp = tc(0, i, j);

				if(i == j)
					continue;

				if(cities[j].get_type() == "REGIONAL" && cities[i].get_zone() == cities[j].get_zone() && i != j) {
					graph[i].push_back(j);
					graph[j].push_back(i);
				}

				if(cities[j].get_type() == "GATEWAY" && cities[i].get_zone() == cities[j].get_zone() && (mini_gate == -1 || tmp <= mini_distance)) {
					mini_gate = j;
					mini_distance = tmp;
				}
			}

			graph[i].push_back(mini_gate);
			graph[mini_gate].push_back(i);
		}

		if(cities[i].get_type() == "GATEWAY") {
			
			int min_index = -1;
            float mini_dist = 6001.0f;
            int previous_zone = -1; // keeps track of what zone last city was in
				
			for(int j = 0; j < cities.size(); j++) {
				float tmp = tc(0, i, j);

				if(cities[j].get_type() == "GATEWAY" && cities[i].get_zone() == cities[j].get_zone() && i != j) {
					graph[i].push_back(j);
					graph[j].push_back(i);
				}

				else if(cities[j].get_type() == "GATEWAY" && tmp <= 6000.0f && i != j) {
					if(cities[j].get_zone() != previous_zone) {
						if(min_index != -1) {
							graph[i].push_back(min_index);
							graph[min_index].push_back(i);
						}
					
						mini_dist = tmp;
						min_index = j;
					}
	
					else if (tmp < mini_dist) {
						mini_dist = tmp;
						min_index = j;	
					}

					previous_zone = cities[j].get_zone();
				}
			}

			graph[i].push_back(min_index);
			graph[min_index].push_back(i);
		}

		for(int i = 0; i < cities.size(); i++) {
			sort(graph[i].begin(), graph[i].end());
			graph[i].erase(unique(graph[i].begin(), graph[i].end()), graph[i].end());
		}
	}
}

void write_citygraph(vector<city> &cities, travelcost &tc, vector<vector<int> > &graph, ostream& out) {

	unsigned int i, j, sz, jsz, c_id;

	sz = cities.size();
	out << "CITY GRAPH:\n";

	cout << graph.size() << endl;

	for(i = 0; i < sz; i++) {
		jsz = graph[i].size();
		out << "\n" << setw(3) << right << i << " " << cities[i].get_name() << "\n";

		for(j = 0; j < jsz; j++) {
			c_id = graph[i][j];

			out << setw(6) << right << c_id << " " 
				<< setw(8) << left << cities[c_id].get_name() << " "
				<< fixed << setprecision(1) 
				<< setw(7) << right << tc(0, i, c_id) << " miles "
				<< setw(5) << right << tc(1, i, c_id) << " hours\n";
		}
	}
}

void travelcost::dijkstra(int source, int sink, int m, vector<city> &cities, travelcost &tc, vector<vector<int> > &graph) {  
	vector<vcolor_t> vcolor;
	vector<float> vdist;
	vector<int> vlink;

	vcolor.assign(cities.size(), WHITE);  
	vdist.assign(cities.size(), numeric_limits<float>::max());  
	vlink.assign(cities.size(), -1);

	vdist[source] = 0;  
	vlink[source] = source;  

	while (1) {    
		int next_i = -1;    
		float mindist = numeric_limits<float>::max();    

		for (int i = 0; i < (int) vcolor.size(); i++) {      
			if (vcolor[i] == WHITE && mindist > vdist[i]) {        
				next_i = i;        
				mindist = vdist[i];      
			}    
		}    

		int i = next_i;    
		if (i == -1)      
			break;    

		vcolor[i] = BLACK;    

		for (int k = 0; k < (int) graph[i].size(); k++) {      
			int j = graph[i][k];      
			float wij = tc(m, i, j);
      
			if (vcolor[j] == WHITE) {        
				if (vdist[j] > vdist[i] + wij) {          
					vdist[j] = vdist[i] + wij;          
					vlink[j] = i;        
				}      
			}    
		}  
	}

	//printing for dijsktra
	stack<int> path;
	float total_miles, total_hours;

	//setup the stack
	int ii = sink, jj = source, kk;
	float dist, time;

	while(ii != source) {
		path.push(ii);
		ii = vlink[ii];
	}
	path.push(source);

	//setup the counters
	total_miles = total_hours = 0.0f;

	//okay ready
	while(!path.empty()) {
		kk = jj;
		jj = path.top();

		path.pop();

		if(jj != source) {
			dist = tc(0, kk, jj);
			time = tc(1, kk, jj);

			total_miles += dist;
			total_hours += time;
		}

		cout << fixed << setprecision(1)
			<< setw(7) << right << total_miles << " miles "
			<< setw(5) << right << total_hours << " hours :"
			<< setw(3) << right << jj << " "
			<< setw(18) << left << cities[jj].get_name();

		if (jj != source) {
			cout << fixed << setprecision(1)
				<< setw(7) << right << dist << " miles "
				<< setw(5) << right << time << " hours";
		}

		cout << "\n";
	}
	cout << "\n";
}

int main(int argc, char *argv[]) {
	//option decoding
	int mode1;

	if(argc != 2) {
		cerr << "Usage: ./citysim -graphinfo/-distance \n";
		exit(0);
	}
	
	string mode = argv[1];

	if(mode != "-distance" && mode != "-time" && mode != "-graphinfo") {
		cerr << "Usage: ./Citysim -graphinfo/time/distance \n";
		exit(0);
	}
	
	if(mode == "-distance")
		mode1 = 0;
	else if (mode == "-time")
		mode1 = 1;

	//object declarations
	city village;
	string city1, city2;
	map<string,int> bs;
	travelcost tc;
	vector<city> c_list;
	vector<vector<int> > g_list;

	read_cityinfo(bs, c_list);
	tc.fill_vector(c_list);
	create_citygraph(c_list, tc, g_list);
	
	if(mode == "-graphinfo") {
		write_cityinfo(c_list);;
		write_travelcost(tc, c_list);
		write_citygraph(c_list, tc, g_list, cout);

		return 0;
	}
	
	while (1) {
		//link cities to index values with a map
		cout << "Enter> ";
		if(!(cin >> city1 >> city2))
			break;
		tc.dijkstra(bs[city1], bs[city2], mode1, c_list, tc, g_list); 
	}
	
	cout << "\n";
}
