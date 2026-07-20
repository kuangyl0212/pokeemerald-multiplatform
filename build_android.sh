#!/bin/bash
set -e
cd /mnt/w/workspace/pokeemerald-multiplatform-master
export JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64
export ANDROID_HOME=/mnt/w/AndroidSDK
export ANDROID_SDK_ROOT=/mnt/w/AndroidSDK
export PATH="$JAVA_HOME/bin:$PATH"
java -version
echo "=== starting Android build ==="
android/SDL2/android-project/gradlew -p android :app:assembleDebug
