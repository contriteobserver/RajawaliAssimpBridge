# RajawaliAssimpBridge
Example Bridge between [Rajawali](https://github.com/Rajawali/Rajawali) and the [Open Asset Import Library (assimp)](https://www.assimp.org)

### Initial crude approach to cross-compiling the Open Asset Import Library
```
rm -rf ~/assimp
git clone https://github.com/assimp/assimp.git
mkdir assimp/contrib/android-cmake/build
cd assimp/contrib/android-cmake/build
cmake -DCMAKE_TOOLCHAIN_FILE=~/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake -DANDROID_PLATFORM=21 -DANDROID_NDK=~/Android/Sdk/ndk-bundle/ -DBUILD_SHARED_LIBS=OFF -DASSIMP_NO_EXPORT=ON -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_ZLIB=ON -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi-v7a with NEON" ~/assimp
cmake ~/assimp/CMakeLists.txt
make -j4
mkdir -p ~/RajawaliAssimpBridge/app/src/main/cpp/lib/armeabi-v7a
cp contrib/zlib/libzlibstatic.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/armeabi-v7a/
cp lib/libassimp.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/armeabi-v7a/

rm -rf ~/assimp
git clone https://github.com/assimp/assimp.git
mkdir assimp/contrib/android-cmake/build
cd assimp/contrib/android-cmake/build
cmake -DCMAKE_TOOLCHAIN_FILE=~/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake -DANDROID_PLATFORM=21 -DANDROID_NDK=~/Android/Sdk/ndk-bundle/ -DBUILD_SHARED_LIBS=OFF -DASSIMP_NO_EXPORT=ON -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_ZLIB=ON -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="arm64-v8a" ~/assimp
cmake ~/assimp/CMakeLists.txt
make -j4
mkdir -p ~/RajawaliAssimpBridge/app/src/main/cpp/lib/arm64-v8a
cp contrib/zlib/libzlibstatic.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/arm64-v8a/
cp lib/libassimp.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/arm64-v8a/

rm -rf ~/assimp
git clone https://github.com/assimp/assimp.git
mkdir assimp/contrib/android-cmake/build
cd assimp/contrib/android-cmake/build
cmake -DCMAKE_TOOLCHAIN_FILE=~/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake -DANDROID_PLATFORM=21 -DANDROID_NDK=~/Android/Sdk/ndk-bundle/ -DBUILD_SHARED_LIBS=OFF -DASSIMP_NO_EXPORT=ON -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_ZLIB=ON -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="x86" ~/assimp
cmake ~/assimp/CMakeLists.txt
make -j4
mkdir -p ~/RajawaliAssimpBridge/app/src/main/cpp/lib/x86
cp contrib/zlib/libzlibstatic.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/x86/
cp lib/libassimp.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/x86/

rm -rf ~/assimp
git clone https://github.com/assimp/assimp.git
mkdir assimp/contrib/android-cmake/build
cd assimp/contrib/android-cmake/build
cmake -DCMAKE_TOOLCHAIN_FILE=~/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake -DANDROID_PLATFORM=21 -DANDROID_NDK=~/Android/Sdk/ndk-bundle/ -DBUILD_SHARED_LIBS=OFF -DASSIMP_NO_EXPORT=ON -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_ZLIB=ON -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="x86_64" ~/assimp
cmake ~/assimp/CMakeLists.txt
make -j4
mkdir -p ~/RajawaliAssimpBridge/app/src/main/cpp/lib/x86_64
cp contrib/zlib/libzlibstatic.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/x86_64/
cp lib/libassimp.a ~/RajawaliAssimpBridge/app/src/main/cpp/lib/x86_64
```
