#pragma once
/////////////////////////////////////////////////////////////////////
// NoSqlDb.h - key/value pair in-memory database                   //
// ver 1.0                                                         //
// Application: An implementation of NoSQL database using templates//
// Platform:    Apple Macbbok pro, Win 8.1 Pro, Visual Studio 2013 //
// Author:      Saisumanth Gopisetty,Graduate student,			   //
//				Computer Engineering, Syracuse University          //
//              sgopiset@syr.edu								   //
//Proffessor:						                               //
//Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////

//* Operations :
//*------------------ -
//* NoSQL database constructed as part of this project is a key value 
//* type database which is generalized for any 'Data' type using the power 
//* tempalates in cpp
//*
//* This package provides a complete implementation of NoSQL Database.
//* The prime functionalities are:
//* 1. The Data type which the user wants to store is generic. 
//* 2. The user can store elements of his custom type, Add keys to the store,
//* Edit the metadata and Data of a key, Add or delete relations of an Element.
//* 3. Persistance mechanism has been implemented. The store can be populated 
//* from an xml and the store can be persisted to an xml using commands.
//* 4. Query mechanism has been implemented which enables the user to query on the
//* database, querying on the keys filtered from a query, Union of multiple queries.
//* XmlParser objects throw if given an invalid path to an XML file.

//* Class operations:
//* Element: It is the class which corresponds to every element in the store.
//* NoSqlDB: It is the class which corresponds to the database store.
//* ElementWrapper: This class provides a wrapper so that Element can be persisted 
//* to the xml.
//* DBWrapper: This class provides a wrapper so that the the store can be persisted 
//* to the xml.


//* Required Files :
//*-------------- -
//*-XmlDocument.h, XmlDocument.cpp,
//*XmlElement.h, XmlElement.cpp
//*CppProperties.h,CppProperties.cpp
//*PersistHelp.h,PersistHelp.cpp
//*StrHelper.h



//* Maintenance History :
//*--------------------
//* Ver 1.0 - Febrauary 6, 2017

//* Build Process :
//*--------------
//*   devenv NoSQL.sln / debug rebuild



#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include<regex>
#include<set>
#include "CppProperties.h"
#include "XmlDocument.h"
#include "XmlElement.h"
#include "PersistHelp.h"
#include "StrHelper.h"
#include <fstream>
using namespace std;
using namespace std;
using namespace XmlProcessing;
using SPtr = std::shared_ptr<AbstractXmlElement>;
using StrData = std::string; // added by me

							 /////////////////////////////////////////////////////////////////////
							 // Element class represents a data record in our NoSql database
							 // - In  NoSql database that is just the value in a key/value pair
							 // - It stores the child data of an element along with the Data and Metadata	
template<typename Data>
class Element
{
public:
	 
	using Name = std::string;
	using Category = std::string;
	using TimeDate = std::string;
	using Description = std::string;
	using Children = std::vector<string>;

	Property<Name> name;				// metadata
	Property<Category> category;		// metadata
	Property<TimeDate> timeDate;		// metadata
	Property<Description> description;  //metadata
	Property<Children> children;		//children
	Property<Data> data;                // data

	std::string showElement();
	void fit();
	std::string showwidget();

};

template<typename Data>
inline std::string Element<Data>::showElement()
{
	std::ostringstream out;
	out.setf(std::ios::adjustfield, std::ios::left);
	out << "\n    " << std::setw(8) << "name" << " : " << name;
	out << "\n    " << std::setw(8) << "category" << " : " << category;
	out << "\n    " << std::setw(8) << "data" << " : " << data;
	out << "\n    " << std::setw(8) << "description" << " : " << description;
	out << "\n    " << std::setw(8) << "children" << " : " << convertVectorToString(children);
	out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
	out << "\n";
	return out.str();
}

/////////////////////////////////////////////////////////////////////
// ElementWrapper class inherits from IPersistance2 interface. It provides a wrapper for
// the element class to buils the xml structure from the Element object


class ElementWrapper : public IPersistance2<Element<StrData> >
{
public:
	using Xml = std::string;
	ElementWrapper() {}
	ElementWrapper(const Element<StrData>& elem) : elem_(elem) { }
	ElementWrapper& operator=(const Element<StrData>& elem);
	Xml save();
	void restore(const Xml& xml);
	operator Element<StrData>()
	{
		return elem_;
	}
private:
	Element<StrData> elem_;
};

