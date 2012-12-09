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
                const char* const filepath);
    ~DTXMLWriter();
    
    void startDocument();
    void endDocument();
    DTXMLWriter& startElement(string qname,
                              pair<string,string>* attribs[],
                              bool close = false);
    DTXMLWriter& endElement(string qname);
    DTXMLWriter* writeChars(string toWrite, bool encode = true);
    DTXMLWriter& writeStr(string toWrite, bool encode = true);
    DTXMLWriter& writeInt(int toWrite);
    DTXMLWriter& writeDouble(double toWrite);
    DTXMLWriter& writeBoolAsYesOrNo(bool toWrite);
    DTXMLWriter* writeNewline();
    DTXMLWriter& endl();
    
private:
    LocalFileFormatTarget file;
    XMLFormatter xmlFormatter;
};

#endif /* defined(__soul_sifter__DTXMLWriter__) */
