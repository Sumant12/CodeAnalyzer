/////////////////////////////////////////////////////////////////////
// NoSqlDb.cpp - key/value pair in-memory database                   //
// ver 1.0                                                         //
// Application: An implementation of NoSQL database using templates//
// Platform:    Apple Macbbok pro, Win 8.1 Pro, Visual Studio 2013 //
// Author:      Saisumanth Gopisetty,Graduate student,			   //
//				Computer Engineering, Syracuse University          //
//              sgopiset@syr.edu								   //
//Proffessor:						                               //
//Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////
//* Opearations:
//*	Can perform operations on the NoSqlDB using the templates declared 
//* in the NoSqlDb.h


//* Required Files :
//*-------------- -
//* NoSqlDb.h

//* Maintenance History :
//*--------------------
//* Ver 1.0 - Febrauary 6, 2017

#include "NoSqlDb.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>
#include <fstream>

#include "CppProperties.h"
#include "XmlDocument.h"
#include "XmlElement.h"
#include "PersistHelp.h"
#include "StrHelper.h"


using namespace std;
//----< Overloads the == operator so thet db object is returned >--------------
DBWrapper& DBWrapper::operator=(const NoSqlDb<StrData>& db)
{
	db_ = db;
	return *this;
}

//----< Overloads the = operator so the it returns the element >--------------
ElementWrapper& ElementWrapper::operator=(const Element<StrData>& elem)
{
	elem_ = elem;
	return *this;
}

//----< Builds the Element document from the elem_ >--------------
ElementWrapper::Xml ElementWrapper::save()
{
	SPtr pRoot = makeTaggedElement("element");
	SPtr pNameElem = makeTaggedElement("key");
	SPtr pTextElem1 = makeTextElement(elem_.name);
	pNameElem->addChild(pTextElem1);
	pRoot->addChild(pNameElem);

	SPtr pvalElem = makeTaggedElement("value");

	SPtr pcategoryElem = makeTaggedElement("category");
	SPtr pTextElem2 = makeTextElement(elem_.category);
	pcategoryElem->addChild(pTextElem2);
	pvalElem->addChild(pcategoryElem);
	SPtr ptimeElem = makeTaggedElement("time");
	SPtr pTextElem3 = makeTextElement(elem_.timeDate);
	ptimeElem->addChild(pTextElem3);
	pvalElem->addChild(ptimeElem);
	SPtr pdescElem = makeTaggedElement("description");
	SPtr pTextElem4 = makeTextElement(elem_.description);
	pdescElem->addChild(pTextElem4);
	pvalElem->addChild(pdescElem);
	SPtr pdataElem = makeTaggedElement("data");
	SPtr pTextElem5 = makeTextElement(elem_.data);
	pdataElem->addChild(pTextElem5);
	pvalElem->addChild(pdataElem);
	SPtr pchildElem = makeTaggedElement("children");
	vector<string> elemchildren = elem_.children;
	std::vector<string>::iterator it = elemchildren.begin();
	for (it; it != elemchildren.end(); it++)
	{
		SPtr pChildKey = makeTaggedElement("key");
		SPtr pTextElem6 = makeTextElement(*it);
		pChildKey->addChild(pTextElem6);
		pchildElem->addChild(pChildKey);
	}
	pvalElem->addChild(pchildElem);
	pRoot->addChild(pvalElem);
	return pRoot->toString();
}

//----< Restores the element object from the xml document >--------------
void ElementWrapper::restore(const Xml& xml)
{
	try
	{
		XmlDocument doc(xml);
		vector<SPtr> Element = doc.elements("element").select();
		vector<string> elemchildren = elem_.children;
		elemchildren.clear();
		for (auto pElem : Element)
		{
			if (pElem->value().compare("key") == 0)
				elem_.name = trim(pElem->children()[0]->value());
			else if (pElem->value().compare("value") == 0)
			{
				vector<SPtr> valChild = pElem->children();
				vector<string> elemchildren = elem_.children;
				for (auto pElem2 : valChild)
				{
					if (pElem2->value().compare("description") == 0)
						elem_.description = trim(pElem2->children()[0]->value());
					else if (pElem2->value().compare("time") == 0)
						elem_.timeDate = trim(pElem2->children()[0]->value());
					else if (pElem2->value().compare("category") == 0)
						elem_.category = trim(pElem2->children()[0]->value());
					else if (pElem2->value().compare("data") == 0)
						elem_.data = trim(pElem2->children()[0]->value());
					else if (pElem2->value().compare("children") == 0)
					{
						vector<SPtr> pElem3 = pElem2->children();
						for (auto pElem4 : pElem3)
						{
							if (pElem4->value().compare("key") == 0)
								elemchildren.push_back(trim(pElem4->children()[0]->value()));
						}
						elem_.children = elemchildren;
					}
				}
			}
		}
	}
	catch (std::exception& ex)
	{
		std::cout << "\n something bad happened in restoring the element ";
		std::cout << "\n " << ex.what();
	}
}

