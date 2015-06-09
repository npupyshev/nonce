# nonce
A little tool for OS X to lookup nonce and ECID of connected iOS device.
# build
xcrun -sdk macosx clang -arch x86_64 -F/System/Library/PrivateFrameworks -framework CoreFoundation -framework MobileDevice nonce.c -o nonce
