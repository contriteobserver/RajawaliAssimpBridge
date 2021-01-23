# RajawaliAssimpBridge
Example Bridge between [Rajawali](https://github.com/Rajawali/Rajawali) and the [Open Asset Import Library (assimp)](https://www.assimp.org)

### Initial crude approach to cross-compiling the Open Asset Import Library
A better approach is needed, will revisit this once the bridge foundations are in place.
```
cd

rm -rf ~/assimp
rm -rf ~/RajawaliAssimpBridge

git clone https://github.com/assimp/assimp.git
git clone https://github.com/contriteobserver/RajawaliAssimpBridge.git

mkdir ~/assimp/contrib/android-cmake/build
mkdir -p ~/RajawaliAssimpBridge/app/src/main/cpp/lib/armeabi-v7a/
mkdir -p ~/RajawaliAssimpBridge/app/src/main/cpp/lib/arm64-v8a/
mkdir -p ~/RajawaliAssimpBridge/app/src/main/cpp/lib/x86/
mkdir -p ~/RajawaliAssimpBridge/app/src/main/cpp/lib/x86_64/

rm -f ~/assimp/CMakeCache.txt
rm -rf ~/assimp/contrib/android-cmake/build
mkdir ~/assimp/contrib/android-cmake/build
cd assimp/contrib/android-cmake/build
cmake -DCMAKE_TOOLCHAIN_FILE=~/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake -DANDROID_PLATFORM=21 -DANDROID_NDK=~/Android/Sdk/ndk-bundle/ -DBUILD_SHARED_LIBS=OFF -DASSIMP_NO_EXPORT=ON -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_ZLIB=ON -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi-v7a with NEON" ~/assimp
cmake ~/assimp/CMakeLists.txt
make -j4 clean all
mkdir -p ~/RajawaliAssimpBridge/app/src/main/cpp/lib/armeabi-v7a
cp contrib/zlib/libzlibstatic.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/armeabi-v7a/
cp lib/libassimp.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/armeabi-v7a/
cd

rm -f ~/assimp/CMakeCache.txt
rm -rf ~/assimp/contrib/android-cmake/build
mkdir ~/assimp/contrib/android-cmake/build
cd assimp/contrib/android-cmake/build
cmake -DCMAKE_TOOLCHAIN_FILE=~/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake -DANDROID_PLATFORM=21 -DANDROID_NDK=~/Android/Sdk/ndk-bundle/ -DBUILD_SHARED_LIBS=OFF -DASSIMP_NO_EXPORT=ON -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_ZLIB=ON -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="arm64-v8a" ~/assimp
cmake ~/assimp/CMakeLists.txt
make -j4 clean all
mkdir -p ~/RajawaliAssimpBridge/app/src/main/cpp/lib/arm64-v8a
cp contrib/zlib/libzlibstatic.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/arm64-v8a/
cp lib/libassimp.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/arm64-v8a/
cd

rm -f ~/assimp/CMakeCache.txt
rm -rf ~/assimp/contrib/android-cmake/build
mkdir ~/assimp/contrib/android-cmake/build
cd assimp/contrib/android-cmake/build
cmake -DCMAKE_TOOLCHAIN_FILE=~/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake -DANDROID_PLATFORM=21 -DANDROID_NDK=~/Android/Sdk/ndk-bundle/ -DBUILD_SHARED_LIBS=OFF -DASSIMP_NO_EXPORT=ON -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_ZLIB=ON -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="x86" ~/assimp
cmake ~/assimp/CMakeLists.txt
make -j4 clean all
mkdir -p ~/RajawaliAssimpBridge/app/src/main/cpp/lib/x86
cp contrib/zlib/libzlibstatic.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/x86/
cp lib/libassimp.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/x86/
cd

rm -f ~/assimp/CMakeCache.txt
rm -rf ~/assimp/contrib/android-cmake/build
mkdir ~/assimp/contrib/android-cmake/build
cd assimp/contrib/android-cmake/build
cmake -DCMAKE_TOOLCHAIN_FILE=~/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake -DANDROID_PLATFORM=21 -DANDROID_NDK=~/Android/Sdk/ndk-bundle/ -DBUILD_SHARED_LIBS=OFF -DASSIMP_NO_EXPORT=ON -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_ZLIB=ON -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="x86_64" ~/assimp
cmake ~/assimp/CMakeLists.txt
make -j4 clean all
mkdir -p ~/RajawaliAssimpBridge/app/src/main/cpp/lib/x86_64
cp contrib/zlib/libzlibstatic.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/x86_64/
cp lib/libassimp.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/x86_64
cd

mkdir -p ~/RajawaliAssimpBridge/app/src/main/cpp/include
cp -r ~/assimp/include ~/RajawaliAssimpBridge/app/src/main/cpp
```
