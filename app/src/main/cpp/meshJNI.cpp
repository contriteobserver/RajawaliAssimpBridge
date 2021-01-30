#include <jni.h>
#include <string>

#include <assimp/mesh.h>
#include <assimp/scene.h>

extern "C" JNIEXPORT jint JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNImaterialIndex(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jIndex)];
    return mesh->mMaterialIndex;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIvertices(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNInormals(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIcolors(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNItextureCoords(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIindices(
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
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNImeshName(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jIndex)];
    return env->NewStringUTF(mesh->mName.C_Str());
}

extern "C" JNIEXPORT jint JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNInumAnimeshes(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jIndex) {
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jIndex)];
    return mesh->mNumAnimMeshes;
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_org_rajawali3d_rajawaliassimpbridge_Bridge_getJNIanimeshVertices(
        JNIEnv* env,
        jclass /* this */,
        jlong jScene,
        jint jMeshIndex,
        jint jAnimeshIndex) {
    jfloatArray result;
    auto * scene = reinterpret_cast<aiScene *>(jScene);
    aiMesh * mesh = scene->mMeshes[reinterpret_cast<int>(jMeshIndex)];
    if(mesh->mNumAnimMeshes < reinterpret_cast<int>(jAnimeshIndex)) return result = env->NewFloatArray(0);
    if(reinterpret_cast<int>(jAnimeshIndex) < 0) return result = env->NewFloatArray(0);

    aiAnimMesh * animesh = mesh->mAnimMeshes[reinterpret_cast<int>(jAnimeshIndex)];
    result = env->NewFloatArray(3 * animesh->mNumVertices);
    for(int i=0; i<animesh->mNumVertices; i++) {
        aiVector3D vertex = animesh->mVertices[i];
        jfloat buf[3];
        buf[0] = vertex.x;
        buf[1] = vertex.y;
        buf[2] = vertex.z;
        env->SetFloatArrayRegion(result,3*i,3, buf);
    }
    return result;
}