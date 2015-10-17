#ifndef CHARMLISTG2_H
#define CHARMLISTG2_H

#include "CryptoLib.h"
#include "CharmListInt.h"
#include "CharmListStr.h"

#if ASYMMETRIC == 1

struct g2_cmp_str
{
	bool operator()(const std::string a, const std::string b) const {
		return strcmp(a.c_str(), b.c_str()) < 0;
	}
};


class CharmListG2
{
public:
	CharmListG2(void); // static list
	~CharmListG2();
    CharmListG2(const CharmListG2&);
	void insert(int, G2);
	void insert(std::string, G2);
	void append(G2&);
	CharmListInt keys();
	CharmListStr strkeys();
	int length(); // return length of lists
	std::string printAtIndex(int index);
	std::string printStrKeyIndex(int index);
	// retrieve a particular index
	G2& operator[](const std::string index);
	G2& operator[](const int index);
	CharmListG2& operator=(const CharmListG2&);
    friend std::ostream& operator<<(std::ostream&, const CharmListG2&);
private:
	int cur_index;
	std::map<int, G2> list;
	std::map<std::string, int, g2_cmp_str> strList;
};

class CharmMetaListG2
{
public:
	CharmMetaListG2(void); // static list
	~CharmMetaListG2();
    CharmMetaListG2(const CharmMetaListG2&); // copy constructor
    CharmMetaListG2& operator=(const CharmMetaListG2&);

	// consider adding remove
	void insert(int, CharmListG2);
	void insert(std::string, CharmListG2);

	void append(CharmListG2&);

	int length(); // return length of lists
	std::string printAtIndex(int index);
	std::string printStrKeyIndex(int index);

	// retrieve a particular index
	CharmListG2& operator[](const int index);
	CharmListG2& operator[](const std::string index);

    friend std::ostream& operator<<(std::ostream&, const CharmMetaListG2&);
private:
	int cur_index;
	std::map<int, CharmListG2> list;
	std::map<std::string, int, g2_cmp_str> strList;
};

#endif

#endif
