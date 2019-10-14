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

#define EARTH_RADIUS = 3982;

const static double ER = 6372.8; //earth radius in km

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
		double Haversine(city &, city &);

		float &operator()(travelcost::mode, int, int);

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

void travelcost::city2city(vector<city> &cities) {
	for(int i = 0; i < cities.size(); i++) {
		for(int j = 0; j < i; j++) {
			float dist = HaversineDistance(cities[i], cities[j]); //from one city to every other city
			dist = 25.0 * round(dist/25.0);
			dist_table.resize(cities.size() * (cities.size() + 1)) / 2;
			time_table.resize(cities.size() * (cities.size() + 1)) / 2;

		}
	}
}

float &operator()(travelcost::mode m, int i, int j) {
	return (i < j) { //i and j is city1 and city2 in integers
		? table[m][((j * (j + 1)) / 2) + i] : table[m][((i * (i + 1)) / 2) + j];
	}	
}

float deg_to_rad(float angle) { //degrees to radians
	return angle * M_PI/180.0;

float HaversineDistance(const city &city1, const city &city2)
{
	float latitudeRad1 = deg_to_rad(city1.get_latitude());
	float longitudeRad1 = deg_to_rad(city1.get_longitude());
	float latitudeRad2 = deg_to_rad(city2.get_latitude());
	float longitudeRad2 = deg_to_rad(city2.get_longitude());
 
	float diffLa = latitudeRad2 - latitudeRad1;
	float diffLo = longitudeRad2 - longitudeRad1;
 
	float computation = asin(sqrt(sin(diffLa / 2) * sin(diffLa / 2) + cos(latitudeRad1) * cos(latitudeRad2) * sin(diffLo / 2) * sin(diffLo / 2)));
	
	return 2 * ER * computation;
}

//create_citygraph() { }
//dijkstra_route() { }

int main(int argc, char *argv[])
{
  //option decoding

  //object declarations
	vector<city> c_list;

	read_cityinfo(c_list);

	write_cityinfo(c_list);

  //set up travelcosts

  //create_citygraph()

 /* while (not done) {
	ask for form, to cities
    dijkstra_route(from,to) 
  }*/
}
