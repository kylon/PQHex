cmake_minimum_required(VERSION 3.23)

project(PQHex VERSION 1.1 DESCRIPTION "The Pokemon Quest save editor" LANGUAGES CXX)

set(PROJECT_AUTHOR "kylon")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Widgets)
find_package(OpenSSL)

qt_standard_project_setup()

qt_add_resources(QT_RESOURCE
    res/resources.qrc
    Resources/app_res.qrc
)

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
    tabs/include/FlowLayout.h
    tabs/include/FlowLayout.cpp
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

if (WIN32)
    configure_file(Resources/Windows/win.rc.in ${CMAKE_CURRENT_SOURCE_DIR}/win.rc)

    qt_add_executable(${PROJECT_NAME}
        ${QT_RESOURCE}
        ${PROJECT_SOURCES}
        "win.rc")
else ()
    qt_add_executable(${PROJECT_NAME}
        ${QT_RESOURCE}
        ${PROJECT_SOURCES})
endif ()

include(CheckIPOSupported)
check_ipo_supported(RESULT has_ipo OUTPUT ipo_error)
if (has_ipo)
    message(STATUS "${PROJECT_NAME}: IPO/LTO enabled")
    set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core Qt::Widgets OpenSSL::Crypto)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER "kylon.pqhex.com"
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
        TARGET ${PROJECT_NAME}
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
