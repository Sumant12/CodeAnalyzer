#pragma once
/////////////////////////////////////////////////////////////////////////
// TypeTable.cpp - Provides a container class that stores type         //
//                 information needed for dependency analysis.         //
// ver 1.0                                                             //
// Language:    C++, Visual Studio 2015                                //
// Application: Support for DepAnal, CSE687 - Object Oriented Design   //
// Author:      Jashwanth Reddy, Syracuse University,                  //
//              jgangula@syr.edu                                       //
/////////////////////////////////////////////////////////////////////////

#include "TypeTable.h"
#include "../Utilities/Utilities.h"
#include <iomanip>

using namespace CodeAnalysis;
using namespace Utilities;

void TypeTable::displayTypeTable()
{
	Utilities::StringHelper::Title("Displaying the TypeTable Information");

	std::cout << "\n";

	string name;
	StoreData s1;

	//cout << setw(25) << setfill(' ') << "Name" << setw(25) << setfill(' ') << "Type" << setw(25) << setfill(' ') << "FileName" << endl;
	cout << "------------------------------------------------------------------------------------" << endl;
	cout << setw(45) << setfill(' ') << "Name" << setw(45) << setfill(' ') << "Type" << setw(45) << setfill(' ') << "FileName" << endl;
	cout << "------------------------------------------------------------------------------------" << endl;
	for (std::unordered_map<string, StoreData>::iterator it = tt_.begin(); it != tt_.end(); ++it) {
		name = it->first;
		s1 = it->second;
		//cout << name << "			 " << s1.type << "				" << s1.filename << endl;
		cout << setw(45) << setfill(' ') << name << setw(45) << setfill(' ') << s1.type << setw(45) << setfill(' ') << s1.filename << endl;
	}



}

void TypeTable::InsertIntoTT(TypeInfo ti, StoreData fi)
{
	if (tt_.find(ti) == tt_.end())
	{
		tt_[ti] = fi;
	}
}

#ifdef TEST_TYPETABLE
int main()
{
	return 0;
}
#endif