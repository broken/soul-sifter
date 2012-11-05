//
//  RapidEvolutionMusicDatabaseReader.m
//  soul-sifter
//
//  Created by Robby Neale on 11/4/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//
//  Reads the RE database file and updates mysql database.

#import "RapidEvolutionMusicDatabaseReader.h"

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>

#import "Constants.h"
#import "RapidEvolutionDatabaseHandler.h"

using namespace xercesc;

@implementation RapidEvolutionMusicDatabaseReader

- (bool)read {
    NSLog(@"rapidEvolutionMusicDatabaseReader.read");
    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        NSLog(@"error %S", toCatch.getMessage());
        return false;
    }
    
    NSString *rePath = [[NSUserDefaults standardUserDefaults] stringForKey:UDRapidEvolutionPath];
    NSString *reFilePath = [NSString stringWithFormat:@"%@/music_database.xml", rePath];
    
    SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
    parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
    parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);   // optional
    
    RapidEvolutionDatabaseHandler* defaultHandler = new RapidEvolutionDatabaseHandler(parser, NULL);
    parser->setContentHandler(defaultHandler);
    parser->setErrorHandler(defaultHandler);
    
    try {
        parser->parse([reFilePath UTF8String]);
    }
    catch (const XMLException& toCatch) {
        NSLog(@"Exception message is: %S", toCatch.getMessage());
        return false;
    }
    catch (const SAXParseException& toCatch) {
        NSLog(@"Exception message is: %S", toCatch.getMessage());
        return false;
    }
    catch (...) {
        NSLog(@"Unexpected exception");
        return false;
    }
    
    XMLPlatformUtils::Terminate();
    // TODO: above line delete these?
    //delete parser;
    //delete defaultHandler;
    
    // Other terminations and cleanup.

    return true;
}

@end
