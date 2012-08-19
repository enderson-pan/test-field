#include "packfileinspector.h"

#include <string>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/lexical_cast.hpp>

#include <stdint.h>
#include <arpa/inet.h>


// public:
PackfileInspector::PackfileInspector(const std::string &packfileName)
    : packfileName_(packfileName),
      isForceTerminated_(false),
      isPack_(false),
      isIndex_(false)

{
    using namespace boost::filesystem;

    path p(packfileName);

    try
    {
        packFile_.open(p, std::ios_base::binary | std::ios_base::in);
        path extension = p.extension();
        if (path(".pack") == extension)
        {
            isPack_ = true;
        }
        else if (path(".idx") == extension)
        {
            isIndex_ = true;
        }
    }

    catch (const filesystem_error& ex)
    {
        exit(0);
    }
}

PackfileInspector::~PackfileInspector()
{
    packFile_.close();
}

bool PackfileInspector::isEnd() const
{
    if (isForceTerminated_)
        return true;

    return packFile_.eof();
}

std::string PackfileInspector::getBlocksOfPackfile()
{
    std::string content;

    if (isPack_)
    {
        content = ".pack file is loaded...\n";

        //
        // Header
        //

        // 4 bytes signature. "PACK".
        content += "Signature:";
        char sigBuf[5];
        packFile_.read(sigBuf, 4);
        sigBuf[4] = '\0';
        std::string packSignature(sigBuf);
        content += "\n\t";
        content += packSignature;

        // 4 bytes version. Network byte order.
        int32_t version;
        packFile_.read(reinterpret_cast< char* >(&version), 4);
        version = ntohl(version);
        content += "\nVersion:";
        content += "\n\t";
        content += boost::lexical_cast< std::string >(version);

        // 4 bytes entries. Network byte order.
        int32_t entries;
        packFile_.read(reinterpret_cast< char* >(&entries), 4);
        entries = ntohl(entries);
        content += "\nEntries:";
        content += "\n\t";
        content += boost::lexical_cast< std::string >(entries);



        isForceTerminated_ = true;
        content += "\n\n\n\nTo be continued...";
    }
    else if(isIndex_)
    {
        content = ".idx file is loaded...\n";

        //
        // Header
        //

        // 4 bytes signature. "\fftOc"
        content += "Signature:";
        unsigned char num;
        packFile_.read(reinterpret_cast< char* >(&num), 1);
        content += "\n\t";
        content += boost::lexical_cast< std::string >(static_cast< int >(num));
        char sigBuff[4];
        packFile_.read(sigBuff, 3);
        sigBuff[3] = '\0';
        std::string indexSignature(sigBuff);
        content += indexSignature;

        // 4 bytes version. Network byte order.
        content += "\nVersion";
        int32_t version;
        packFile_.read(reinterpret_cast< char* >(&version), 4);
        version = ntohl(version);
        content += "\n\t";
        content += boost::lexical_cast< std::string >(version);

        // Fanout table, 256 * 4 bytes fanouts. Network byte order.
        std::vector< int32_t > fanoutTable;
        content += "\nFanout table:";
        int32_t fanout;
        for(int i = 0; i < 256; ++i)
        {
            content += "\n:";
            content += boost::lexical_cast< std::string >(i);
            content += "\t\t";
            packFile_.read(reinterpret_cast< char* >(&fanout), 4);
            content += boost::lexical_cast< std::string >(fanout);
            fanoutTable.push_back(fanout);
        }




        isForceTerminated_ = true;
        content += "\nTo be continued...";
    }
    else
    {
        isForceTerminated_ = true;
        content = "File format is not supported now!";
    }

    return content;

}




























