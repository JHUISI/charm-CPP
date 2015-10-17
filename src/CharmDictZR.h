#ifndef CHARMDICTZR_H
#define CHARMDICTZR_H

#include "CryptoLib.h"
#include "CharmListStr.h"

struct cmp_str
{
	bool operator()(const std::string a, const std::string b) const {
		return strcmp(a.c_str(), b.c_str()) < 0;
	}
};

class CharmDictZR
{
public:
	CharmDictZR(void); // static list
	~CharmDictZR();
    CharmDictZR(const CharmDictZR&); // copy constructor

	int length(); // return length of lists
	CharmListStr keys(); // vector<std::string>
	std::string printAll();
	void set(std::string key, ZR& value);

	// retrieve a particular index
	ZR& operator[](const std::string key);
    CharmDictZR& operator=(const CharmDictZR&);
    friend std::ostream& operator<<(std::ostream&, const CharmDictZR&);
private:
	std::map<std::string, ZR, cmp_str> emap;
};

/*
class CharmDict
{
public:
	CharmDict(void); // static list
	~CharmDict();
	// consider adding remove
	void set(std::string key, Element& value);
	int length(); // return length of lists
	CharmList keys(); // vector<std::string>
	std::string printAll();

	// retrieve a particular index
	Element& operator[](const std::string key);
    friend std::ostream& operator<<(std::ostream&, const CharmDict&);

private:
	std::map<std::string, Element, cmp_str> emap;
};
*/

#endif
