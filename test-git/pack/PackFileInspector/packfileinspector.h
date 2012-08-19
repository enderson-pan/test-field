#ifndef PACKFILEINSPECTOR_H
#define PACKFILEINSPECTOR_H

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem/fstream.hpp>

#include <string>

class PackfileInspector
{    
public:
    PackfileInspector(const std::string& packfileName);
    ~PackfileInspector();

    bool isEnd() const;
    std::string getBlocksOfPackfile();

private:
    const std::string& packfileName_;
    boost::filesystem::ifstream packFile_;

    bool isForceTerminated_;

    bool isPack_;
    bool isIndex_;
};

#endif // PACKFILEINSPECTOR_H
