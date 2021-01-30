#include <jni.h>
#include <string>

#include <assimp/material.h>
#include <assimp/scene.h>

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNImaterialName(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * mtl = scene->mMaterials[reinterpret_cast<int>(jIndex)];
    return env->NewStringUTF(mtl->GetName().C_Str());
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_hasJNIambientTexture(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_hasJNIdiffuseTexture(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_hasJNIspecularTexture(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_hasJNInormalMap(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMaterial * mtl = scene->mMaterials[reinterpret_cast<int>(jIndex)];
    aiString path;

    return(AI_SUCCESS == mtl->GetTexture(aiTextureType_NORMALS, 0, &path));
}

extern "C" JNIEXPORT jint JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIshadingModel(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_enableJNIwireframe(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIambientRGBA(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIdiffuseRGBA(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIspecularRGBA(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIopacity(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNItransparency(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIshininess(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIstrength(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIdoubleSided(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIambientName(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIdiffuseName(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIspecularName(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNInormalMapName(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {

    auto * scene = reinterpret_cast<aiScene *>(jScene);
    size_t index = jIndex;
    aiMaterial *mtl = scene->mMaterials[index];
    aiString path;

    if(AI_SUCCESS != mtl->GetTexture(aiTextureType_NORMALS, 0, &path)) {
        path = "";
    }
    return env->NewStringUTF(path.C_Str());
}



