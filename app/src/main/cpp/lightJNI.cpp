#include <jni.h>
#include <string>

#include <assimp/scene.h>
#include <assimp/light.h>

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIlightName(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiLight * light = scene->mLights[reinterpret_cast<int>(jIndex)];
    aiString name = light->mName;
    return env->NewStringUTF(name.C_Str());
}

extern "C" JNIEXPORT jint JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIlightType(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiLight * light = scene->mLights[reinterpret_cast<int>(jIndex)];
    return (jint) light->mType;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIlightDirection(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    aiQuaternion rotation;
    aiVector3D position;
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiLight * light = scene->mLights[reinterpret_cast<int>(jIndex)];
    aiString name = aiString(light->mName);
    aiNode * node = scene->mRootNode->FindNode(name.C_Str());
    aiMatrix4x4 transform = node->mTransformation;
    transform.DecomposeNoScaling (rotation,position);
    rotation.Normalize();
    aiVector3D dir = rotation.Rotate(light->mDirection);
    jfloat buf[] = { dir.x, dir.y, dir.z };
    jfloatArray result = env->NewFloatArray(3);
    env->SetFloatArrayRegion(result,0, 3, buf);
    return result;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIlightPosition(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    aiQuaternion rotation;
    aiVector3D position;
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiLight * light = scene->mLights[reinterpret_cast<int>(jIndex)];
    aiString name = aiString(light->mName);
    aiNode * node = scene->mRootNode->FindNode(name.C_Str());
    aiMatrix4x4 transform = node->mTransformation;
    transform.DecomposeNoScaling (rotation,position);
    aiVector3D pos = light->mPosition;
    pos.x += position.x; pos.y += position.y; pos.z += position.z;
    jfloat buf[] = { pos.x, pos.y, pos.z };
    jfloatArray result = env->NewFloatArray(3);
    env->SetFloatArrayRegion(result,0, 3, buf);
    return result;
}


extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIlightAmbientRGB(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiLight * light = scene->mLights[reinterpret_cast<int>(jIndex)];
    aiColor3D color = light->mColorAmbient;
    jfloat buf[] = { color.r, color.g, color.b };
    jfloatArray result = env->NewFloatArray(3);
    env->SetFloatArrayRegion(result,0, 3, buf);
    return result;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIlightDiffuseRGB(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiLight * light = scene->mLights[reinterpret_cast<int>(jIndex)];
    aiColor3D color = light->mColorDiffuse;
    jfloat buf[] = { color.r, color.g, color.b };
    jfloatArray result = env->NewFloatArray(3);
    env->SetFloatArrayRegion(result,0, 3, buf);
    return result;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIlightSpecularRGB(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiLight * light = scene->mLights[reinterpret_cast<int>(jIndex)];
    aiColor3D color = light->mColorSpecular;
    jfloat buf[] = { color.r, color.g, color.b };
    jfloatArray result = env->NewFloatArray(3);
    env->SetFloatArrayRegion(result,0, 3, buf);
    return result;
}
