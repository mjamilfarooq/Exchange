/*
 * utility_functions.cpp
 *
 *  Created on: 26/10/2018
 *      Author: jamil
 */


#include "utility_functions.h"

using namespace std;

vector<string> split_str(string str, char delimeter)
{
	vector<string> split_vector;
	string temp;
	for_each(str.begin(), str.end(), [&split_vector, delimeter, &temp](char ch){
		if ( ch == delimeter )
			{
				split_vector.push_back(temp);
				temp.clear();
			}
		else temp.push_back(ch);
	});

	if( temp != "" )
		split_vector.push_back(temp);

	return split_vector;
}

//TODO: change time format API
string current_time()
{
	auto time_now = time(nullptr);
	auto temp = string(ctime(&time_now));
	temp.pop_back();
	return temp;
}
