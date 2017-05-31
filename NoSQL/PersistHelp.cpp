/////////////////////////////////////////////////////////////////////
// PersistHelp.cpp - demo one way to persist objects to XML file   //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////

//* Maintenance History :
//*--------------------
//After Downloading the project from Professor Fawcett's code repo,
//* Ver 1.0 - Febrauary 6, 2017
//#ifdef TEST_PERSISTHELP
/*
* - You can define and undefine using
*   project > Properties > C/C++ > Preprocessor > Processor Definitions
* - or using command line
*   cl /DTEST_PERSISTHELP persist.cpp [plus all the other cpp files needed]
*/

#include "PersistHelp.h"
#include <iostream>
//#include "../Utilities/Utilities.h"

/*----< overload insertion operator for const std::string properties >---*/

//std::ostream& operator<<(std::ostream& out, Property<const std::string>& p)
//{
//	std::string temp = p;
//	try {
//		out << (temp).c_str();
//	}
//	catch (std::exception& ex)
//	{
//		std::cout << "\n  exception:\n  " << ex.what() << "\n";
//	}
//	return out;
//}
//
///*----< overload insertion operator for std::string properties >---*/
//std::ostream& operator<<(std::ostream& out, Property<std::string>& p)
//{
//	std::string temp = p;
//	try {
//		out << (temp).c_str();
//	}
//	catch (std::exception& ex)
//	{
//		std::cout << "\n  exception:\n  " << ex.what() << "\n";
//	}
//	return out;
//}

StringWrapper& StringWrapper::operator=(const std::string& s)
{
	str_ = s;
	return *this;
}

StringWrapper::Xml StringWrapper::save()
{
	return "<StringWrapper>" + str_ + "</StringWrapper>";
}

StringWrapper::operator std::string()
{
	return str_;
}

void StringWrapper::restore(const Xml& xml)
{
	size_t posStart = xml.find_first_of(">") + 1;
	size_t posEnd = xml.find_last_of("</");
	str_ = xml.substr(posStart, posEnd - posStart - 1);
}

DoubleWrapper& DoubleWrapper::operator=(const double& d)
{
	d_ = d;
	return *this;
}

DoubleWrapper::Xml DoubleWrapper::save()
{
	return "<DoubleWrapper>" + Convert<double>::toString(d_) + "</DoubleWrapper>";
}

void DoubleWrapper::restore(const Xml& xml)
{
	size_t posStart = xml.find_first_of(">") + 1;
	size_t posEnd = xml.find_last_of("</");
	std::string bodyString = xml.substr(posStart, posEnd - posStart - 1);
	d_ = Convert<double>::fromString(bodyString);
}


DoubleWrapper::operator double()
{
	return d_;
}

WidgetWrapper& WidgetWrapper::operator=(const Widget& widget)
{
	widget_ = widget;
	return *this;
}

WidgetWrapper::Xml WidgetWrapper::save()
{
	XmlDocument doc;

	// make and add root element to doc
	SPtr root = makeTaggedElement("WidgetWrapper");
	doc.docElement() = root;

	// make Property<int> wint element and add to root
	int wintValue = static_cast<Widget>(*this).wint;
	std::string wintStr = Convert<int>::toString(wintValue);
	SPtr pWintElem = makeTaggedElement("wint");
	pWintElem->addChild(makeTextElement(wintStr));
	root->addChild(pWintElem);

	// make Property<std::string> wstr element and add to root
	std::string wStr = static_cast<Widget>(*this).wstr;
	SPtr pWstrElem = makeTaggedElement("wstr");
	pWstrElem->addChild(makeTextElement(wStr));
	root->addChild(pWstrElem);
	return doc.toString();
}

void WidgetWrapper::restore(const Xml& xml)
{
	XmlDocument doc(xml);
	std::vector<SPtr> elems = doc.element("wint").select();
	std::string temp = elems[0]->children()[0]->value();
	widget_.wint = Convert<int>::fromString(temp);
	elems = doc.element("wstr").select();
	widget_.wstr = elems[0]->children()[0]->value();
}

WidgetWrapper::operator Widget()
{
	return widget_;
}

#ifdef Persist_Test



int main()
{
	//Title("Demonstrate Persisting to and from XML");
	//putLine();

	//subTitle("Persisting a string");
	StringWrapper sw("Hello World");
	sw = "hello world";     // using assignment overload
	std::string temp = sw;  // using implicit cast
	std::cout << "\n  StringWrapper state = " << static_cast<std::string>(sw);
	StringWrapper::Xml xml = sw.save();
	std::cout << "\n  XML saved from StringWrapper = " << xml;
	StringWrapper newSw;
	newSw.restore(xml);
	std::cout << "\n  id of restored StringWrapper = " << newSw.id();
	std::cout << "\n  restored StringWrapper state = " << static_cast<std::string>(newSw);
	//putLine();
	//subTitle("Persisting a double");
	DoubleWrapper dw(3.1415927);
	DoubleWrapper::Xml xmlD = dw.save();
	std::cout << "\n  DoubleWrapper state = " << static_cast<double>(dw);
	std::cout << "\n  XML saved from DoubleWrapper = " << xmlD;
	DoubleWrapper newDw;
	newDw.restore(xmlD);
	std::cout << "\n  id of restored DoubleWrapper = " << newDw.id();
	std::cout << "\n  restored DoubleWrapper state = " << static_cast<double>(newDw);
	//putLine();
	//subTitle("Persisting a Widget");
	Widget wdgt;
	wdgt.wint = 42;
	wdgt.wstr = "Fred";
	WidgetWrapper wwdgt(wdgt);
	std::cout << "\n  WidgetWrapper state:";
	std::cout << "\n    wint = " << static_cast<Widget>(wwdgt).wint;
	std::cout << "\n    wstr = " << static_cast<Widget>(wwdgt).wstr;
	WidgetWrapper::Xml xmlW = wwdgt.save();
	std::cout << "\n  XML saved from WidgetWrapper:" << xmlW;
	WidgetWrapper newWwdgt;
	newWwdgt.restore(xmlW);
	std::cout << "\n  id of restored WidgetWrapper = " << newWwdgt.id();
	std::cout << "\n  WidgetWrapper state:";
	std::cout << "\n    wint = " << static_cast<Widget>(newWwdgt).wint;
	std::cout << "\n    wstr = " << static_cast<Widget>(newWwdgt).wstr;
	getchar();
}

#endif // Persist_Test
