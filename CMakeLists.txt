cmake_minimum_required(VERSION 3.16)

project(PQHex VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(OpenSSL)

set(PROJECT_SOURCES
    include/Error.h
    include/TypeAliases.h
    include/quest/CharacterStorage.h
    include/quest/ConfigData.h
    include/quest/CheckData.h
    include/quest/Core.h
    include/quest/ItemStorage.h
    include/quest/ManageData.h
    include/quest/BattleData.h
    include/quest/FormationData.h
    include/quest/MemberData.h
    include/quest/PotentialStorage.h
    include/quest/SaveCharacterData.h
    include/quest/SaveCharacterPoteintialData.h
    include/quest/SavePotentialSkillData.h
    include/quest/SerializeData.h
    include/quest/StoneData.h
    include/quest/PowerStone.h
    include/quest/PowerStoneBonus.h
    include/quest/Misc.h
    include/quest/PlayerData.h
    include/quest/Goods.h
    include/quest/GoodsManageData.h
    include/quest/PlacementData.h
    include/quest/PokemonMemory.h

    classes/Parser.h
    classes/Parser.cpp
    classes/Patcher/include/Patcher.h
    classes/Patcher/ItemStoragePatcher.h
    classes/Patcher/ItemStoragePatcher.cpp
    classes/Patcher/PlayerNamePatcher.h
    classes/Patcher/PlayerNamePatcher.cpp
    classes/Patcher/StonePatcher.h
    classes/Patcher/StonePatcher.cpp
    classes/Patcher/GoodsPatcher.h
    classes/Patcher/GoodsPatcher.cpp

    tabs/include/Utils.h
    tabs/include/Utils.cpp
    tabs/include/GridWidget.h
    tabs/include/MainSubWidget.h

    tabs/widgets/PokemonWidget.h
    tabs/widgets/PokemonWidget.cpp
    tabs/widgets/PokemonContainer.h
    tabs/widgets/PokemonContainer.cpp
    tabs/widgets/PokemonEditor/PokemonEditor.h
    tabs/widgets/PokemonEditor/PokemonEditor.cpp
    tabs/widgets/PokemonEditor/SaveCharacterData/PokemonBaseDataEditor.h
    tabs/widgets/PokemonEditor/SaveCharacterData/PokemonBaseDataEditor.cpp
    tabs/widgets/PokemonEditor/SaveCharacterData/CharacterPotentialData/PokemonCharacterPotentialEditor.h
    tabs/widgets/PokemonEditor/SaveCharacterData/CharacterPotentialData/PokemonCharacterPotentialEditor.cpp
    tabs/widgets/PokemonEditor/SaveCharacterData/CharacterPotentialData/AttachStoneStorageIDEditor.h
    tabs/widgets/PokemonEditor/SaveCharacterData/CharacterPotentialData/AttachStoneStorageIDEditor.cpp
    tabs/widgets/PokemonEditor/SaveCharacterData/CharacterPotentialData/AttachSkillStoneStorageIDEditor.h
    tabs/widgets/PokemonEditor/SaveCharacterData/CharacterPotentialData/AttachSkillStoneStorageIDEditor.cpp
    tabs/widgets/PokemonEditor/SaveCharacterData/CharacterPotentialData/SlotPropertyTypesEditor.h
    tabs/widgets/PokemonEditor/SaveCharacterData/CharacterPotentialData/SlotPropertyTypesEditor.cpp
    tabs/widgets/PokemonEditor/SaveCharacterData/CharacterPotentialData/PotentialSkillDataEditor.h
    tabs/widgets/PokemonEditor/SaveCharacterData/CharacterPotentialData/PotentialSkillDataEditor.cpp
    tabs/widgets/PokemonEditor/SaveCharacterData/CharacterPotentialData/ActiveSlotsEditor.h
    tabs/widgets/PokemonEditor/SaveCharacterData/CharacterPotentialData/ActiveSlotsEditor.cpp
    tabs/widgets/MiscEditor.h
    tabs/widgets/MiscEditor.cpp
    tabs/widgets/ConfigDataEditor.h
    tabs/widgets/ConfigDataEditor.cpp
    tabs/widgets/StoneContainer.h
    tabs/widgets/StoneContainer.cpp
    tabs/widgets/StoneWidget.h
    tabs/widgets/StoneWidget.cpp
    tabs/widgets/StoneEditor/StoneEditor.h
    tabs/widgets/StoneEditor/StoneEditor.cpp
    tabs/widgets/StoneEditor/StoneData/StoneDataEditor.h
    tabs/widgets/StoneEditor/StoneData/StoneDataEditor.cpp
    tabs/widgets/StoneEditor/StoneData/StoneBonusEditor.h
    tabs/widgets/StoneEditor/StoneData/StoneBonusEditor.cpp

    tabs/mainSubTabs/PokemonTab.h
    tabs/mainSubTabs/PokemonTab.cpp
    tabs/mainSubTabs/StoneTab.h
    tabs/mainSubTabs/StoneTab.cpp
    tabs/mainSubTabs/PartyTab.h
    tabs/mainSubTabs/PartyTab.cpp
    tabs/mainSubTabs/IngridientsTab.h
    tabs/mainSubTabs/IngridientsTab.cpp
    tabs/mainSubTabs/GoodsTab.h
    tabs/mainSubTabs/GoodsTab.cpp
    tabs/mainSubTabs/PokedexTab.h
    tabs/mainSubTabs/PokedexTab.cpp
    tabs/mainSubTabs/MiscTab.h
    tabs/mainSubTabs/MiscTab.cpp
    tabs/mainSubTabs/PlayerTab.h
    tabs/mainSubTabs/PlayerTab.cpp
    tabs/mainSubTabs/InfoTab.h
    tabs/mainSubTabs/InfoTab.cpp
    tabs/NatureTab.h
    tabs/NatureTab.cpp
    tabs/MainTab.h
    tabs/MainTab.cpp
    tabs/LogTab.h
    tabs/LogTab.cpp

    Save.h
    Save.cpp
    main.cpp
    PQHex.cpp
    PQHex.h
    pqhex.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        res/resources.qrc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(${PROJECT_NAME}
        res/resources.qrc
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets OpenSSL::Crypto)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.kylon.${PROJECT_NAME})
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