////----< Overloads the = operator so the it returns the element >--------------
//ElementWrapper& ElementWrapper::operator=(const Element<StrData>& elem)
//{
//	elem_ = elem;
//	return *this;
//}
//
////----< Builds the Element document from the elem_ >--------------
//ElementWrapper::Xml ElementWrapper::save()
//{
//	SPtr pRoot = makeTaggedElement("element");
//	SPtr pNameElem = makeTaggedElement("key");
//	SPtr pTextElem1 = makeTextElement(elem_.name);
//	pNameElem->addChild(pTextElem1);
//	pRoot->addChild(pNameElem);
//
//	SPtr pvalElem = makeTaggedElement("value");
//
//	SPtr pcategoryElem = makeTaggedElement("category");
//	SPtr pTextElem2 = makeTextElement(elem_.category);
//	pcategoryElem->addChild(pTextElem2);
//	pvalElem->addChild(pcategoryElem);
//	SPtr ptimeElem = makeTaggedElement("time");
//	SPtr pTextElem3 = makeTextElement(elem_.timeDate);
//	ptimeElem->addChild(pTextElem3);
//	pvalElem->addChild(ptimeElem);
//	SPtr pdescElem = makeTaggedElement("description");
//	SPtr pTextElem4 = makeTextElement(elem_.description);
//	pdescElem->addChild(pTextElem4);
//	pvalElem->addChild(pdescElem);
//	SPtr pdataElem = makeTaggedElement("data");
//	SPtr pTextElem5 = makeTextElement(elem_.data);
//	pdataElem->addChild(pTextElem5);
//	pvalElem->addChild(pdataElem);
//	SPtr pchildElem = makeTaggedElement("children");
//	vector<string> elemchildren = elem_.children;
//	std::vector<string>::iterator it = elemchildren.begin();
//	for (it; it != elemchildren.end(); it++)
//	{
//		SPtr pChildKey = makeTaggedElement("key");
//		SPtr pTextElem6 = makeTextElement(*it);
//		pChildKey->addChild(pTextElem6);
//		pchildElem->addChild(pChildKey);
//	}
//	pvalElem->addChild(pchildElem);
//	pRoot->addChild(pvalElem);
//	return pRoot->toString();
//}
//
////----< Restores the element object from the xml document >--------------
//void ElementWrapper::restore(const Xml& xml)
//{
//	try
//	{
//		XmlDocument doc(xml);
//		vector<SPtr> Element = doc.elements("element").select();
//		vector<string> elemchildren = elem_.children;
//		elemchildren.clear();
//		for (auto pElem : Element)
//		{
//			if (pElem->value().compare("key") == 0)
//				elem_.name = trim(pElem->children()[0]->value());
//			else if (pElem->value().compare("value") == 0)
//			{
//				vector<SPtr> valChild = pElem->children();
//				vector<string> elemchildren = elem_.children;
//				for (auto pElem2 : valChild)
//				{
//					if (pElem2->value().compare("description") == 0)
//						elem_.description = trim(pElem2->children()[0]->value());
//					else if (pElem2->value().compare("time") == 0)
//						elem_.timeDate = trim(pElem2->children()[0]->value());
//					else if (pElem2->value().compare("category") == 0)
//						elem_.category = trim(pElem2->children()[0]->value());
//					else if (pElem2->value().compare("data") == 0)
//						elem_.data = trim(pElem2->children()[0]->value());
//					else if (pElem2->value().compare("children") == 0)
//					{
//						vector<SPtr> pElem3 = pElem2->children();
//						for (auto pElem4 : pElem3)
//						{
//							if (pElem4->value().compare("key") == 0)
//								elemchildren.push_back(trim(pElem4->children()[0]->value()));
//						}
//						elem_.children = elemchildren;
//					}
//				}
//			}
//		}
//	}
//	catch (std::exception& ex)
//	{
//		std::cout << "\n something bad happened in restoring the element ";
//		std::cout << "\n " << ex.what();
//	}
//}
//
////----< Displays the content of the Element<StrData> >--------------
//template<typename Data>
//std::string Element<Data>::show()
//{
//	std::ostringstream out;
//	out.setf(std::ios::adjustfield, std::ios::left);
//	out << "\n    " << std::setw(8) << "name" << " : " << name;
//	out << "\n    " << std::setw(8) << "category" << " : " << category;
//	out << "\n    " << std::setw(8) << "data" << " : " << data;
//	out << "\n    " << std::setw(8) << "description" << " : " << description;
//	out << "\n    " << std::setw(8) << "children" << " : " << convertVectorToString(children);
//	out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
//	out << "\n";
//	return out.str();
//}
//
////----< Displays the content of the Element<Widget> >--------------
//template<typename Data>
//std::string Element<Data>::showwidget()
//{
//	std::ostringstream out;
//	out.setf(std::ios::adjustfield, std::ios::left);
//	out << "\n    " << std::setw(8) << "name" << " : " << name;
//	out << "\n    " << std::setw(8) << "category" << " : " << category;
//	out << "\n    " << std::setw(8) << "description" << " : " << description;
//	out << "\n    " << std::setw(8) << "children" << " : " << convertVectorToString(children);
//	out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
//	out << "\n";
//	return out.str();
//}




