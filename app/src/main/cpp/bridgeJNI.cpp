#include <jni.h>
#include <string>

#include <assimp/version.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "AssetManagerIOSystem.h"

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIversion(
        JNIEnv* env,
        jclass /* this */) {
    std::string version =
            "v" + std::to_string(aiGetVersionMajor()) +
            "." + std::to_string(aiGetVersionMinor()) +
            "." + std::to_string(aiGetVersionRevision());
    return env->NewStringUTF(version.c_str());
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_createJNIimporter(
        JNIEnv* env,
        jclass /* this */,
        jobject assetManager) {
    Assimp::Importer* importer = new Assimp::Importer();
    Assimp::DefaultIOSystem *ioSystem = new AssetManagerIOSystem(env, assetManager);
    importer->SetIOHandler(ioSystem);
    return (jlong) importer;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_readJNIfile(
        JNIEnv* env,
        jclass /* this */,
        jlong jImporter,
        jstring pathObj) {
    Assimp::Importer* importer = reinterpret_cast<Assimp::Importer *>(jImporter);

    const char *pFile = env->GetStringUTFChars(pathObj, 0);
    const aiScene* scene = importer->ReadFile( pFile,
                                          aiProcess_CalcTangentSpace       |
                                          aiProcess_Triangulate            |
                                          aiProcess_JoinIdenticalVertices  |
                                          aiProcess_SortByPType);
    env->ReleaseStringUTFChars(pathObj, pFile);
    return (jlong) scene;
}

extern "C" JNIEXPORT void JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_destroyJNIimporter(
        JNIEnv* env,
        jclass /* this */,
        jlong jImporter) {
    Assimp::Importer* importer = reinterpret_cast<Assimp::Importer *>(jImporter);
    delete importer;
    return;
}