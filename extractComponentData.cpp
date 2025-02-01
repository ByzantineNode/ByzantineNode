#include "extractComponentData.h"
#include "LayerDirectory.h"
#include "StepDirectory.h"
#include "ComponentsFile.h"
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <filesystem>
#include <vector>
#include "enums.h"

namespace Odb::Lib::FileModel::Design {

    void extractComponentData(const FileArchive &archive)
    {
        const auto &steps = archive.GetStepsByName();
        std::cout << "Steps in the archive: " << steps.size() << std::endl;

        for (const auto &[stepName, stepPtr] : steps)
        {
            std::cout << "\nStep Name: " << stepName << std::endl;

            const auto &layers = stepPtr->GetLayersByName();
            std::cout << "Layers in the step: " << layers.size() << std::endl;

            for (const auto &[layerName, layerPtr] : layers)
            {
                std::cout << "\n  Layer Name: " << layerPtr->GetName() << std::endl;
                std::cout << "  Layer Path: " << layerPtr->GetPath() << std::endl;

                // Access the ComponentsFile from LayerDirectory
                Odb::Lib::FileModel::Design::ComponentsFile currcomponentsFile = layerPtr->GetComponentsFile();

                if (!currcomponentsFile.GetLayerName().empty())
                {
                    std::cout << "    Components Layer Name: " << currcomponentsFile.GetLayerName() << std::endl;
                    std::cout << "    Units: " << currcomponentsFile.GetUnits() << std::endl;

                    // Determine Board Side
                    std::string boardSide;
                    if (currcomponentsFile.GetSide() == Odb::Lib::BoardSide::Top)
                    {
                        boardSide = "Top";
                    }
                    else if (currcomponentsFile.GetSide() == Odb::Lib::BoardSide::Bottom)
                    {
                        boardSide = "Bottom";
                    }
                    else
                    {
                        boardSide = "None";
                    }
                    std::cout << "Board Side: " << boardSide << std::endl;
                    std::cout << "    Components File Path: " << currcomponentsFile.GetPath() << std::endl;

                    // Retrieve Component Records
                    const auto &componentRecords = currcomponentsFile.GetComponentRecords();
                    std::cout << "    Components in the file: " << componentRecords.size() << std::endl;

                    for (const auto &componentRecord : componentRecords)
                    {
                        std::cout << "\n      Component Name: " << componentRecord->compName << std::endl;
                        std::cout << "      Part Name: " << componentRecord->partName << std::endl;
                        std::cout << "      Location X: " << componentRecord->locationX << std::endl;
                        std::cout << "      Location Y: " << componentRecord->locationY << std::endl;
                        std::cout << "      Mirror: " << componentRecord->mirror << std::endl;
                        std::cout << "      Rotation: " << componentRecord->rotation << std::endl;
                        std::cout << "      Component ID: " << componentRecord->id << std::endl;
                        std::cout << "      Component Index: " << componentRecord->index << std::endl;

                        // Toeprint Records
                        const auto &toeprintRecords = componentRecord->m_toeprintRecords;
                        std::cout << "      Toeprint Records: " << toeprintRecords.size() << std::endl;
                        for (const auto &toeprintRecord : toeprintRecords)
                        {
                            std::cout << "        Pin Number: " << toeprintRecord->pinNumber << std::endl;
                            std::cout << "        Net Number: " << toeprintRecord->netNumber << std::endl;
                            std::cout << "        Name: " << toeprintRecord->name << std::endl;
                            std::cout << "        Location X: " << toeprintRecord->locationX << std::endl;
                            std::cout << "        Location Y: " << toeprintRecord->locationY << std::endl;
                            std::cout << "        Rotation: " << toeprintRecord->rotation << std::endl;
                            std::cout << "        Mirror: " << toeprintRecord->mirror << std::endl;
                        }

                        // Property Records
                        const auto &propertyRecords = componentRecord->m_propertyRecords;
                        std::cout << "      Property Records: " << propertyRecords.size() << std::endl;
                        for (const auto &propertyRecord : propertyRecords)
                        {
                            std::cout << "        Property Name: " << propertyRecord->name << std::endl;
                            std::cout << "        Property Value: " << propertyRecord->value << std::endl;
                        }
                    }

                    // BOM Description Records
                    const auto &bomDescriptionRecords = currcomponentsFile.GetBomDescriptionRecordsByCpn();
                    std::cout << "    BOM Description Records: " << bomDescriptionRecords.size() << std::endl;
                    for (const auto &[cpn, bomDescriptionRecord] : bomDescriptionRecords)
                    {
                        std::cout << "      CPN: " << cpn << std::endl;
                        std::cout << "      PKG: " << bomDescriptionRecord->pkg << std::endl;
                        std::cout << "      IPN: " << bomDescriptionRecord->ipn << std::endl;
                        std::cout << "      Descriptions: ";
                        for (const auto &desc : bomDescriptionRecord->descriptions)
                        {
                            std::cout << desc << ", ";
                        }
                        std::cout << std::endl;
                        std::cout << "      VPL_VND: " << bomDescriptionRecord->vpl_vnd << std::endl;
                        std::cout << "      VPL_MPN: " << bomDescriptionRecord->vpl_mpn << std::endl;
                        std::cout << "      VND: " << bomDescriptionRecord->vnd << std::endl;
                        std::cout << "      MPN: " << bomDescriptionRecord->mpn << std::endl;
                    }
                }
                else
                {
                    std::cout << "    No Components File found in this layer." << std::endl;
                }
            }
        }
    }

} // namespace Odb::Lib::FileModel::Design

