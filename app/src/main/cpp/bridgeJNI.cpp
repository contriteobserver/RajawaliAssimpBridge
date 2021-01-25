#include <jni.h>
#include <string>

#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/version.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "BundledAssetIOSystem.h"

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
    auto * importer = new Assimp::Importer();
    Assimp::DefaultIOSystem *ioSystem = new BundledAssetIOSystem(env, assetManager);
    importer->SetIOHandler(ioSystem);
    return (jlong) importer;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_readJNIfile(
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
Java_org_rajawali_rajawaliassimpbridge_Bridge_errorJNImessage(
        JNIEnv* env,
        jclass, /* this */
        jlong jImporter) {
    auto * importer = reinterpret_cast<Assimp::Importer *>(jImporter);
    const char *message = importer->GetErrorString();
    return env->NewStringUTF(message);
}

extern "C" JNIEXPORT void JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_freeJNIscene(
        JNIEnv* env,
        jclass /* this */,
        jlong jImporter) {
    auto * importer = reinterpret_cast<Assimp::Importer *>(jImporter);
    importer->FreeScene();
}

extern "C" JNIEXPORT void JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_destroyJNIimporter(
        JNIEnv* env,
        jclass /* this */,
        jlong jImporter) {
    auto * importer = reinterpret_cast<Assimp::Importer *>(jImporter);
    delete importer;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getNumJNImeshes(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);

    return scene->mNumMeshes;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getNumJNItextures(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);

    return scene->mNumTextures;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getNumJNIcameras(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);

    return scene->mNumCameras;
}


extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getNumJNIlights(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);

    return scene->mNumLights;
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getNumJNIanimations(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);

    return scene->mNumAnimations;
}

extern "C" JNIEXPORT jint JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNImaterialIndex(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jIndex)];
    return mesh->mMaterialIndex;
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNImaterialName(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * mtl = scene->mMaterials[reinterpret_cast<int>(jIndex)];
    return env->NewStringUTF(mtl->GetName().C_Str());
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_hasJNIambientTexture(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * mtl = scene->mMaterials[reinterpret_cast<int>(jIndex)];
    aiString path;

    return(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &path));
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_hasJNIdiffuseTexture(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * mtl = scene->mMaterials[reinterpret_cast<int>(jIndex)];
    aiString path;

    return(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &path));
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_hasJNIspecularTexture(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * mtl = scene->mMaterials[reinterpret_cast<int>(jIndex)];
    aiString path;

    return(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &path));
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIvertices(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
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
    auto * scene = reinterpret_cast<aiScene *>(jScene);
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
    auto * scene = reinterpret_cast<aiScene *>(jScene);
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
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jIndex)];

    jfloatArray result;
    result = env->NewFloatArray(2 * mesh->mNumVertices);
    for(int i=0; i<mesh->mNumVertices; i++) {
        aiVector3D coords;
        if(mesh->mTextureCoords[0]) coords = mesh->mTextureCoords[0][i];
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
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jIndex)];
    jintArray result;
    result = env->NewIntArray(3 * mesh->mNumFaces);
    for(int i=0; i<mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        jint buf[3]; // Rajawali expects triangles
        switch(face.mNumIndices) {
            case 0: // nothing to see
                buf[0] = 0;
                buf[1] = 0;
                buf[2] = 0;
                break;
            case 1: // unattached point
                buf[0] = face.mIndices[0];
                buf[1] = face.mIndices[0];
                buf[2] = face.mIndices[0];
                break;
            case 2: // a loose edge
                buf[0] = face.mIndices[0];
                buf[1] = face.mIndices[1];
                buf[2] = face.mIndices[0];
                break;
            default: // reporting only the first three vertices
                buf[0] = face.mIndices[0];
                buf[1] = face.mIndices[1];
                buf[2] = face.mIndices[2];
                break;
        }
        env->SetIntArrayRegion(result,3*i, 3, buf);
    }
    return result;
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNImeshName(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jIndex)];
    return env->NewStringUTF(mesh->mName.C_Str());
}

