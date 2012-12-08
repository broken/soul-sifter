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

static const XMLCh  gEndElement[] = { chOpenAngle, chForwardSlash, chNull };
static const XMLCh  gEndPI[] = { chQuestion, chCloseAngle, chNull };
static const XMLCh  gStartPI[] = { chOpenAngle, chQuestion, chNull };
static const XMLCh  gXMLDecl1[] = {
    chOpenAngle, chQuestion, chLatin_x, chLatin_m, chLatin_l
    ,   chSpace, chLatin_v, chLatin_e, chLatin_r, chLatin_s, chLatin_i
    ,   chLatin_o, chLatin_n, chEqual, chDoubleQuote, chDigit_1, chPeriod
    ,   chDigit_0, chDoubleQuote, chSpace, chLatin_e, chLatin_n, chLatin_c
    ,   chLatin_o, chLatin_d, chLatin_i, chLatin_n, chLatin_g, chEqual
    ,   chDoubleQuote, chNull
};

static const XMLCh  gXMLDecl2[] = { chDoubleQuote, chQuestion, chCloseAngle, chLF, chNull };

#pragma mark initialization

DTXMLWriter::DTXMLWriter(const char* const encodingName,
                         const char* const filepath,
                         const bool expandNamespaces) :
file(filepath),
fFormatter(encodingName, &file),
fExpandNS(expandNamespaces) {
    //  Go ahead and output an XML Decl with our known encoding. This
    //  is not the best answer, but its the best we can do until we
    //  have SAX2 support.
    fFormatter << gXMLDecl1 << fFormatter.getEncodingName() << gXMLDecl2;
}

DTXMLWriter::~DTXMLWriter() {
}

# pragma mark output

void DTXMLWriter::startDocument() {
}

DTXMLWriter* DTXMLWriter::startElement(string qname,
                               const vector<pair<string,string> >* attribs,
                               bool end) {
    // The name has to be representable without any escapes
    fFormatter  << XMLFormatter::NoEscapes << chOpenAngle;
    fFormatter << XMLString::transcode(qname.c_str());
    
    if (attribs) {
        for (vector<pair<string,string> >::const_iterator it = attribs->begin(); it != attribs->end(); ++it) {
            fFormatter  << XMLFormatter::NoEscapes << chSpace ;
            fFormatter  << XMLString::transcode((*it).first.c_str());
            fFormatter  << chEqual << chDoubleQuote
                        << XMLFormatter::AttrEscapes
                        << XMLString::transcode((*it).second.c_str())
                        << XMLFormatter::NoEscapes
                        << chDoubleQuote;
        }
    }
    if (end) fFormatter << chForwardSlash;
    fFormatter << chCloseAngle;
    if (end) writeNewline();
    return this;
}

DTXMLWriter* DTXMLWriter::endElement(string qname) {
    // No escapes are legal here
    fFormatter << XMLFormatter::NoEscapes << gEndElement;
	fFormatter << XMLString::transcode(qname.c_str()) << chCloseAngle << chLF;
    return this;
}

DTXMLWriter* DTXMLWriter::writeChars(string element, bool encode) {
    if (encode) {
        fFormatter << XMLFormatter::CharEscapes << XMLString::transcode(element.c_str());
    } else {
        fFormatter << XMLString::transcode(element.c_str());
    }
    return this;
}

DTXMLWriter* DTXMLWriter::writeChars(int element) {
    ostringstream oss;
    oss << element;
    fFormatter << XMLString::transcode(oss.str().c_str());
    return this;
}

DTXMLWriter* DTXMLWriter::writeChars(double element) {
    ostringstream oss;
    oss << element;
    fFormatter << XMLString::transcode(oss.str().c_str());
    return this;
}

DTXMLWriter* DTXMLWriter::writeNewline() {
    fFormatter << chLF;
    return this;
}

void DTXMLWriter::endDocument() {
}

