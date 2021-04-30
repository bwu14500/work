#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

/**
Hash Table for CS104 hw6
*/
class Hashtable  {
public:
	Hashtable (bool debug, unsigned int probing);
	~Hashtable ();

	void add(std::string k);
    int count(std::string k);
	void resize();
	void reportAll (std::ostream & os) const;

private:
	int hash (std::string k) const;
	int hash2(std::string k);
	std::pair<std::string, int>** data;
	int size;
	int size_num;
	int numElements;
	bool debug;
	unsigned int probing;
    bool find(std::string k);
};

#endif