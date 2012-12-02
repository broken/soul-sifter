//
//  DTCopyHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#ifndef __soul_sifter__DTCopyHandler__
#define __soul_sifter__DTCopyHandler__

#include "DTAbstractHandler.h"

#include <string>

class DTCopyHandler : public DTAbstractHandler {
public:
    DTCopyHandler(xercesc::SAX2XMLReader* parser,
                  DTAbstractHandler* parentHandler);
    
    virtual void startElement(const XMLCh* const uri,
                              const XMLCh* const localname,
                              const XMLCh* const qname,
                              const xercesc::Attributes& attrs);
    
    virtual void endElement(const XMLCh* const uri,
                            const XMLCh* const localName,
                            const XMLCh* const qName);
    
    virtual void characters(const XMLCh* const chars, const XMLSize_t length);
    
    virtual const XMLCh* const getQname() = 0;
    
    virtual void init() = 0;
    virtual void commit() = 0;
protected:
    std::string* text;
};

#endif /* defined(__soul_sifter__DTCopyHandler__) */
