#ifndef RAJAWALI_ASSIMP_BRIDGE_BUNDLEDASSETIOSYSTEM_H
#define RAJAWALI_ASSIMP_BRIDGE_BUNDLEDASSETIOSYSTEM_H

#include <android/asset_manager_jni.h>

#include <assimp/DefaultIOSystem.h>
#include <assimp/IOStream.hpp>

class BundledAssetIOSystem : public Assimp::DefaultIOSystem {

public:
    AAssetManager* mApkAssetManager;

    BundledAssetIOSystem(JNIEnv* env, jobject assetManager) { mApkAssetManager = AAssetManager_fromJava(env, assetManager); }
    ~BundledAssetIOSystem() {};

    bool Exists( const char* pFile) const;

    Assimp::IOStream* Open( const char* pFile, const char* pMode = "rb");

    void Close( Assimp::IOStream* pFile);

private:

    class AssetIOStream : public Assimp::IOStream {
        AAsset * asset;

    public:
        AssetIOStream(AAsset *asset) { this->asset = asset; };
        ~AssetIOStream() { AAsset_close(asset); }

        size_t Read(void* pvBuffer, size_t pSize, size_t pCount) { return AAsset_read(asset, pvBuffer, pSize * pCount);}
        size_t Write(const void* pvBuffer, size_t pSize, size_t pCount) { return 0; };
        aiReturn Seek(size_t pOffset, aiOrigin pOrigin) { return (AAsset_seek(asset, pOffset, pOrigin) >= 0 ? aiReturn_SUCCESS : aiReturn_FAILURE); }
        size_t Tell() const { return(AAsset_getLength(asset) - AAsset_getRemainingLength(asset)); };
        size_t FileSize() const  { return  AAsset_getLength(asset); }
        void Flush() { }
    };

};


#endif //RAJAWALI_ASSIMP_BRIDGE_BUNDLEDASSETIOSYSTEM_H
