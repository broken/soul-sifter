//
//  RapidEvolutionDatabaseAbstractHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseAbstractHandler__
#define __soul_sifter__RapidEvolutionDatabaseAbstractHandler__

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>

class RapidEvolutionDatabaseAbstractHandler : public xercesc::DefaultHandler {
public:
    RapidEvolutionDatabaseAbstractHandler(xercesc::SAX2XMLReader* parser,
                                          RapidEvolutionDatabaseAbstractHandler* parentHandler);
    ~RapidEvolutionDatabaseAbstractHandler();
    
    virtual void startElement(const XMLCh* const uri,
                              const XMLCh* const localname,
                              const XMLCh* const qname,
                              const xercesc::Attributes& attrs);
    
    virtual void endElement(const XMLCh* const uri,
                            const XMLCh* const localName,
                            const XMLCh* const qName);
    
    virtual const XMLCh* const getQname() = 0;
protected:
    RapidEvolutionDatabaseAbstractHandler* parentHandler;
    // This variable must end in a NULL pointer
    RapidEvolutionDatabaseAbstractHandler** childHandlers;
    xercesc::SAX2XMLReader* parser;
};


#endif /* defined(__soul_sifter__RapidEvolutionDatabaseAbstractHandler__) */
