#!/bin/bash
set -e
cd /home/forest/pokeemerald-multiplatform
export JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64
export ANDROID_HOME=/home/forest/android-sdk
export ANDROID_SDK_ROOT=/home/forest/android-sdk
export PATH="$JAVA_HOME/bin:$PATH"
java -version 2>&1 | head -1
echo "=== starting Android release build ==="
android/SDL2/android-project/gradlew -p android :app:assembleRelease --console=plain
echo "=== APK output ==="
ls -la android/app/build/outputs/apk/release/