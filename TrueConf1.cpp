//============================================================================
// Name        : TrueConf1.cpp
// Author      : Vsevolod Pozhalostin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <map>
#include <vector>
#include<algorithm>
#include<random>
enum class Location{
	In_Vector,
	In_Map,
	In_Both_Containers,
};
void Print(const std::vector<int>& rand_vec)
{
	for(const auto& val: rand_vec)
	{
		std::cout<< val << " ";
	}
	std::cout << std::endl;
}
void Print(const std::map<int, int>& rand_map)
{
	for(const auto& p : rand_map)
	{
		std::cout<< p.second << " ";
	}
	std::cout << std::endl;
}
template<class T>
void Identify_Location(T& container, Location loc, const int value)
{
	try{
		container.at(value);
	}
	catch(...){
		container[value] = loc;
	}
	if(container[value] != loc) {
		container[value] = Location::In_Both_Containers;
	}
}
template<class T>
void Generate_Random_Elements(T& container, int N)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1,9);
	for (int i = 0; i < N; i++){
			container[i] = dist(gen);
	}
}
template<class C>
void Delete_Unique_Elements(const std::map<int, Location>& locations, C& container, bool is_vec)
{
	int i = 0;
	for(auto iter = container.begin(); iter != container.end(); i++)
	{
		if(locations.at(container[i]) != Location::In_Both_Containers)
		{
			iter = container.erase(iter);
			if(is_vec) i--;
		}
		else {
			iter++;
		}
	}
}
int main()
{
	int N;
	std::vector<int> rand_vec;
	std::map<int, int> rand_map;
	std::map<int, Location> locations;
    std::random_device rd;
	int k = rd() % 15;
	std::cout << "Enter containers size:\n";
	std::cin >> N;
	rand_vec.resize(N);
	Generate_Random_Elements(rand_vec, N);
	Generate_Random_Elements(rand_map, N);
	if(k < N)
	{
		rand_vec.erase(rand_vec.end()-k, rand_vec.end());
		rand_map.erase(rand_map.find(N-k), rand_map.end());
	}
	else
	{
		rand_map.clear();
		rand_vec.clear();
	}
	std::cout<<"Vector values:\n";
	Print(rand_vec);
	std::cout<<"Map values:\n";
	Print(rand_map);
	for(size_t i = 0; i < rand_vec.size(); i++)
	{
		Identify_Location(locations, Location::In_Vector, rand_vec[i]);
		Identify_Location(locations, Location::In_Map, rand_map[i]);
	}
	Delete_Unique_Elements(locations, rand_vec, true);
	Delete_Unique_Elements(locations, rand_map, false);
	std::cout<<"Vector values after synchronization:\n";
	Print(rand_vec);
	std::cout<<"Map values after synchronization:\n";
	Print(rand_map);
	return 0;
}

