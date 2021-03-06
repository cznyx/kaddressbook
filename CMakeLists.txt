cmake_minimum_required(VERSION 3.1)
set(KDEPIM_VERSION_NUMBER "5.7.40")
project(kaddressbook VERSION ${KDEPIM_VERSION_NUMBER})

set(KF5_VERSION "5.43.0")

find_package(ECM ${KF5_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(ECMInstallIcons)

include(ECMOptionalAddSubdirectory)
include(ECMSetupVersion)
include(ECMAddTests)
include(ECMMarkNonGuiExecutable)
include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(CMakePackageConfigHelpers)
include(FeatureSummary)
include(CheckFunctionExists)
include(ECMGeneratePriFile)


include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMAddAppIcon)
include(ECMQtDeclareLoggingCategory)
include(ECMCoverageOption)

# Do NOT add quote
set(KDEPIM_DEV_VERSION alpha)

# add an extra space
if(DEFINED KDEPIM_DEV_VERSION)
    set(KDEPIM_DEV_VERSION " ${KDEPIM_DEV_VERSION}")
endif()

set(KDEPIM_VERSION "${KDEPIM_VERSION_NUMBER}${KDEPIM_DEV_VERSION}")

set(KPIMTEXTEDIT_LIB_VERSION "5.7.40")
set(AKONADI_VERSION "5.7.40")
set(KONTACTINTERFACE_LIB_VERSION "5.7.40")

set(KDEPIM_LIB_VERSION "${KDEPIM_VERSION_NUMBER}")
set(KDEPIM_LIB_SOVERSION "5")


set(QT_REQUIRED_VERSION "5.8.0")
find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Test DBus PrintSupport)
set(LIBKDEPIM_LIB_VERSION_LIB "5.7.40")
set(KDEPIM_APPS_LIB_VERSION_LIB "5.7.40")
set(LIBGRANTLEETHEME_LIB_VERSION_LIB "5.7.40")
set(PIMCOMMON_LIB_VERSION_LIB "5.7.40")
set(LIBKLEO_LIB_VERSION "5.7.40")
# Find KF5 package
find_package(KF5DBusAddons ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5DocTools ${KF5_VERSION} REQUIRED)
find_package(KF5KCMUtils ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Crash ${KF5_VERSION} REQUIRED)
find_package(KF5IconThemes ${KF5_VERSION} REQUIRED)
find_package(KF5Libkleo ${LIBKLEO_LIB_VERSION} CONFIG REQUIRED)

option(DOMAIN_EXPERIMENTAL "Enable this feature if you want to build experimental domain library. Not Stable yet." FALSE)


# Find KdepimLibs Package
find_package(KF5PimTextEdit ${KPIMTEXTEDIT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)
find_package(KF5KontactInterface ${KONTACTINTERFACE_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkdepim ${LIBKDEPIM_LIB_VERSION_LIB} CONFIG REQUIRED)
find_package(KF5KdepimDBusInterfaces ${KDEPIM_APPS_LIB_VERSION_LIB} CONFIG REQUIRED)
find_package(KF5PimCommonAkonadi ${PIMCOMMON_LIB_VERSION_LIB} CONFIG REQUIRED)

find_package(KF5KaddressbookGrantlee ${KDEPIM_APPS_LIB_VERSION_LIB} CONFIG REQUIRED)
find_package(KF5KaddressbookImportExport ${KDEPIM_APPS_LIB_VERSION_LIB} CONFIG REQUIRED)
find_package(KF5GrantleeTheme ${LIBGRANTLEETHEME_LIB_VERSION_LIB} CONFIG REQUIRED)


set(GPGMEPP_LIB_VERSION "1.8.0")
find_package(Gpgmepp ${GPGMEPP_LIB_VERSION} CONFIG REQUIRED)

find_package(KF5AkonadiSearch "5.7.40" CONFIG REQUIRED)
set_package_properties(KF5AkonadiSearch PROPERTIES DESCRIPTION "The Akonadi Search libraries" URL "http://www.kde.org" TYPE REQUIRED PURPOSE "Provides search capabilities in KMail and Akonadi")

include_directories(${kaddressbook_SOURCE_DIR} ${kaddressbook_BINARY_DIR})
add_definitions(-DQT_USE_QSTRINGBUILDER)
add_definitions(-DQT_NO_URL_CAST_FROM_STRING)
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)

find_package(KF5Prison ${KF5_VERSION} CONFIG REQUIRED)

add_definitions(-DTRANSLATION_DOMAIN=\"kaddressbook\")
add_definitions(-DQT_NO_CAST_FROM_ASCII)
add_definitions(-DQT_NO_CAST_TO_ASCII)
add_definitions(-DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT)

add_subdirectory(src)
add_subdirectory(kontactplugin)

install( FILES kaddressbook.renamecategories kaddressbook.categories DESTINATION ${KDE_INSTALL_CONFDIR} )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
