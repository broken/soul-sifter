//
//  RapidEvolutionMusicDatabaseReader.m
//  soul-sifter
//
//  Created by Robby Neale on 11/4/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//
//  Reads the RE database file and updates mysql database.

#include "RapidEvolutionMusicDatabaseReader.h"

#include <iostream>

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>

#include "RapidEvolutionDatabaseHandler.h"
#include "XMLStartTagCounter.h"

using namespace std;
using namespace xercesc;

# pragma mark initialization

RapidEvolutionMusicDatabaseReader::RapidEvolutionMusicDatabaseReader() :
processing(false),
length(0),
reDbHandler(NULL) {
}

# pragma mark xml reader

void RapidEvolutionMusicDatabaseReader::computeMusicDatabaseLength() {
    xercesc::SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
    XMLStartTagCounter* startTagCounter = new XMLStartTagCounter(parser, NULL);
    parser->setContentHandler(startTagCounter);
    parser->setErrorHandler(startTagCounter);
    try {
        parser->parse("/Users/rneale/Library/Application Support/Rapid Evolution 2/music_database.xml");
    }
    catch (const XMLException& toCatch) {
        cout << "Exception message is: " << toCatch.getMessage() << endl;
    }
    catch (const SAXParseException& toCatch) {
        cout << "Exception message is: " << toCatch.getMessage() << endl;
    }
    catch (...) {
        cout << "Unexpected exception" << endl;
    }
    length = startTagCounter->getStartTagCount();
    delete startTagCounter;
    delete parser;
}

bool RapidEvolutionMusicDatabaseReader::read() {
    cout << "rapidEvolutionMusicDatabaseReader.read" << endl;
    processing = true;
    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        cout << "error " << toCatch.getMessage() << endl;
        return false;
    }
    
    //NSString *rePath = [[NSUserDefaults standardUserDefaults] stringForKey:UDRapidEvolutionPath];
    //NSString *reFilePath = [NSString stringWithFormat:@"%@/music_database.xml", rePath];
    computeMusicDatabaseLength();
    
    xercesc::SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
    // for srcOffset. Unfortunately doesn't work on macs. :(
    parser->setFeature(XMLUni::fgXercesCalculateSrcOfs, false);
    parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
    parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);   // optional. need?
    
    reDbHandler = new RapidEvolutionDatabaseHandler(parser, NULL);
    parser->setContentHandler(reDbHandler);
    parser->setErrorHandler(reDbHandler);
    
    try {
        parser->parse("/Users/rneale/Library/Application Support/Rapid Evolution 2/music_database.xml");
    }
    catch (const XMLException& toCatch) {
        cout << "Exception message is: " << toCatch.getMessage() << endl;
        processing = false;
        return false;
    }
    catch (const SAXParseException& toCatch) {
        cout << "Exception message is: " << toCatch.getMessage() << endl;
        processing = false;
        return false;
    }
    catch (...) {
        cout << "Unexpected exception" << endl;
        processing = false;
        return false;
    }
    
    // TODO: below line delete these?
    delete reDbHandler;
    delete parser;
    XMLPlatformUtils::Terminate();
    
    // Other terminations and cleanup.
    
    processing = false;
    length = 0;
    return true;
}

bool RapidEvolutionMusicDatabaseReader::isProcessing() {
    return processing;
}

