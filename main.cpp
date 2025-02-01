#include "FileArchive.h"
#include "extractComponentData.h"
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <filesystem>
#include <vector>
#include "enums.h"

int main()
{
    std::string archiveName = "/home/ritik/test/designodb_rigidflex.tgz";
    Odb::Lib::FileModel::Design::FileArchive archive(archiveName);

    // Parse the file model
    bool status = archive.ParseFileModel();
    if (status)
    {
        std::cout << "File Model Parsed Successfully" << std::endl;
        // Call the function within the namespace
        Odb::Lib::FileModel::Design::extractComponentData(archive);
    }
    else
    {
        std::cout << "File Model Parsing Failed" << std::endl;
        return -1;
    }

    return 0;
}

