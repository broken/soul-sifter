//
//  DTAbstractHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#ifndef __soul_sifter__DTAbstractHandler__
#define __soul_sifter__DTAbstractHandler__

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>

namespace dogatech {
  
class DTAbstractHandler : public xercesc::DefaultHandler {
public:
    DTAbstractHandler(xercesc::SAX2XMLReader* parser,
                                          DTAbstractHandler* parentHandler);
    ~DTAbstractHandler();
    
    virtual void startElement(const XMLCh* const uri,
                              const XMLCh* const localname,
                              const XMLCh* const qname,
                              const xercesc::Attributes& attrs);
    
    virtual void endElement(const XMLCh* const uri,
                            const XMLCh* const localName,
                            const XMLCh* const qName);
    
    virtual void characters(const XMLCh* const chars, const XMLSize_t length);
    
    unsigned long getStartTagCount();
    
    virtual const XMLCh* const getQname() = 0;
protected:
    DTAbstractHandler* parentHandler;
    // This variable must end in a NULL pointer
    DTAbstractHandler** childHandlers;
    xercesc::SAX2XMLReader* parser;
    static unsigned long startTagCount;
};

}

#endif /* defined(__soul_sifter__DTAbstractHandler__) */
