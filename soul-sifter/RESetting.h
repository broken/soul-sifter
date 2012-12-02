//
//  RESetting.h
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#ifndef __soul_sifter__RESetting__
#define __soul_sifter__RESetting__

#include <string>

using namespace std;

class RESetting {
public:
    RESetting();
    ~RESetting();
    
    static RESetting* findByName(const string& name);
    
    bool update();
    RESetting* save();
    
    const string& getName() const;
    void setName(const string& name);
    const string& getValue() const;
    void setValue(const string& value);
private:
    string name;
    string value;
};

#endif /* defined(__soul_sifter__RESetting__) */