//----< Displays the content of the Element<StrData> >--------------
//template<typename Data>
//std::string Element<Data>::showElement()
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

template<typename Data>
void Element<Data>::fit()
{
	
//	return std::string("Hello element");
	std::cout << "Hello Element" << endl;
}

//----< Displays the content of the Element<Widget> >--------------
template<typename Data>
std::string Element<Data>::showwidget()
{
	std::ostringstream out;
	out.setf(std::ios::adjustfield, std::ios::left);
	out << "\n    " << std::setw(8) << "name" << " : " << name;
	out << "\n    " << std::setw(8) << "category" << " : " << category;
	out << "\n    " << std::setw(8) << "description" << " : " << description;
	out << "\n    " << std::setw(8) << "children" << " : " << convertVectorToString(children);
	out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
	out << "\n";
	return out.str();
}
//----< Saves the instance of the db object into an xml >--------------
DBWrapper::Xml DBWrapper::save()
{
	XmlDocument doc;
	try {
		// make and add root element to doc
		SPtr root = makeTaggedElement("store");
		doc.docElement() = root;

		/*Use keys of key for now just use iterator */
		vector<string> getKeys = db_.keys();
		vector<string>::iterator it = getKeys.begin();
		for (it; it != getKeys.end(); it++)
		{
			Element<StrData> elem = db_.value(*it);
			ElementWrapper ew(elem);
			SPtr textElem = makeTextElement(ew.save());
			//	ew.restore(ew.save());
			root->addChild(textElem);
		}
	}
	catch (exception e) {
		cout << "An exception occured in save method of DBWrapper" << endl;
	}
	return doc.toString();
}


//----< Restores the db object from the xml >--------------
void DBWrapper::restore(const Xml& xml)
{
	try
	{
		XmlDocument doc(xml);
		vector<SPtr> childElem = doc.elements("store").select();
		for (auto pElem : childElem)
		{
			if (pElem->value().compare("element") == 0)
			{
				//	cout << "Element found in the datastore " << endl;
				ElementWrapper ew;
				ew.restore(pElem->toString());
				Element<StrData> restoreElem = static_cast<Element<StrData>>(ew);
				//restoreElem = ew.operator Element<StrData>();
				db_.save(restoreElem.name, restoreElem);
			}
		}
	}
	catch (std::exception& ex)
	{
		std::cout << "\n something bad happened in restroing the database in the restore method ";
		std::cout << "\n " << ex.what();
	}
}

void erase(std::vector<string>& v, string str)
{
	std::vector<string>::iterator iter = v.begin();

	while (iter != v.end())
	{
		if (*iter == str)
			iter = v.erase(iter);
		else
			iter++;
	}

}

std::string convertVectorToString(vector<string> vec) {
	std::ostringstream oss;
	string res;

	// Convert all but the last element to avoid a trailing ","
	if (!vec.empty()) {
		std::copy(vec.begin(), vec.end() - 1,
			std::ostream_iterator<string>(oss, ","));

		// Now add the last element with no delimiter
		oss << vec.back();

		res = oss.str();

	}

	return res;
}

#ifdef TEST_NoSqlDb

using StrData = std::string;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

int main()
{
	cout << " Test stub for NoSqlDb" << endl;
	cout << " Teststub demonstrates that an element can be created and store in the NoSqlDb.";
	NoSqlDb<StrData> db(10);
	Element<StrData> elem1;
	elem1.name = "elem1";
	elem1.category = "mycategory";
	elem1.data = "mydata";
	elem1.description = "mydescription";
	elem1.timeDate = "2010/05/02  13:00:03";
	db.save(elem1.name, elem1);
	std::cout << "\n  Retrieving elements from NoSqlDb<string>";
	std::cout << "\n ------------------------------------------\n";

	std::cout << "\n  size of db = " << db.count() << "\n";
	Keys keys = db.keys();
	for (Key key : keys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}

	std::cout << "\n\n";
	getchar();
	return 0;
}

#endif