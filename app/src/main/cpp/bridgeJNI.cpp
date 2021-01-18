#include <jni.h>
#include <string>

extern "C" unsigned int aiGetVersionMajor (void);
extern "C" unsigned int aiGetVersionMinor (void);
extern "C" unsigned int aiGetVersionRevision(void);

extern "C" JNIEXPORT jstring JNICALL
Java_org_rajawali_rajawaliassimpbridge_MainActivity_getAssimpVersion(
        JNIEnv* env,
        jobject /* this */) {
    std::string version =
            "v" + std::to_string(aiGetVersionMajor()) +
            "." + std::to_string(aiGetVersionMinor()) +
            "." + std::to_string(aiGetVersionRevision());
    return env->NewStringUTF(version.c_str());
}