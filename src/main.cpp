// Created by I. Ganelin
// Date 26/05/2020

#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <vector>

#include "jaroWinkler.hpp"
#include "kmeans.cpp"

using namespace std;

int main()
{
    fstream infile;
    ofstream outfile;
    std::string inFileName;
    std::string line;
    vector<std::string> buffer;
    vector<vector<double>> jaroDistanceVector;
    vector<vector<double>> jaroWinklerDistanceVector;
    
    cout << "Enter input file name (-filelist.txt- by default): ";
    if(std::getline(std::cin, line))
    {
        if(line == "")
        {
            inFileName = "filelist.txt";
        }
        cout << "Reading file: " << inFileName << endl;
    }

    infile.open(inFileName, ios::in);
    cout << "Getting the file content into a vector." << endl;
    if (infile.is_open())
    {
        std::string line;
        while(getline(infile, line))
        {
            buffer.push_back(line);
        }
    infile.close();
    }
    else // I don't want to create infinite loop, so will check the file name only once.
    {
        cout << "Could not open a file. Please make sure you have typed file name correctly." << endl;
        return -1;
    }

    cout << "Using Jaro and Jaro-Winkler metrics in order to create the distance namespaces." << endl;
    for(std::size_t i=0; i<buffer.size()-1; ++i)
    {
        vector<double> jv;
        vector<double> jwv;
        for(std::size_t j=0; j<buffer.size(); ++j) // all vectors should be of the same size
        {
            jv.push_back( jaroDistance(buffer[i], buffer[j]) );
            jwv.push_back( jaroWinklerDistance(buffer[i], buffer[j]) );
        }
        jaroDistanceVector.emplace_back( jv );
        jaroWinklerDistanceVector.emplace_back( jwv );
    }
    
    cout << "Fitting the data using k-means clastering." << endl;
    srand (time(NULL));
    
	int total_points = buffer.size()-1;
	int total_values = buffer.size();
	int K;
	int max_iterations = 50;
	vector<Point> jPoints;
	vector<Point> jwPoints;
	string point_name;

	cout << "Please enter value of K: ";
	cin >> K;
	cout << endl;

	for(int i = 0; i < total_points; i++)
	{
		vector<double> jValues;
        jValues = jaroDistanceVector[i];
        vector<double> jwValues;
        jwValues = jaroWinklerDistanceVector[i];
		
		Point jP(i, jValues);
		jPoints.push_back(jP);
			
		Point jwP(i, jwValues);
		jwPoints.push_back(jwP);
	}

	KMeans kmeans(K, total_points, total_values, max_iterations);
	kmeans.run(jPoints, "j_results.txt");
	kmeans.run(jwPoints, "jw_results.txt");
	
	cout << "Completed." << endl;
    return 0;
}
