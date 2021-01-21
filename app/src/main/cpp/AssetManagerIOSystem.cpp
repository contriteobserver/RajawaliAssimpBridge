#include <android/asset_manager.h>
#include <assimp/DefaultIOStream.h>

#include "AssetManagerIOSystem.h"

/** Tests for the existence of a file at the given path. */
bool AssetManagerIOSystem::Exists( const char* pFile) const {
    assert(NULL != mApkAssetManager);
    AAsset *  asset = AAssetManager_open(mApkAssetManager, pFile, AASSET_MODE_UNKNOWN);
    if (!asset) { return false; }
    if (asset) AAsset_close(asset);
    return true;
}

// -------------------------------------------------------------------
/** Open a new file with a given path. */
Assimp::IOStream* AssetManagerIOSystem::Open( const char* pFile, const char* pMode) {
    assert(NULL != mApkAssetManager);
    AAsset *  asset = AAssetManager_open(mApkAssetManager, pFile, AASSET_MODE_UNKNOWN);
    if (!asset) { return NULL; }

    return new AssetIOStream(asset);
}

// -------------------------------------------------------------------
/** Closes the given file and releases all resources associated with it. */
void AssetManagerIOSystem::Close( Assimp::IOStream* pFile) {
    delete reinterpret_cast<AssetIOStream *>(pFile);
}

