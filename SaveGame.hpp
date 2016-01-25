//
//  SaveGame.hpp
//  Five Animals
//

#ifndef SaveGame_hpp
#define SaveGame_hpp

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

namespace SaveGame {
    // Extracts the first number in a string
    static int extractFirstInt(const std::string &s) {
        std::stringstream ss;
        ss << s;
        // If return -1 there is a problem
        int found = -1;
        std::string item;
        while(std::getline(ss, item, ' ')) {
            if(std::stringstream(item) >> found) {
                // Only want the first string
                break;
            }
        }
        return found;
    }
    // Split string on a delimiter
    static void splitString(std::vector<std::string> &elems, const std::string &s, const char delim) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            if (!item.empty()) {
                elems.push_back(item);
                elems.push_back(std::string(1,delim));
            }
        }
    }
    typedef std::map<std::string,std::string> stringMap;
    static stringMap gameData;
    // Read map from file
    static bool fileToMap(const std::string &filename, stringMap &fileMap) {
        std::ifstream ifile;
        ifile.open(filename.c_str());
        if(!ifile) return false;   // Could not read the file
        std::string line;
        while(std::getline(ifile, line)) {
            std::vector<std::string> v_str;
            splitString(v_str,line,'|');
            fileMap[v_str.at(0)] = v_str.at(2);
        }
        return true;
    }
    // Write map to file
    static bool mapToFile(const std::string &filename,const stringMap &fileMap) {
        std::ofstream ofile;
        ofile.open(filename.c_str());
        if(!ofile) return false;           // Could not read the file
        for(stringMap::const_iterator iter= fileMap.begin(); iter!=fileMap.end(); ++iter){
            ofile << iter->first << "|" << iter->second;
            ofile << "\n";
        }
        return true;
    }
}

#endif /* SaveGame_hpp */