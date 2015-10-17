#ifndef CHARMLIST_H
#define CHARMLIST_H

#include <map>
#include <string>
#include <fstream>
#include "CryptoLib.h"
#include "CharmListStr.h"
#include "CharmListInt.h"
#include "CharmListZR.h"
#include "CharmListG1.h"
#include "CharmListG2.h"
#include "CharmListGT.h"

/* forward declare Element class */
class Element;

struct e_cmp_str
{
	bool operator()(const std::string a, const std::string b) const {
		return strcmp(a.c_str(), b.c_str()) < 0;
	}
};

class CharmList
{
public:
	CharmList(void); // static list
	~CharmList();
    CharmList(const CharmList&); // copy constructor
	// consider adding remove
	void append(const char *);
	void append(std::string);
	void append(ZR&);
	void append(const ZR&);
	void append(G1&);
	void append(const G1&);
#if ASYMMETRIC == 1
	void append(G2&);
	void append(const G2&);
	void insert(int, G2&);
	void insert(int, const G2&);
	void insert(int, CharmListG2);
#endif
	void append(GT&);
	void append(const GT&);
	void append(Element&);
	void append(const Element&);
	void append(const CharmList&);

	void insert(int, int);
	void insert(int, const char *);
	void insert(int, std::string);
	void insert(int, ZR&);
	void insert(int, const ZR&);
	void insert(int, CharmListZR);
	void insert(int, G1&);
	void insert(int, const G1&);
	void insert(int, CharmListG1);
	void insert(int, GT&);
	void insert(int, const GT&);
	void insert(int, CharmListGT);
	void insert(int, CharmList);
	void insert(int, CharmListStr&);
	void insert(int, CharmListInt&);
	void insert(std::string, CharmList);
	void insert(int, Element&);
	void insert(int, const Element&);
	//void append(const CharmList&);

	int length(); // return length of lists
	std::string printAtIndex(int index);
	std::string printStrKeyIndex(int index);

	// retrieve a particular index
	CharmList operator+(const Element&) const;
	CharmList operator+(const CharmList&) const;
	Element& operator[](const int index);
	Element& operator[](const std::string index);
	CharmList& operator=(const CharmList&);
	//Element& operator=(const GT&);
    friend std::ostream& operator<<(std::ostream&, const CharmList&);
private:
	int cur_index;
	std::map<int, Element> list;
	std::map<std::string, int, e_cmp_str> strList;

};

class Element
{
public:
	// public values for now
	int type;
	int z;
	ZR zr;
	G1 g1;
	GT gt;
	CharmList aList;
	CharmListZR zrList;
	CharmListG1 g1List;
	CharmListGT gtList;
	CharmListStr sList;
	CharmListInt iList;
	std::string strPtr;
	Element();
	~Element();
	Element(int);
	Element(const char *);
	Element(std::string);
	Element(ZR&);
	Element(CharmListZR&);
	Element(G1&);
	Element(CharmListG1&);
#if ASYMMETRIC == 1
	G2 g2;
	CharmListG2 g2List;
	Element(G2&);
	Element(CharmListG2&);
 	G2 getG2(); // returns value (or copy)
 	CharmListG2 getListG2(); // returns value (or copy)
 	G2& getRefG2(); // returns reference for G2 (for cleanup)
#endif
	Element(GT&);
	Element(CharmListGT&);
	Element(CharmList&);
	Element(CharmListStr&);
	Element(CharmListInt&);
 	Element(const Element& e);
 	CharmList getList();
 	ZR getZR(); // returns value (or copy)
 	ZR& getRefZR(); // returns reference for ZR (for cleanup)
 	CharmListZR getListZR(); // returns value (or copy)
 	G1 getG1(); // getter methods
 	CharmListG1 getListG1(); // returns value (or copy)
 	G1& getRefG1(); // getter methods
 	GT getGT();
 	CharmListGT getListGT(); // returns value (or copy)
 	GT& getRefGT();
	std::string str();
	CharmListStr getListStr();
 	int getInt();
	CharmListInt getListInt();

	friend void deserialize(Element&, std::string);
	friend std::string serialize(Element&);

	CharmList operator+(const Element&) const;       // operator+()
	CharmList operator+(const CharmList&) const;
 	Element operator=(const Element& e);

    friend std::ostream& operator<<(std::ostream&, const Element&);
};

// TODO: update MetaListZR -> GT according to MetaList
class CharmMetaList
{
public:
	CharmMetaList(void); // static list
	~CharmMetaList();
    CharmMetaList(const CharmMetaList&); // copy constructor
    CharmMetaList& operator=(const CharmMetaList&);

	void insert(int, CharmList);
	void insert(std::string, CharmList);
	void append(CharmList&);

	int length(); // return length of lists
	std::string printAtIndex(int index);
	std::string printStrKeyIndex(int index);
	// retrieve a particular index
	CharmList& operator[](const int index);
	CharmList& operator[](const std::string index);
    friend std::ostream& operator<<(std::ostream&, const CharmMetaList&);
private:
	int cur_index;
	std::map<int, CharmList> list;
	std::map<std::string, int, e_cmp_str> strList;
};

/* base-64 encoding functions */
std::string _base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
std::string _base64_decode(std::string const& encoded_string);
bool is_base64(unsigned char c);

extern std::string Element_ToBytes(Element &e);
extern int Element_FromBytes(Element &e, int type, unsigned char *data);
int measureSize(CharmList & c);
int measureSize(CharmListStr & c);
int measureSize(CharmListZR & c);
int measureSize(CharmListG1 & c);
#if ASYMMETRIC == 1
int measureSize(CharmListG2 & c);
#endif
int measureSize(CharmListGT & c);
int measureSize(Element & e);

#endif
