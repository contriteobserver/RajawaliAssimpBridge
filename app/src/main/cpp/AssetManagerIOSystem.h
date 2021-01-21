#ifndef RAJAWALI_ASSIMP_BRIDGE_ANDROIDASSETIOSYSTEM_H
#define RAJAWALI_ASSIMP_BRIDGE_ANDROIDASSETIOSYSTEM_H

#include <string">

#include <assimp/DefaultIOSystem.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/native_activity.h>
class AndroidAssetIOSystem : public DefaultIOSystem {

public:
    AAssetManager* mApkAssetManager;

    /** Constructor. */
    AndroidAssetIOSystem() {};

    /** Destructor. */
    ~AndroidAssetIOSystem() {};

    // -------------------------------------------------------------------
    /** Tests for the existence of a file at the given path. */
    bool Exists( const char* pFile) const;

    // -------------------------------------------------------------------
    /** Returns the directory separator. */
    char getOsSeparator() const;

    // -------------------------------------------------------------------
    /** Open a new file with a given path. */
    Assimp::IOStream* Open( const char* pFile, const char* pMode = "rb");

    // -------------------------------------------------------------------
    /** Closes the given file and releases all resources associated with it. */
    void Close( Assimp::IOStream* pFile);

    // -------------------------------------------------------------------
    /** Compare two paths */
    bool ComparePaths (const char* one, const char* second) const;

    /** @brief get the file name of a full filepath
     * example: /tmp/archive.tar.gz -> archive.tar.gz
     */
    static std::string fileName( const std::string &path );

    /** @brief get the complete base name of a full filepath
     * example: /tmp/archive.tar.gz -> archive.tar
     */
    static std::string completeBaseName( const std::string &path);

    /** @brief get the path of a full filepath
     * example: /tmp/archive.tar.gz -> /tmp/
     */
    static std::string absolutePath( const std::string &path);
};


#endif //RAJAWALI_ASSIMP_BRIDGE_ANDROIDASSETIOSYSTEM_H
