#include <jni.h>
#include <string>

#include <assimp/scene.h>
#include <assimp/anim.h>

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIanimationName(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiAnimation * anim = scene->mAnimations[reinterpret_cast<int>(jIndex)];
    aiString name = anim->mName;
    return env->NewStringUTF(name.C_Str());
}

extern "C" JNIEXPORT jdouble JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIanimationDuration(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiAnimation * anim = scene->mAnimations[reinterpret_cast<int>(jIndex)];
    return anim->mDuration / anim->mTicksPerSecond;
}

extern "C" JNIEXPORT jint JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNInumChannels(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiAnimation * anim = scene->mAnimations[reinterpret_cast<int>(jIndex)];
    return anim->mNumChannels;
}

extern "C" JNIEXPORT jint JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNInumMeshChannels(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiAnimation * anim = scene->mAnimations[reinterpret_cast<int>(jIndex)];
    return anim->mNumMeshChannels;
}

extern "C" JNIEXPORT jint JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNInumMorphMeshChannels(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiAnimation * anim = scene->mAnimations[reinterpret_cast<int>(jIndex)];
    return anim->mNumMorphMeshChannels;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNItranslationKeyframes(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    jfloatArray result;
    auto *scene = reinterpret_cast<aiScene *>(jScene);
    aiAnimation *anim = scene->mAnimations[reinterpret_cast<int>(jIndex)];
    if(anim->mNumChannels<1) return result = env->NewFloatArray(0);

    jsize length = anim->mChannels[0]->mNumPositionKeys;
    aiVectorKey *keyframes = anim->mChannels[0]->mPositionKeys;
    result = env->NewFloatArray(4 * length);
    for(int i=0; i<length; i++) {
        jfloat buf[4];
        buf[0] = (float)(keyframes[i].mTime / anim->mTicksPerSecond);
        buf[1] = keyframes[i].mValue.x;
        buf[2] = keyframes[i].mValue.y;
        buf[3] = keyframes[i].mValue.z;
        env->SetFloatArrayRegion(result,4*i,4, buf);
    }
    return result;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIorientationKeyframes(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    jfloatArray result;
    auto *scene = reinterpret_cast<aiScene *>(jScene);
    aiAnimation *anim = scene->mAnimations[reinterpret_cast<int>(jIndex)];
    if(anim->mNumChannels<1) return result = env->NewFloatArray(0);

    jsize length = anim->mChannels[0]->mNumRotationKeys;
    aiQuatKey *keyframes = anim->mChannels[0]->mRotationKeys;
    result = env->NewFloatArray(5 * length);
    for(int i=0; i<length; i++) {
        jfloat buf[5];
        buf[0] = (float)(keyframes[i].mTime / anim->mTicksPerSecond);
        buf[1] = keyframes[i].mValue.w;
        buf[2] = keyframes[i].mValue.x;
        buf[3] = keyframes[i].mValue.y;
        buf[4] = keyframes[i].mValue.z;
        env->SetFloatArrayRegion(result,5*i,5, buf);
    }
    return result;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIscalingKeyframes(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    jfloatArray result;
    auto *scene = reinterpret_cast<aiScene *>(jScene);
    aiAnimation *anim = scene->mAnimations[reinterpret_cast<int>(jIndex)];
    if(anim->mNumChannels<1) return result = env->NewFloatArray(0);

    jsize length = anim->mChannels[0]->mNumScalingKeys;
    aiVectorKey *keyframes = anim->mChannels[0]->mScalingKeys;
    result = env->NewFloatArray(4 * length);
    for(int i=0; i<length; i++) {
        jfloat buf[4];
        buf[0] = (float)(keyframes[i].mTime / anim->mTicksPerSecond);
        buf[1] = keyframes[i].mValue.x;
        buf[2] = keyframes[i].mValue.y;
        buf[3] = keyframes[i].mValue.z;
        env->SetFloatArrayRegion(result,4*i,4, buf);
    }
    return result;
}

extern "C" JNIEXPORT jint JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNInumShapeKeys(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    jfloatArray result;
    auto *scene = reinterpret_cast<aiScene *>(jScene);
    aiAnimation *anim = scene->mAnimations[reinterpret_cast<int>(jIndex)];
    if(anim->mNumMorphMeshChannels<1) {
        return 0;
    } else {
        return anim->mMorphMeshChannels[0]->mNumKeys;
    }
}

extern "C" JNIEXPORT jintArray JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIshapeKey(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jAnimation,
        jint jIndex) {
    jintArray result;
    auto *scene = reinterpret_cast<aiScene *>(jScene);
    aiAnimation *anim = scene->mAnimations[reinterpret_cast<int>(jAnimation)];
    if(jIndex > anim->mMorphMeshChannels[0]->mNumKeys) return result = env->NewIntArray(0);
    if(jIndex<0) return result = env->NewIntArray(0);

    aiMeshMorphKey keyFrame = anim->mMorphMeshChannels[0]->mKeys[jIndex];
    result = env->NewIntArray(keyFrame.mNumValuesAndWeights);
    for(int i=0; i<keyFrame.mNumValuesAndWeights; i++) {
        unsigned int data = keyFrame.mValues[i];
        env->SetIntArrayRegion(result, i, 1, reinterpret_cast<const jint *>(&data));
    }
    return result;
}
