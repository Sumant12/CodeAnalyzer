#ifndef TYPETABLE_H
#define TYPETABLE_H
/////////////////////////////////////////////////////////////////////
// TypeTable.h - Store the type information needed for dependency  //
//               Analysis between the files                        //
// ver 1.2                                                         //
//-----------------------------------------------------------------//
// Saisumanth Gopisetty (c) copyright 2015                              //
// All rights granted provided this copyright notice is retained   //
//-----------------------------------------------------------------//
// Language:    C++, Visual Studio 2015                            //
// Application: TYpe Based Dependency Analysis                     //
//              CSE687 - Object Oriented Design                    //
// Author:      Saisumanth Gopisetty, Syracuse University          //
//              sgopiset@syr.edu                                   //
/////////////////////////////////////////////////////////////////////
//*Operatins:
//*Provides a Datastructure to store the Typetable information.
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>


namespace CodeAnalysis
{
	using namespace std;
	struct StoreData {
		string name;
		string type;
		string filename;
		//string namespacel;

	};
	class TypeTable
	{
	public:
		//----< All the method below perform various simmple operations on Typetable >--------------
		using TypeInfo = std::string;
		using FileInfo = std::string;
		using TypeMap = std::unordered_map<TypeInfo, StoreData>;
		using TyeTableIterator = std::pair<TypeInfo, FileInfo>;
		TypeTable() {}
		~TypeTable() { tt_.clear(); }
		void displayTypeTable();
		void InsertIntoTT(TypeInfo ti, StoreData s1);
		TypeMap& getTypeTable() { return tt_; }
	private:
		TypeMap tt_;
	};
}
#endif