/////////////////////////////////////////////////////////////////////
// NoSqlDb class is a key/value pair in-memory database
// - stores and retrieves elements
// - Query mechanism has been made integral part of NoSqlDb
//   That should probably be another class that uses NoSqlDb

template<typename Data>
class NoSqlDb
{
public:
	using Xml = std::string;
	using Key = std::string;
	using Keys = std::vector<Key>;
	NoSqlDb() {}
	NoSqlDb(int in) {
		threshold = in;
	}

	Keys keys();
	bool save(Key key, Element<Data> elem);
	void deleteKey(Element<Data> ele);
	void AddChildren(string parent, Element<Data> child);
	void DeleteChildren(string parent, Element<Data> child);
	Element<Data> value(Key key);
	void EditValue(string name, string data, string type);
	size_t count();
	vector<string> MatchKeys(vector<string> input, string str);
	vector<string> MatchKeysWithSameData(vector<string> input, string str);
	vector<string> MatchKeysWithSameCategory(vector<string> input, string str);
	vector<string> MatchKeysInTimeInterval(vector<string> input, string time1, string time2);
	vector<string> MatchKeysInTimeInterval(vector<string> input, string time1);
	std::set<string> UnionOfQueries(vector<string> v1, vector<string> v2);
	std::set<string> UnionOfQueries(vector<string> v1, vector<string> v2, vector<string> v3);
	time_t getEpochFromVector(vector<string> v1);
	time_t getEpochfromString(string str);

private:
	using Item = std::pair<Key, Element<Data>>;
	//static  int counter;
	std::string type;
	std::unordered_map<Key, Element<Data>> store;
public:
	static  int counter;
	int threshold = 10;
};
template<typename Data>
int NoSqlDb<Data>::counter = 0;

//----< Returns the keys of the NoSqlDB > >--------------
template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
	Keys keys;
	for (Item item : store)
	{
		keys.push_back(item.first);
	}
	return keys;
}

//----< stores the Element to the NoSqlDB >--------------
template<typename Data>
bool NoSqlDb<Data>::save(Key key, Element<Data> elem)
{
	/*if (store.find(key) != store.end())
	return false;*/
	store[key] = elem;
	counter = counter + 1;
	//cout << "The counter is " << counter << endl;
	return true;
}

//----< Returns the value of a key >--------------
template<typename Data>
Element<Data> NoSqlDb<Data>::value(Key key)
{
	if (store.find(key) != store.end())
		/*Element<Data> Value = store[key];
		Value.show();*/
		return store[key];

	else {
		cout << "The element is not found in the store" << endl;
		return Element<Data>();
	}

}

//----< Returns the epoch time from the vector of timestamp data >--------------
template<typename Data>
time_t NoSqlDb<Data>::getEpochFromVector(vector<string> v1) {

	struct tm t = { 0 };  // Initalize to all 0's
	t.tm_year = stoi(v1.at(0)) - 1900;  // This is year-1900, so 112 = 2012
	t.tm_mon = stoi(v1.at(1));
	t.tm_mday = stoi(v1.at(2));
	t.tm_hour = stoi(v1.at(3));
	t.tm_min = stoi(v1.at(4));
	t.tm_sec = stoi(v1.at(5));
	time_t timeSinceEpoch = mktime(&t);
	return timeSinceEpoch;
}

