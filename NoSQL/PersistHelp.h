#pragma once
/////////////////////////////////////////////////////////////////////
// PersistHelp.h - demo one way to persist objects to XML file     //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////
/*
* This package builds wrapper classes for strings, doubles, and Widgets.
* They provide the same functionality as the wrapped type, but also
* attach methods save() and restore() to persist the wrapped type.
*
* Package operations:
* -------------------
* This package contains:
* - IPersistance2 interface - defines the methods needed to
*   serialize to XML and deserialize from XML
* - StringWrapper class that persists strings
* - DoubleWrapper class that persists doubles
* - Widget class with int and string properties
* - WidgetWrapper class that persits Widgets
*
* Required Files:
* ---------------
*   PersistHelp.h, PersistHelp.cpp,
*   Convert.h, Convert.cpp,
*   CppProperties.h, CppProperties.cpp,
*   XmlDocument.h, XmlDocument.cpp, XmlElement.h, XmlElement.cpp,
*  ---- required to build XmlDocument from file or string ----
*   XmlParser.h, XmlParser.cpp,
*   XmlElementParts.h, XmlElementParts.cpp,
*   ITokenizer.h, Tokenizer.h, Tokenizer.cpp,
*
* Build Instructions:
* -------------------
* - Uses XmlDocument, so build XmlDocument project as static library
*   after undefining its test stub
*/
#include <string>
#include <vector>
#include "Convert.h"
#include "CppProperties.h"
#include "XmlDocument.h"
#include "XmlElement.h"

using namespace XmlProcessing;

/////////////////////////////////////////////////////////////////////
// IPersistance2 interface
// - declares methods Persistance Wrappers must use
//
template<typename T>
struct IPersistance2
{
	using Xml = std::string;

	virtual ~IPersistance2() {}
	virtual IPersistance2<T>& operator=(const T& t) = 0;
	virtual operator T() = 0;
	virtual Xml save() = 0;
	virtual void restore(const Xml& xml) = 0;
	std::string id() { return typeid(*this).name(); }
};

/////////////////////////////////////////////////////////////////////
// StringWrapper class
// - wrapper classes implement the persistance interface
// - they almost certainly should be non-template classes
//   because they have to be type specific
//
class StringWrapper : public IPersistance2<std::string>
{
public:
	using Xml = std::string;
	StringWrapper(const std::string& str = "") : str_(str) {}
	StringWrapper& operator=(const std::string& s);  // covariant return type
	Xml save();
	void restore(const Xml& xml);
	operator std::string();
private:
	std::string str_;
};
//----< assignment overload >----------------------------------------

//----< saves instance state as XML string >-------------------------

//---< restores instance state from XML string >---------------------


//----< cast operator returns string member >------------------------



/////////////////////////////////////////////////////////////////////
// DoubleWrapper class
//
class DoubleWrapper : public IPersistance2<double>
{
public:
	using Xml = std::string;
	DoubleWrapper(double d = 0) : d_(d) {}
	DoubleWrapper& operator=(const double& d);
	Xml save();
	void restore(const Xml& xml);
	operator double();
private:
	double d_;
};
//----< assignment overload >----------------------------------------


//----< saves instance state as XML string >-------------------------


//---< restores instance state from XML string >---------------------


//----< cast operator returns double member >------------------------


/////////////////////////////////////////////////////////////////////
// Widget and WidgetWrapper classes
//
class Widget
{
public:
	Property<int> wint;
	Property<std::string> wstr;
};

class WidgetWrapper : public IPersistance2<Widget>
{
public:
	using Xml = std::string;
	WidgetWrapper() {};
	WidgetWrapper(Widget widget) : widget_(widget) {}
	WidgetWrapper& operator=(const Widget& widget);
	Xml save();
	void restore(const Xml& xml);
	operator Widget();
private:
	Widget widget_;
};
//----< assignment operator overload >-------------------------------



using SPtr = std::shared_ptr<AbstractXmlElement>;

//----< saves instance state as XML string >-------------------------


//---< restores instance state from XML string >---------------------

//----< cast operator returns Widget member >------------------------


