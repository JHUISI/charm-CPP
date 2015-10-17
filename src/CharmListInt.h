#ifndef CHARMLISTINT_H
#define CHARMLISTINT_H

#include "CryptoLib.h"

struct i_cmp_str
{
	bool operator()(const std::string a, const std::string b) const {
		return strcmp(a.c_str(), b.c_str()) < 0;
	}
};


class CharmListInt
{
public:
	CharmListInt(void);
	~CharmListInt();
    CharmListInt(const CharmListInt&); // copy constructor
    CharmListInt& operator=(const CharmListInt&);
	int length(); // return length of lists
	std::string printAtIndex(int index);
	void init(int list[], int length);
	bool contains(int value);

	int& operator[](const int index);
    friend std::ostream& operator<<(std::ostream&, const CharmListInt&);
private:
    int cur_index;
    std::map<int, int> intList;
};

class CharmMetaListInt
{
public:
	CharmMetaListInt(void); // static list
	~CharmMetaListInt();
    CharmMetaListInt(const CharmMetaListInt&); // copy constructor
    CharmMetaListInt& operator=(const CharmMetaListInt&);

	// consider adding remove
	void insert(int, CharmListInt);
	void insert(std::string, CharmListInt);
	void append(CharmListInt&);

	int length(); // return length of lists
	std::string printAtIndex(int index);
	std::string printStrKeyIndex(int index);
	// retrieve a particular index
	CharmListInt& operator[](const int index);
	CharmListInt& operator[](const std::string index);

    friend std::ostream& operator<<(std::ostream&, const CharmMetaListInt&);
private:
	int cur_index;
	std::map<int, CharmListInt> list;
	std::map<std::string, int, i_cmp_str> strList;
};



#endif
