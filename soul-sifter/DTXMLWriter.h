//
//  DTXMLWriter.h
//  soul-sifter
//
//  Created by Robby Neale on 12/5/12.
//
//

#ifndef __soul_sifter__DTXMLWriter__
#define __soul_sifter__DTXMLWriter__

#include <string>
#include <vector>

#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/XMLFormatter.hpp>

using namespace std;
using namespace xercesc;

class DTXMLWriter {
public:
    DTXMLWriter(const char* const encodingName,
                const char* const filepath,
                const bool expandingNamespaces);
    ~DTXMLWriter();
    
    void startDocument();
    void endDocument();
    DTXMLWriter* startElement(string qname,
                              const vector<pair<string, string> >* attribs,
                              bool end = false);
    DTXMLWriter* endElement(string qname);
    DTXMLWriter* writeChars(string toWrite, bool encode = true);
    DTXMLWriter* writeChars(int toWrite);
    DTXMLWriter* writeChars(double toWrite);
    DTXMLWriter* writeNewline();
    
private:
    LocalFileFormatTarget file;
    XMLFormatter    fFormatter;
	bool			fExpandNS ;
};

#endif /* defined(__soul_sifter__DTXMLWriter__) */
