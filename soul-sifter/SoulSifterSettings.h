//
//  SoulSifterSettings.h
//  soul-sifter
//
//  Created by Robby Neale on 12/9/12.
//
//

#ifndef __soul_sifter__SoulSifterSettings__
#define __soul_sifter__SoulSifterSettings__

#include <hash_map.h>
#include <string>

using namespace std;

namespace soulsifter {
    
    class SoulSifterSettings {
    public:
        ~SoulSifterSettings() { }
        static SoulSifterSettings& getInstance() {
            static SoulSifterSettings instance;  // guaranteed to be destroyed
            // instantiated on first use
            return instance;
        }
        
        const string& getMusicPath() const { return musicPath; }
        void setMusicPath(const string& path) { musicPath = path; }
        const string& getREPath() const { return rePath; }
        void setREPath(const string& path) { rePath = path; }
        const string& getStagingPath() const { return stagingPath; }
        void setStagingPath(const string& path) { stagingPath = path; }
        
    private:
        // singleton
        SoulSifterSettings() { }
        SoulSifterSettings(SoulSifterSettings const&);
        void operator=(SoulSifterSettings const&);
        
        string musicPath;
        string rePath;
        string stagingPath;
    };
    
}

#endif /* defined(__soul_sifter__SoulSifterSettings__) */
