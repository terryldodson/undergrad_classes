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

const static double ER = 3982; //earth radius in miles

using namespace std;

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


void read_cityinfo(vector<city> &cities) {
  // write this to read data object data
  ifstream fp;
  string s;
  city temp;

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

	vector<int> adjgateway;
	vector<vector<int> > zone;
	zone.assign(6, vector<int>()); //puts 6 vectors into zone
	
//	int k = -1;

	//find gateway cities in each zone
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < cities.size(); j++) {
			if(cities[j].get_zone() == i+1 && cities[j].get_type() == "GATEWAY")
				zone[i].push_back(j);
		}
	}

	//find the minimum distance gateway city and push it back to a vector 
	for(int i = 0; i < cities.size(); i++) {
		if(cities[i].get_type() == "GATEWAY") {
			for(int j = 0; j < 6; j++) {
				int mindistance = INT_MAX;
				for(int q = 0; q < zone[j].size(); q++) {
					if(cities[zone[j][q]].get_zone() != cities[i].get_zone() && tc(0,i,j) <= 6000 && tc(0,i,j) < mindistance)
							mindistance = tc(0, i, zone[j][q]);
					if(mindistance != INT_MAX) 
						adjgateway.push_back(mindistance);
				}
			}
		}
	}

	for(int i = 0; i < cities.size(); i++) {
		
		int k = -1;

		if(cities[i].get_type() == "REGIONAL") {	
			for(int j = 0; j < cities.size(); j++) { 
				if(i == j) //dont want them to be the same
					continue;

				if(cities[j].get_type() == "REGIONAL" && cities[i].get_zone() == cities[j].get_zone()) {
					graph[i].push_back(j);
					graph[j].push_back(i);
				}
				
				if(cities[j].get_type() == "GATEWAY" && cities[i].get_zone() == cities[j].get_zone() && k == -1) {
					if(k == -1)
						k = j;
					else if(tc(0,i,j) < tc(0,i,k))
						k = j;
				}
			}

			if(k != -1) {
				graph[i].push_back(k);
				graph[k].push_back(i);
			}
		}

		if(cities[i].get_type() == "GATEWAY") {
			for(int j = 0; j < cities.size(); j++) {
				if(i == j)
					continue;

				if(cities[j].get_type() == "GATEWAY" && cities[i].get_zone() == cities[j].get_zone()) {
					graph[i].push_back(j);
					graph[j].push_back(i);
				}
				
				
				if(tc(0,i,j) == adjgateway[i]) {
					graph[i].push_back(j);
					graph[j].push_back(i);
				}
			}
	}

	for(int i = 0; i < cities.size(); i++) {
		sort(graph[i].begin(), graph[i].end());
		graph[i].erase(unique(graph[i].begin(), graph[i].end()), graph[i].end());
	}
}
}

void write_citygraph(vector<city> &cities, travelcost &tc, vector<vector<int> > &graph, ostream &out) {
	
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
//dijkstra_route() { }

int main(int argc, char *argv[]) {
  //option decoding

  //object declarations
	travelcost tc;
	vector<city> c_list;
	vector<vector<int> > g_list;

	read_cityinfo(c_list);
//	write_cityinfo(c_list);

  //set up travelcosts
	tc.fill_vector(c_list);
//	write_travelcost(tc, c_list);

  create_citygraph(c_list, tc, g_list);
  write_citygraph(c_list, tc, g_list, cout);

 /* while (not done) {
	ask for form, to cities
    dijkstra_route(from,to) 
  }*/
}
