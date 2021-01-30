#include <jni.h>
#include <string>

#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/version.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "BundledAssetIOSystem.h"

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIversion(
        JNIEnv* env,
        jclass /* this */) {
    std::string version =
            "v" + std::to_string(aiGetVersionMajor()) +
            "." + std::to_string(aiGetVersionMinor()) +
            "." + std::to_string(aiGetVersionRevision());
    return env->NewStringUTF(version.c_str());
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_createJNIimporter(
        JNIEnv* env,
        jclass /* this */,
        jobject assetManager) {
    auto * importer = new Assimp::Importer();
    Assimp::DefaultIOSystem *ioSystem = new BundledAssetIOSystem(env, assetManager);
    importer->SetIOHandler(ioSystem);
    return (jlong) importer;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_readJNIfile(
        JNIEnv* env,
        jclass /* this */,
        jlong jImporter,
        jstring pathObj) {
    auto * importer = reinterpret_cast<Assimp::Importer *>(jImporter);

    const char *pFile = env->GetStringUTFChars(pathObj, nullptr);
    const aiScene* scene = importer->ReadFile( pFile,
                                          aiProcess_CalcTangentSpace       |
                                          aiProcess_Triangulate            |
                                          aiProcess_JoinIdenticalVertices  |
                                          aiProcess_SortByPType);
    env->ReleaseStringUTFChars(pathObj, pFile);
    return (jlong) scene;
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_errorJNImessage(
        JNIEnv* env,
        jclass, /* this */
        jlong jImporter) {
    auto * importer = reinterpret_cast<Assimp::Importer *>(jImporter);
    const char *message = importer->GetErrorString();
    return env->NewStringUTF(message);
}

extern "C" JNIEXPORT void JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_freeJNIscene(
        JNIEnv* env,
        jclass /* this */,
        jlong jImporter) {
    auto * importer = reinterpret_cast<Assimp::Importer *>(jImporter);
    importer->FreeScene();
}

extern "C" JNIEXPORT void JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_destroyJNIimporter(
        JNIEnv* env,
        jclass /* this */,
        jlong jImporter) {
    auto * importer = reinterpret_cast<Assimp::Importer *>(jImporter);
    delete importer;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getNumJNImeshes(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);

    return scene ? scene->mNumMeshes : 0;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getNumJNItextures(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);

    return scene ? scene->mNumTextures : 0;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getNumJNIcameras(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);

    return scene ? scene->mNumCameras : 0;
}


extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getNumJNIlights(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);

    return scene ? scene->mNumLights : 0;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getNumJNIanimations(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);

    return scene ? scene->mNumAnimations : 0;
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIembeddedLabel(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jstring labelObj) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);

    const char *pFile = env->GetStringUTFChars(labelObj, nullptr);
    const aiTexture * embed = scene->GetEmbeddedTexture(pFile);
    return env->NewStringUTF(embed->mFilename.C_Str());
}

extern "C" JNIEXPORT jint JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIembeddedLength(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jstring labelObj) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);

    const char *pFile = env->GetStringUTFChars(labelObj, nullptr);
    const aiTexture * embed = scene->GetEmbeddedTexture(pFile);
    return embed->mWidth;
}

extern "C" JNIEXPORT jint JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIembeddedOffset(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jstring labelObj) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);

    const char *pFile = env->GetStringUTFChars(labelObj, nullptr);
    const aiTexture * embed = scene->GetEmbeddedTexture(pFile);
    return embed->mHeight;
}

extern "C" JNIEXPORT jbyteArray JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIembeddedBytes(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jstring labelObj) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);

    const char *pFile = env->GetStringUTFChars(labelObj, nullptr);
    const aiTexture * embed = scene->GetEmbeddedTexture(pFile);

    size_t length = embed->mWidth;
    off_t  offset = embed->mHeight;
    auto * data = (jbyte *)reinterpret_cast<uint8_t *>(embed->pcData);

    jbyteArray result;
    result = env->NewByteArray(length);
    env->SetByteArrayRegion(result,offset,length,data);
    return result;
}