//
//  DTXMLWriter.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/5/12.
//
//

#include "DTXMLWriter.h"

#include <iostream>
#include <sstream>
#include <string>

#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/xinclude/XIncludeUtils.hpp>

using namespace std;
using namespace xercesc;

# pragma mark local const data

static const XMLCh gEndElement[] = { chOpenAngle, chForwardSlash, chNull };
static const XMLCh gEndPI[] = { chQuestion, chCloseAngle, chNull };
static const XMLCh gStartPI[] = { chOpenAngle, chQuestion, chNull };
// <?xml version="1.0" encoding="
static const XMLCh gXMLDecl1[] = {
    chOpenAngle, chQuestion, chLatin_x, chLatin_m, chLatin_l
    ,   chSpace, chLatin_v, chLatin_e, chLatin_r, chLatin_s, chLatin_i
    ,   chLatin_o, chLatin_n, chEqual, chDoubleQuote, chDigit_1, chPeriod
    ,   chDigit_0, chDoubleQuote, chSpace, chLatin_e, chLatin_n, chLatin_c
    ,   chLatin_o, chLatin_d, chLatin_i, chLatin_n, chLatin_g, chEqual
    ,   chDoubleQuote, chNull
};
// " standalone="no"?>
static const XMLCh gXMLDecl2[] = {
    chDoubleQuote, chSpace, chLatin_s, chLatin_t, chLatin_a, chLatin_n, chLatin_d, chLatin_a,
    chLatin_l, chLatin_o, chLatin_n, chLatin_e, chEqual, chDoubleQuote, chLatin_n, chLatin_o,
    chDoubleQuote, chQuestion, chCloseAngle, chLF, chNull
};
static const XMLCh gYes[] = { chLatin_y, chLatin_e, chLatin_s, chNull };
static const XMLCh gNo[] = { chLatin_n, chLatin_o, chNull };

#pragma mark initialization

DTXMLWriter::DTXMLWriter(const char* const encodingName,
                         const char* const filepath) :
file(filepath),
xmlFormatter(encodingName, &file) {
}

DTXMLWriter::~DTXMLWriter() {
}

# pragma mark output

void DTXMLWriter::startDocument() {
    //  Go ahead and output an XML Decl with our known encoding. This
    //  is not the best answer, but its the best we can do until we
    //  have SAX2 support.
    xmlFormatter << gXMLDecl1 << xmlFormatter.getEncodingName() << gXMLDecl2;
}

DTXMLWriter& DTXMLWriter::startElement(string qname,
                                       pair<string,string>* attribs[],
                                       bool close) {
    // The name has to be representable without any escapes
    xmlFormatter << XMLFormatter::NoEscapes << chOpenAngle;
    xmlFormatter << XMLString::transcode(qname.c_str());
    if (attribs) {
        for (int i = 0; attribs[i] != NULL; ++i) {
            xmlFormatter << XMLFormatter::NoEscapes << chSpace;
            xmlFormatter << XMLString::transcode(attribs[i]->first.c_str());
            xmlFormatter << chEqual << chDoubleQuote
                         << XMLFormatter::AttrEscapes
                         << XMLString::transcode(attribs[i]->second.c_str())
                         << XMLFormatter::NoEscapes
                         << chDoubleQuote;
        }
    }
    if (close) xmlFormatter << chForwardSlash;
    xmlFormatter << chCloseAngle;
    return *this;
}

DTXMLWriter& DTXMLWriter::endElement(string qname) {
    // No escapes are legal here
    xmlFormatter << XMLFormatter::NoEscapes << gEndElement;
	xmlFormatter << XMLString::transcode(qname.c_str()) << chCloseAngle << chLF;
    return *this;
}

DTXMLWriter* DTXMLWriter::writeChars(string element, bool encode) {
    if (encode) {
        xmlFormatter << XMLFormatter::CharEscapes << XMLString::transcode(element.c_str());
    } else {
        xmlFormatter << XMLString::transcode(element.c_str());
    }
    return this;
}

DTXMLWriter& DTXMLWriter::writeStr(string element, bool encode) {
    if (encode) {
        xmlFormatter << XMLFormatter::CharEscapes << XMLString::transcode(element.c_str());
    } else {
        xmlFormatter << XMLString::transcode(element.c_str());
    }
    return *this;
}

DTXMLWriter& DTXMLWriter::writeInt(int element) {
    ostringstream oss;
    oss << element;
    xmlFormatter << XMLString::transcode(oss.str().c_str());
    return *this;
}

DTXMLWriter& DTXMLWriter::writeDouble(double element) {
    ostringstream oss;
    oss << element;
    xmlFormatter << XMLString::transcode(oss.str().c_str());
    return *this;
}

DTXMLWriter& DTXMLWriter::writeBoolAsYesOrNo(bool toWrite) {
    xmlFormatter << (toWrite ? gYes : gNo);
    return *this;
}

DTXMLWriter* DTXMLWriter::writeNewline() {
    xmlFormatter << chLF;
    return this;
}

DTXMLWriter& DTXMLWriter::endl() {
    xmlFormatter << chLF;
    return *this;
}

void DTXMLWriter::endDocument() {
}

