//
//  REXml.h
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#ifndef __soul_sifter__REXml__
#define __soul_sifter__REXml__

#include <string>
#include <vector>


namespace sql {
    class ResultSet;
}

using namespace std;

namespace soulsifter {

    class REXml {
    public:
        REXml();
        explicit REXml(const REXml& reXml);
        void operator=(const REXml& reXml);
        ~REXml();
        void clear();

        static REXml* findById(int id);
        static REXml* findByName(const string& name);

        bool sync();
        int update();
        int save();

        string& getXmlRef();

        const int getId() const;
        void setId(int id);
        const string& getName() const;
        void setName(const string& name);
        const string& getXml() const;
        void setXml(const string& xml);

    private:
        int id;
        string name;
        string xml;

        static void populateFields(const sql::ResultSet* rs, REXml* reXml);
    };

}

#endif /* defined(__soul_sifter__REXml__) */
