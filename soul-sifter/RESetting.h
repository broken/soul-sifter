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
#include <vector>

using namespace std;

class RESetting {
public:
    RESetting();
    ~RESetting();
    void clear();
    
    static RESetting* findById(const int id);
    static RESetting* findByName(const string& name);
    static void findAll(vector<const RESetting*>* settings);
    
    bool update();
    RESetting* save();
    
    const int getId() const;
    void setId(const int id);
    const string& getName() const;
    void setName(const string& name);
    const string& getValue() const;
    string& getValueRef();
    void setValue(const string& value);
private:
    int id;
    string name;
    string value;
};

#endif /* defined(__soul_sifter__RESetting__) */
