#ifndef SECRETUTIL_H
#define SECRETUTIL_H

#include <string>
#include <iostream>
using namespace std;

extern "C" {
#include "util.h"
#include "policy.h"
}
#include "CharmListInt.h"
#include "CharmListZR.h"
#include "CharmListStr.h"
#include "Charm.h"

class Policy
{
public:
	charm_attribute_policy *p;
	bool isInit;
	Policy();
	Policy(std::string);
	~Policy();
	Policy(const Policy&);
	Policy& operator=(const Policy&);
    friend std::ostream& operator<<(std::ostream&, const Policy&);
};


/* implements secret sharing */
class SecretUtil
{
public: 
	SecretUtil();
	~SecretUtil();
	Policy createPolicy(std::string s);
	CharmListStr prune(Policy&, CharmListStr attrs);
	CharmListStr getAttributeList(Policy&);
	CharmListZR genShares(PairingGroup & group, ZR secret, int k, int n);
	CharmListZR genSharesForX(PairingGroup & group, ZR secret, CharmListZR & q, CharmListZR & x);
	CharmDictZR calculateSharesDict(PairingGroup & group, ZR, Policy&);
	CharmListZR calculateSharesList(PairingGroup & group, ZR, Policy&);
	CharmDictZR getCoefficients(PairingGroup & group, Policy&);
	CharmListZR recoverCoefficientsDict(PairingGroup & group, CharmListInt & list);
	CharmListZR recoverCoefficientsDict(PairingGroup & group, CharmListZR & list);
	CharmListZR intersectionSubset(PairingGroup & group, CharmListStr&, CharmListStr&, int);
};







#endif
