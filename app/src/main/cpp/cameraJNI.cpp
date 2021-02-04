#include <jni.h>
#include <string>

#include <assimp/scene.h>
#include <assimp/camera.h>

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIcameraName(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiCamera * camera = scene->mCameras[reinterpret_cast<int>(jIndex)];
    aiString name = camera->mName;
    return env->NewStringUTF(name.C_Str());
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIcameraUpAxis(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiCamera * camera = scene->mCameras[reinterpret_cast<int>(jIndex)];
    aiVector3D up = camera->mUp;
    jfloat buf[] = { up.x, up.y, up.z };
    jfloatArray result = env->NewFloatArray(3);
    env->SetFloatArrayRegion(result,0, 3, buf);
    return result;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIcameraLookAt(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    aiQuaternion rotation;
    aiVector3D position;
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiCamera* camera = scene->mCameras[reinterpret_cast<int>(jIndex)];
    aiString name = aiString(camera->mName);
    aiNode * node = scene->mRootNode->FindNode(name.C_Str());
    aiMatrix4x4 transform = node->mTransformation;
    transform.DecomposeNoScaling (rotation,position);
    rotation.Normalize();
    aiVector3D dir = rotation.Rotate(camera->mLookAt);
    jfloat buf[] = { dir.x, dir.y, dir.z };
    jfloatArray result = env->NewFloatArray(3);
    env->SetFloatArrayRegion(result,0, 3, buf);
    return result;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIcameraPosition(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    aiQuaternion rotation;
    aiVector3D position;
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiCamera * camera = scene->mCameras[reinterpret_cast<int>(jIndex)];
    aiString name = aiString(camera->mName);
    aiNode * node = scene->mRootNode->FindNode(name.C_Str());
    aiMatrix4x4 transform = node->mTransformation;
    transform.DecomposeNoScaling (rotation,position);
    aiVector3D pos = camera->mPosition;
    pos.x += position.x; pos.y += position.y; pos.z += position.z;
    jfloat buf[] = { pos.x, pos.y, pos.z };
    jfloatArray result = env->NewFloatArray(3);
    env->SetFloatArrayRegion(result,0, 3, buf);
    return result;
}

