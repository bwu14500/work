#include "hashtable.h"
#include <iostream>
#include <utility>  
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h> 


using namespace std;

int r[5] ={983132572, 62337998, 552714139, 984953261, 261934300};

int m[28] = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 
411527, 823117, 1646237, 3292489, 6584983, 13169977, 26339969, 52679969, 105359969, 210719881, 
421439783, 842879579, 1685759167}; 

int p[28] = {7, 19, 43, 89, 193, 389, 787, 1583, 3191, 6397, 12841, 25703, 51431, 102871, 205721, 
411503, 823051, 1646221, 3292463, 6584957, 13169963, 26339921, 52679927, 105359939, 210719881, 
421439749, 842879563, 1685759113};


/**
Hash function 1
*/
int Hashtable::hash(string k) const
{
	// 26^5 a1 + 26^4 a2 + 26^3 a3 + 26^2 a4 + 26 a5 + a6
	// a=0,b=1,c=2,...,z=25 
	//(r1 w1 + r2 w2 + r3 w3 + r4 w4 + r5 w5) % m
	int w[] = {0,0,0,0,0};
	const char* s = k.c_str();
	int j = 0;
	int num = 0;
	int num2 = 4;
	for (int i = strlen(s) - 1; i >= 0; --i){
		int temp = s[i]-'a';
		num += temp*pow(26,j);
		++j;
		if (j == 6){
			w[num2] = num;
			--num2;
			num = 0;
			j = 0;
		}
	}	
	if (num > 0){
		w[num2] = num;
	}
	int result = 0;
	for (int q = 0; q < 5; ++q){
		long long temp1 = (long long)w[q]*(long long)r[q];
		result += temp1 % size;
	}
	result = result % size;
	return result;
}

/**
Second Hash function for double hashing
*/
int Hashtable::hash2(string k) 
{
	const char* s = k.c_str();
	int w[] = {0,0,0,0,0};
	int j = 0;
	int num = 0;
	int num2 = 4;
	for (int i = strlen(s) - 1; i >= 0; --i){
		int temp = s[i]-'a';
		num += temp*pow(26,j);
		++j;
		if (j == 6){
			w[num2] = num;
			--num2;
			num = 0;
			j = 0;
		}
	}	
	if (num > 0){
		w[num2] = num;
	}
	// h(w) = p - ((w1+w2+w3+w4+w5) % p)
	long long temp  = 0;
	for (int i = 0; i < 5; ++i){
		temp += (long long)w[i] % (long long)p[size_num];
	}
	temp = temp % (long long)p[size_num];
	int result = p[size_num] - temp;
	return result;
}

/**
Creates a hash table of the given condition.
*/
// probing: 0 means that your Hashtable must use linear probing, 1 means quadratic probing, and 2 means double hashing.
Hashtable::Hashtable(bool debug, unsigned int probing) {
	srand (time(NULL));
	this->size_num = 0;
	this->numElements = 0;
	this->debug = debug;
	this->probing = probing;
	this->size = m[size_num];
	if (!debug){
		for (int i = 0; i < 5; ++i){
			r[i] = rand() % size;
		}
	}
	data = new std::pair<std::string, int>*[size];
}

/**
Destructor
*/
Hashtable::~Hashtable() {
	for(int i = 0; i < size; i++){
		if (data[i] != nullptr) delete data[i];
	}
	delete[] data;
}

/**
resize the hashtable using the m array
*/
void Hashtable::resize(){
	int old_size = size;
	this->size_num = this->size_num + 1;
	this->size = m[size_num];
	if (!debug){
		for (int i = 0; i < 5; ++i){
			r[i] = rand() % size;
		}
	}
	pair<std::string, int>** new_data = new std::pair<std::string, int>*[size];
	for(int j = 0; j < old_size; ++j) {
		if (data[j] != nullptr){
			string word = data[j]->first;
			int num = data[j]->second;
			int h1 = hash(word);
			int h = h1;
			int count = 1;
			for(int i = 0; i < size; ++i) {
				if(new_data[h] == nullptr) {
					pair<string,int>* temp = new pair<string,int>(word,num);
					new_data[h] = temp;
					break;
				}
				if (probing == 0){ // linear probing
					h = h1 + count;
				}
				else if (probing == 1){ // quadratic probing
					h = h1 + pow(count,2);
				}
				else{  // double hashing
					int h2 = hash2(word);
					h = h1 + count*h2;
				}
				++count;
				h = h % size;
			}
			delete data[j];
		}
	}
	delete[] data;
	this->data = new_data;
}


/**
add should do add 1 to the number of the string if the string already exists in the hash table.
*/
void Hashtable::add(string k) {
	double loading = (10*numElements)/(this->size);
	if (loading >= 5){
		this->resize();
	}
	int h1 = hash(k);
	int h = h1;
	int count = 1;
	for(int i = 0; i < size; ++i) {
		if(data[h] == nullptr) {
			pair<string,int>* temp = new pair<string,int>(k,1);
			data[h] = temp;
			break;
		}
		else if(data[h]->first == k){
			data[h]->second = data[h]->second + 1;
			break;
		}
		else{
			if (probing == 0){ // linear probing
				h = h1 + count;
			}
			else if (probing == 1){ // quadratic probing
				h = h1 + pow(count,2);
			}
			else{  // double hashing
				int h2 = hash2(k);
				h = h1 + count*h2;
			}
			++count;
			h = h % size;
		}
	}
	++numElements;
}

/**
Returns the int associated with k, or 0 if k is not in the Hashtable.
*/
int Hashtable::count(string k) {
	int h1 = hash(k);
	int h = h1;
	int count = 1;
	for(int i = 0; i < size; ++i) {
		if(data[h] == nullptr) return 0;
		else if(data[h]->first == k) return data[h]->second;
		else{
			if (probing == 0){ // linear probing
				h = h1 + count;
			}
			else if (probing == 1){ // quadratic probing
				h = h1 + pow(count,2);
			}
			else{  // double hashing
				int h2 = hash2(k);
				h = h1 + count*h2;
			}
			++count;
			h = h % size;
		}
	}
	return 0;
}


/**
output, to the given stream, every (key,value) pair, in the order they appear in the hashtable; on each line,
output the key, followed by a space, followed by the value, and then a newline.
*/
void Hashtable::reportAll (ostream & os) const {
	for(int i = 0; i < size; i++) {
		if (data[i] != nullptr){
			os << data[i]->first << " " << data[i]->second << endl;
		}
	}
}