//----< Returns the epcoh time from the timestamp string >--------------
template<typename Data>
time_t NoSqlDb<Data>::getEpochfromString(string str) {
	//parze the str and load all to a vector so that epcoh time can be obtained from the function getEpochFromVector
	std::vector<std::string> wholevector;
	std::istringstream iss(str);
	for (std::string s; iss >> str; ) {
		wholevector.push_back(str);
	}
	string Date = wholevector.at(0);
	string Time = wholevector.at(1);
	string word;
	stringstream stream(Date);
	vector<string> result;
	while (getline(stream, word, '/')) {
		result.push_back(word);
	}
	string word1;
	stringstream stream1(Time);
	vector<string> TimeVector;
	while (getline(stream1, word1, ':')) {
		result.push_back(word1);
	}
	time_t epochtime = getEpochFromVector(result);
	return epochtime;
}


//----< Returns the size of the store >--------------
template<typename Data>
size_t NoSqlDb<Data>::count()
{
	return store.size();
}

//----< Returns the keys which match the specified pattern >--------------
template<typename Data>
vector<string> NoSqlDb<Data>::MatchKeys(vector<string> input, string str)
{
	vector<string> keyset = input;
	vector<string> result;
	try {
		//Regex pattern to find a substring in a string
		regex e("[a-z1-9 ]*(" + str + ")[ a-z1-9]*");


		for (string str : keyset) {
			if (regex_match(str, e)) {
				result.push_back(str);
			}
		}
	}
	catch (exception e) {
		cout << "Exception Occured" << endl;
		cout << "The pattern you are searching has some error" << endl;
	}
	if (!(result.empty())) {
		return result;
	}
	else {
		// cout << "    No keys are fetched matching the pattern" << endl;
		return keyset;
	}


}


//----< Returns the keys whose Data matches the specified pattern >--------------
template<typename Data>
vector<string> NoSqlDb<Data>::MatchKeysWithSameData(vector<string> input, string str)
{
	Keys keyset = input;
	vector<string> result;
	try {
		//Regex pattern to find a substring in a string
		regex e("[a-z1-9 ]*(" + str + ")[ a-z1-9]*");
		for (Key key : keyset) {

			Element<Data> res = value(key);
			string cat = res.data;
			if (regex_match(cat, e)) {
				result.push_back(res.name);
			}
		}
	}
	catch (exception e) {
		cout << "Exception Occured" << endl;
		cout << "The pattern you are searching has some error" << endl;
	}
	if (!(result.empty())) {
		return result;
	}
	else {
		//cout << "No keys are fetched matching the pattern" << endl;
		result.push_back("No matches");
		return result;
	}

}

//----< Returns the keys whose category matches the specified pattern >--------------
template<typename Data>
vector<string> NoSqlDb<Data>::MatchKeysWithSameCategory(vector<string> input, string str)
{

	Keys keyset = input;
	vector<string> result;
	try {
		//Regex pattern to find a substring in a string
		regex e("[a-z1-9 ]*(" + str + ")[ a-z1-9]*");
		for (Key key : keyset) {
			Element<Data> res = value(key);
			string cat = res.category;
			if (regex_match(cat, e)) {
				result.push_back(res.name);
			}
		}
	}
	catch (exception e) {
		cout << "Exception Occured" << endl;
		cout << "The pattern you are searching has some error" << endl;
	}
	if (!(result.empty())) {
		return result;
	}
	else {
		cout << "No keys are fetched matching the pattern" << endl;
		result.push_back("No matches");
		return result;
	}


}


