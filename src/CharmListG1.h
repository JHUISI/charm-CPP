#ifndef CHARMLISTG1_H
#define CHARMLISTG1_H

#include "CryptoLib.h"
#include "CharmListInt.h"
#include "CharmListStr.h"

struct g_cmp_str
{
    bool operator()(const std::string a, const std::string b) const {
        return strcmp(a.c_str(), b.c_str()) < 0;
    }
};

class CharmListG1
{
public:
	CharmListG1(void); // static list
	~CharmListG1();
    CharmListG1(const CharmListG1&);
	void insert(int, G1);
	void insert(std::string, G1);
	void append(G1&);
	void set(int index, G1);
//	G1& get(const int index);
	CharmListInt keys();
	CharmListStr strkeys();
	int length(); // return length of lists
	std::string printAtIndex(int index);
	std::string printStrKeyIndex(int index);
	// retrieve a particular index
	G1& operator[](const std::string index);
	G1& operator[](const int index);
	CharmListG1& operator=(const CharmListG1&);
    friend std::ostream& operator<<(std::ostream&, const CharmListG1&);
private:
	int cur_index;
	std::map<int, G1> list;
	std::map<std::string, int, g_cmp_str> strList;
};

class CharmMetaListG1
{
public:
	CharmMetaListG1(void); // static list
	~CharmMetaListG1();
    CharmMetaListG1(const CharmMetaListG1&); // copy constructor
    CharmMetaListG1& operator=(const CharmMetaListG1&);

	// consider adding remove
	void insert(int, CharmListG1);
	void insert(std::string, CharmListG1);
	void append(CharmListG1&);

	int length(); // return length of lists
	std::string printAtIndex(int index);
	std::string printStrKeyIndex(int index);
	// retrieve a particular index
	CharmListG1& operator[](const int index);
	CharmListG1& operator[](const std::string index);

    friend std::ostream& operator<<(std::ostream&, const CharmMetaListG1&);
private:
	int cur_index;
	std::map<int, CharmListG1> list;
	std::map<std::string, int, g_cmp_str> strList;
};

#endif
