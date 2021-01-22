#include <jni.h>
#include <string>

#include <assimp/mesh.h>
#include <assimp/scene.h>
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

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getNumJNImeshes(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);

    return scene->mNumMeshes;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getNumJNImaterials(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);

    return scene->mNumMaterials;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getNumJNItextures(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);

    return scene->mNumTextures;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getNumJNIcameras(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);

    return scene->mNumCameras;
}


extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getNumJNIlights(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);

    return scene->mNumLights;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getNumJNIanimations(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);

    return scene->mNumAnimations;
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

extern "C" JNIEXPORT jint JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNImaterialIndex(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jIndex)];
    return mesh->mMaterialIndex;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIvertices(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jIndex)];

    jfloatArray result;
    result = env->NewFloatArray(3 * mesh->mNumVertices);
    for(int i=0; i<mesh->mNumVertices; i++) {
        aiVector3D vertex = mesh->mVertices[i];
        jfloat buf[3];
        buf[0] = vertex.x;
        buf[1] = vertex.y;
        buf[2] = vertex.z;
        env->SetFloatArrayRegion(result,3*i,3, buf);
    }
    return result;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNInormals(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jIndex)];

    jfloatArray result;
    result = env->NewFloatArray(3 * mesh->mNumVertices);
    for(int i=0; i<mesh->mNumVertices; i++) {
        aiVector3D normal = mesh->mNormals[i];
        jfloat buf[3];
        buf[0] = normal.x;
        buf[1] = normal.y;
        buf[2] = normal.z;
        env->SetFloatArrayRegion(result,3*i,3, buf);
    }
    return result;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIcolors(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jIndex)];

    jfloatArray result;
    result = env->NewFloatArray(4 * mesh->mNumVertices);
    for(int i=0; i<mesh->mNumVertices; i++) {
        aiColor4D color;
        if(mesh->mColors[0]) color = mesh->mColors[0][i];
        jfloat buf[4];
        buf[0] = color.r;
        buf[1] = color.b;
        buf[2] = color.g;
        buf[3] = color.a;
        env->SetFloatArrayRegion(result,4*i,4, buf);
    }
    return result;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNItextureCoords(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jIndex)];

    jfloatArray result;
    result = env->NewFloatArray(2 * mesh->mNumUVComponents[0]);
    for(int i=0; i<mesh->mNumUVComponents[0]; i++) {
        aiVector3D coords = mesh->mTextureCoords[0][i];
        jfloat buf[2];
        buf[0] = coords.x;
        buf[1] = coords.y;
        env->SetFloatArrayRegion(result,2*i,2, buf);
    }
    return result;
}

extern "C" JNIEXPORT jintArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIindices(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jIndex)];
    jintArray result;
    result = env->NewIntArray(3 * mesh->mNumFaces);
    for(int i=0; i<mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        jint buf[face.mNumIndices];
        for(int j=0; j<face.mNumIndices; j++) {
            buf[j] = face.mIndices[j];
        }
        env->SetIntArrayRegion(result,3*i,3, buf);
    }
    return result;
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNImeshName(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jIndex)];
    return env->NewStringUTF(mesh->mName.C_Str());
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIdiffuseRGBA(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * material = scene->mMaterials[reinterpret_cast<int>(jIndex)];

    aiColor3D color (0.f,0.f,0.f);
    material->Get(AI_MATKEY_COLOR_DIFFUSE,color);
    jfloatArray result;
    result = env->NewFloatArray(4);
    jfloat buf[4];
    buf[0] = color.r;
    buf[1] = color.g;
    buf[2] = color.b;
    buf[3] = 1;
    env->SetFloatArrayRegion(result,0,4, buf);
    return result;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIambientRGBA(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    aiScene * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * material = scene->mMaterials[reinterpret_cast<int>(jIndex)];

    aiColor3D color (0.f,0.f,0.f);
    material->Get(AI_MATKEY_COLOR_AMBIENT,color);
    jfloatArray result;
    result = env->NewFloatArray(4);
    jfloat buf[4];
    buf[0] = color.r;
    buf[1] = color.g;
    buf[2] = color.b;
    buf[3] = 1;
    env->SetFloatArrayRegion(result,0,4, buf);
    return result;
}