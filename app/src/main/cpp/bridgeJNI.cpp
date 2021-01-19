#include <jni.h>
#include <string>

#include <assimp/version.h>
#include <assimp/Importer.hpp>

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_getJNIversion(
        JNIEnv* env,
        jobject /* this */) {
    std::string version =
            "v" + std::to_string(aiGetVersionMajor()) +
            "." + std::to_string(aiGetVersionMinor()) +
            "." + std::to_string(aiGetVersionRevision());
    return env->NewStringUTF(version.c_str());
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_createJNIimporter(
        JNIEnv* env,
        jobject /* this */) {
    Assimp::Importer* importer = new Assimp::Importer();
    return (jlong) importer;
}

extern "C" JNIEXPORT void JNICALL
Java_org_rajawali_rajawaliassimpbridge_Bridge_destroyJNIimporter(
        JNIEnv* env,
        jobject, /* this */
        jlong jImporter) {
    Assimp::Importer* importer = reinterpret_cast<Assimp::Importer *>(jImporter);
    delete importer;
    return;
}