//----< Returns the keys whose whose timestamp is in the specified timestamps >--------------
template<typename Data>
vector<string> NoSqlDb<Data>::MatchKeysInTimeInterval(vector<string> input, string time1, string time2)
{
	Keys keyset = input;
	vector<string> result;
	try {

		time_t t1 = getEpochfromString(time1);
		time_t t2 = getEpochfromString(time2);
		for (Key key : keyset) {
			Element<Data> res = value(key);
			string timestampstring = res.timeDate;
			time_t timestamp = getEpochfromString(timestampstring);
			if (timestamp >= t1 && timestamp <= t2) {
				result.push_back(res.name);
			}
		}
		if (result.empty()) {
			result.push_back("No matched found");
		}
	}
	catch (exception e) {
		cout << "There is an exception in the method MatchKeysInTimeInterval" << endl;
	}
	return result;
}

//----< Returns the keys whose whose timestamp is after a specified timestamp >--------------
template<typename Data>
vector<string> NoSqlDb<Data>::MatchKeysInTimeInterval(vector<string> input, string time1)
{
	vector<string> result;
	try {
		time_t t1 = getEpochfromString(time1);
		time_t t2 = time(0);
		Keys keyset = input;
		for (Key key : keyset) {

			Element<Data> res = value(key);
			string timestampstring = res.timeDate;
			time_t timestamp = getEpochfromString(timestampstring);
			if (timestamp >= t1 && timestamp <= t2) {
				result.push_back(res.name);
			}

		}

		if (result.empty()) {
			result.push_back("No matched found");
		}
	}
	catch (exception e) {
		cout << "There is an exception in the method MatchKeysInTimeInterval" << endl;
	}
	return result;
}

//----< Returns the keys which are union of 2 queries >--------------
template<typename Data>
set<string> NoSqlDb<Data>::UnionOfQueries(vector<string> v1, vector<string> v2)
{
	set<string> result;
	try {
		Keys vec1 = v1;
		Keys vec2 = v2;

		for (Key key : vec1) {
			result.insert(key);

		}
		for (Key key : vec2) {
			result.insert(key);
		}
	}
	catch (exception e) {
		cout << "There is an exception in the method UnionOfQueries" << endl;
	}

	return result;
}
//----< Returns the keys whose which are union of 3 queries >--------------
template<typename Data>
std::set<string> NoSqlDb<Data>::UnionOfQueries(vector<string> v1, vector<string> v2, vector<string> v3)
{
	set<string> result;
	try {
		Keys vec1 = v1;
		Keys vec2 = v2;
		Keys vec3 = v3;

		for (Key key : vec1) {
			result.insert(key);

		}
		for (Key key : vec2) {
			result.insert(key);
		}
		for (Key key : vec3) {
			result.insert(key);
		}
	}
	catch (exception e) {
		cout << "There is an exception in the method UnionOfQueries" << endl;
	}
	return result;
}



//----< Deletes a key from the store >--------------
template<typename Data>
void NoSqlDb<Data>::deleteKey(Element<Data> ele)

{
	Keys keyset = keys();
	try {
		if (store.find(ele.name) != store.end()) {


			for (Key key : keyset) {
				Element<Data> element = value(key);
				vector<string> childvector = element.children;
				string name = ele.name;
				if (std::find(childvector.begin(), childvector.end(), name) != childvector.end()) {
					erase(childvector, name);
					element.children = childvector;
					save(element.name, element);
				}
			}

			store.erase(ele.name);

		}
		else {
			cout << "The element is not found in the store" << endl;
		}
		counter = counter + 1;
		//cout << "The counter is " << counter << endl;
	}
	catch (exception e) {
		cout << "An exception has been thrown in deleteKey method" << endl;
	}
}

//----< Adds children to a key which is in the store >--------------
template<typename Data>
void NoSqlDb<Data>::AddChildren(string parent, Element<Data> child)
{
	try {
		if (store.find(parent) != store.end()) {
			Element<Data> element = value(parent);

			if (store.find(child.name) != store.end()) {
				//cout << "The Child which is to be added is present in the store" << endl;
				vector<string> vec1;
				vec1 = element.children;
				vec1.push_back(child.name);
				element.children = vec1;
				store[parent] = element;
				counter = counter + 1;
				//cout << "The counter is " << counter << endl;
			}
			else {
				cout << "The element which you are trying to add is not present in the store" << endl;
			}
		}

		else {
			cout << "The element for which you are trying to add children is not present in the store" << endl;
		}
	}
	catch (exception e) {
		cout << "An exception has been thrown in AddChildren method" << endl;
	}
}

