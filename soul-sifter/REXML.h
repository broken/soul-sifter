//
//  REXML.h
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#ifndef __soul_sifter__REXML__
#define __soul_sifter__REXML__

#include <string>

using namespace std;

class REXML {
public:
    REXML();
    ~REXML();
    
    static REXML* findById(const int id);
    static REXML* findByName(const string& name);
    
    bool update();
    REXML* save();
    void clear();
    
    const int getId() const;
    void setId(const int id);
    const string& getName() const;
    void setName(const string& name);
    const string& getXml() const;
    string& getXmlRef();
    void setXml(const string& value);
private:
    int id;
    string name;
    string xml;
};

#endif /* defined(__soul_sifter__REXML__) */
