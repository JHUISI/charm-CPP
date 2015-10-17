#ifndef CHARMLISTSTR_H
#define CHARMLISTSTR_H

#include "CryptoLib.h"

class CharmListStr
{
public:
	CharmListStr(void); // static list
	~CharmListStr();
    CharmListStr(const CharmListStr&); // copy constructor
	void append(std::string&);
	void append(std::string);
	void insert(int, std::string&);
	void insert(int, std::string);
	int length(); // return length of lists
	std::string printAtIndex(int index);
	int searchKey(std::string index);

	// retrieve a particular index
	std::string& operator[](const int index);
    CharmListStr& operator=(const CharmListStr&);
    friend std::ostream& operator<<(std::ostream&, const CharmListStr&);
private:
	int cur_index;
	std::map<int, std::string> list;
};

bool isEqual(std::string value1, std::string value2);
bool isNotEqual(std::string value1, std::string value2);
std::string concat(CharmListStr & list);
std::string GetString(std::string & list);

#endif