//----< A function which deletes an element from a vector >--------------
void erase(std::vector<string>& v, string str);

//----< A function which displays the vector in the form of a string >--------------
std::string convertVectorToString(vector<string> vec);


//----< Deletes specified children from a parent key >--------------
template<typename Data>
void NoSqlDb<Data>::DeleteChildren(string parent, Element<Data> child)
{
	try {
		if (store.find(parent) != store.end()) {
			Keys keyset = keys();

			Element<Data> element = value(parent);
			vector<string> vec1;
			vec1 = element.children;

			erase(vec1, child.name);
			element.children = vec1;
			store[parent] = element;
			counter = counter + 1;
			//cout << "The counter is " << counter << endl;
		}
	}
	catch (exception e) {
		cout << "An exception occured in DeleteChildren method" << endl;
	}
}


//----< Edits the metadata of a key in the store >--------------
template<typename Data>
void NoSqlDb<Data>::EditValue(string name, string data, string type) {
	try {

		if (store.find(name) != store.end()) {
			Element<Data> element = value(name);
			if (type == "description") {
				element.description = data;
			}
			if (type == "category") {
				element.category = data;
			}
			if (type == "data") {
				element.data = data;
			}
			if (type == "timeDate") {
				element.timeDate = data;
			}
			store[name] = element;
			counter = counter + 1;
			//cout << "The counter is " << counter << endl;

		}
		else {
			cout << "The element you are trying to edit is not found in the store" << endl;
		}
	}
	catch (exception e) {
		cout << "An exception occured in DeleteChildren method" << endl;
	}
}

/////////////////////////////////////////////////////////////////////
// DBWrapper class inherits from IPersistance2 interface. It provides a wrapper for
// the NoSqlDB class to builD the xml structure from the NoSqlDB object

class DBWrapper : public IPersistance2<NoSqlDb<StrData> >
{
public:
	using Xml = std::string;
	DBWrapper()
	{}
	DBWrapper(const NoSqlDb<StrData>& db) : db_(db) { }
	DBWrapper& operator=(const NoSqlDb<StrData>& db);
	Xml save();
	void restore(const Xml& xml);
	operator NoSqlDb<StrData>()
	{
		return db_;
	}
private:
	NoSqlDb<StrData> db_;
};

////----< Overloads the == operator so thet db object is returned >--------------
//DBWrapper& DBWrapper::operator=(const NoSqlDb<StrData>& db)
//{
//	db_ = db;
//	return *this;
//}
//
////----< Saves the instance of the db object into an xml >--------------
//DBWrapper::Xml DBWrapper::save()
//{
//	XmlDocument doc;
//	try {
//		// make and add root element to doc
//		SPtr root = makeTaggedElement("store");
//		doc.docElement() = root;
//
//		/*Use keys of key for now just use iterator */
//		vector<string> getKeys = db_.keys();
//		vector<string>::iterator it = getKeys.begin();
//		for (it; it != getKeys.end(); it++)
//		{
//			Element<StrData> elem = db_.value(*it);
//			ElementWrapper ew(elem);
//			SPtr textElem = makeTextElement(ew.save());
//			//	ew.restore(ew.save());
//			root->addChild(textElem);
//		}
//	}
//	catch (exception e) {
//		cout << "An exception occured in save method of DBWrapper" << endl;
//	}
//	return doc.toString();
//}
//
//
////----< Restores the db object from the xml >--------------
//void DBWrapper::restore(const Xml& xml)
//{
//	try
//	{
//		XmlDocument doc(xml);
//		vector<SPtr> childElem = doc.elements("store").select();
//		for (auto pElem : childElem)
//		{
//			if (pElem->value().compare("element") == 0)
//			{
//				//	cout << "Element found in the datastore " << endl;
//				ElementWrapper ew;
//				ew.restore(pElem->toString());
//				Element<StrData> restoreElem = static_cast<Element<StrData>>(ew);
//				//restoreElem = ew.operator Element<StrData>();
//				db_.save(restoreElem.name, restoreElem);
//			}
//		}
//	}
//	catch (std::exception& ex)
//	{
//		std::cout << "\n something bad happened in restroing the database in the restore method ";
//		std::cout << "\n " << ex.what();
//	}
//}
