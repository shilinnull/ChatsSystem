include(F:/ChatsSystem/ChatClient/build/Desktop_Qt_6_7_3_MSVC2019_64bit-Debug/.qt/QtDeploySupport.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/ChatClient-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_ALL_MODULES_FOUND_VIA_FIND_PACKAGE "ZlibPrivate;EntryPointPrivate;Core;Gui;Widgets")

qt6_deploy_runtime_dependencies(
    EXECUTABLE F:/ChatsSystem/ChatClient/build/Desktop_Qt_6_7_3_MSVC2019_64bit-Debug/ChatClient.exe
    GENERATE_QT_CONF
)
