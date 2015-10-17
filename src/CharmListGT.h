#ifndef CHARMLISTGT_H
#define CHARMLISTGT_H

#include "CryptoLib.h"

struct gt_cmp_str
{
	bool operator()(const std::string a, const std::string b) const {
		return strcmp(a.c_str(), b.c_str()) < 0;
	}
};

class CharmListGT
{
public:
	CharmListGT(void);
	~CharmListGT();
    CharmListGT(const CharmListGT&);
	void insert(int, GT);
	void insert(std::string, GT);

	void append(GT&);
	int length(); // return length of lists
	std::string printAtIndex(int index);
	std::string printStrKeyIndex(int index);
	// retrieve a particular index
	GT& operator[](const std::string index);
	GT& operator[](const int index);
	CharmListGT& operator=(const CharmListGT&);
    friend std::ostream& operator<<(std::ostream&, const CharmListGT&);
private:
	int cur_index;
	std::map<int, GT> list;
	std::map<std::string, int, gt_cmp_str> strList;
};

class CharmMetaListGT
{
public:
	CharmMetaListGT(void); // static list
	~CharmMetaListGT();
    CharmMetaListGT(const CharmMetaListGT&); // copy constructor
    CharmMetaListGT& operator=(const CharmMetaListGT&);
	// consider adding remove
	void append(CharmListGT&);

	int length(); // return length of lists
	std::string printAtIndex(int index);

	// retrieve a particular index
	CharmListGT& operator[](const int index);

    friend std::ostream& operator<<(std::ostream&, const CharmMetaListGT&);
private:
	int cur_index;
	std::map<int, CharmListGT> list;
};

#endif