extern "C" JNIEXPORT jint JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIshadingModel(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * material = scene->mMaterials[reinterpret_cast<int>(jIndex)];

    int model;
    return (AI_SUCCESS == material->Get(AI_MATKEY_SHADING_MODEL, model) ? model : 0);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_enableJNIwireframe(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * material = scene->mMaterials[reinterpret_cast<int>(jIndex)];

    bool enableWireframe;
    return (AI_SUCCESS == material->Get(AI_MATKEY_ENABLE_WIREFRAME, enableWireframe) ? enableWireframe : false);
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIambientRGBA(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * mtl = scene->mMaterials[reinterpret_cast<int>(jIndex)];

    aiColor4D ambient;
    jfloat buf[] = {0,0,0,0};
    jfloatArray result;
    result = env->NewFloatArray(4);
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient)) {
        buf[0] = ambient.r;
        buf[1] = ambient.g;
        buf[2] = ambient.b;
        buf[3] = ambient.a;
    }
    env->SetFloatArrayRegion(result,0, 4, buf);
    return result;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIdiffuseRGBA(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * mtl = scene->mMaterials[reinterpret_cast<int>(jIndex)];

    aiColor4D diffuse;
    jfloat buf[] = {0,0,0,0};
    jfloatArray result;
    result = env->NewFloatArray(4);
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse)) {
        buf[0] = diffuse.r;
        buf[1] = diffuse.g;
        buf[2] = diffuse.b;
        buf[3] = diffuse.a;
    }
    env->SetFloatArrayRegion(result,0, 4, buf);
    return result;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIspecularRGBA(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * mtl = scene->mMaterials[reinterpret_cast<int>(jIndex)];

    aiColor4D specular;
    jfloat buf[] = {0,0,0,0};
    jfloatArray result;
    result = env->NewFloatArray(4);
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular)) {
        buf[0] = specular.r;
        buf[1] = specular.g;
        buf[2] = specular.b;
        buf[3] = specular.a;
    }
    env->SetFloatArrayRegion(result,0, 4, buf);
    return result;
}

extern "C" JNIEXPORT jfloat JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIopacity(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * material = scene->mMaterials[reinterpret_cast<int>(jIndex)];

    float opacity;
    return (AI_SUCCESS == material->Get(AI_MATKEY_OPACITY, opacity) ? opacity : 1);
}

extern "C" JNIEXPORT jfloat JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNItransparency(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * material = scene->mMaterials[reinterpret_cast<int>(jIndex)];

    float transparancy;
    return (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_TRANSPARENT, transparancy) ? transparancy : 1);
}

extern "C" JNIEXPORT jfloat JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIshininess(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * material = scene->mMaterials[reinterpret_cast<int>(jIndex)];

    float shininess;
    return (AI_SUCCESS == material->Get(AI_MATKEY_SHININESS, shininess) ? shininess : 0.3f);
}


extern "C" JNIEXPORT jfloat JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIstrength(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * material = scene->mMaterials[reinterpret_cast<int>(jIndex)];

    float strength;
    return (AI_SUCCESS == material->Get(AI_MATKEY_SHININESS_STRENGTH, strength) ? strength : 1);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIdoubleSided(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * material = scene->mMaterials[reinterpret_cast<int>(jIndex)];

    bool twoSided;
    return (AI_SUCCESS == material->Get(AI_MATKEY_TWOSIDED, twoSided) ? twoSided : false);
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIambientName(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {

    auto * scene = reinterpret_cast<aiScene *>(jScene);
    size_t index = jIndex;
    aiMaterial *mtl = scene->mMaterials[index];
    aiString path;

    if(AI_SUCCESS != mtl->GetTexture(aiTextureType_AMBIENT, 0, &path)) {
        path = "";
    }
    return env->NewStringUTF(path.C_Str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIdiffuseName(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {

    auto * scene = reinterpret_cast<aiScene *>(jScene);
    size_t index = jIndex;
    aiMaterial *mtl = scene->mMaterials[index];
    aiString path;

    if(AI_SUCCESS != mtl->GetTexture(aiTextureType_DIFFUSE, 0, &path)) {
        path = "";
    }
    return env->NewStringUTF(path.C_Str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIspecularName(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {

    auto * scene = reinterpret_cast<aiScene *>(jScene);
    size_t index = jIndex;
    aiMaterial *mtl = scene->mMaterials[index];
    aiString path;

    if(AI_SUCCESS != mtl->GetTexture(aiTextureType_SPECULAR, 0, &path)) {
        path = "";
    }
    return env->NewStringUTF(path.C_Str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIembeddedLabel(
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
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIembeddedLength(
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
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIembeddedOffset(
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
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIembeddedBytes(
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