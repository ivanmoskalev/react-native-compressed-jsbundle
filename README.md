# Ship compressed JS bundles

**Warning: not yet available for Android.**

Sometimes you need a very small `.app`, for example if you are building
an [App Clip](https://developer.apple.com/app-clips/). (App Clips have to be strictly less than 10 MB in their _
uncompressed_ form.)

When you distribute your React Native app, JavaScript code gets bundled into a `.jsbundle` file. It can get quite large.

This package allows you to compress your `.jsbundle` when you build the app for distribution. When the app is run, it
automatically uncompresses the `.jsbundle` on the fly.

## How does it work?

`react-native-compressed-jsbundle` provides:

- a script that automatically compresses your `.jsbundle` using the fast and compact Brotli algorithm;
- a custom `.jsbundle` loader that uncompresses the `.jsbundle` (at ~350MB/s) at app launch.

## Installation

### iOS

Add the library a dependency:

```shell
$ yarn add react-native-compressed-jsbundle
```

Open your Xcode project and modify the React Native build phase (“Bundle React Native code and images”):

```(shell)
export NODE_BINARY=node
../node_modules/react-native/packager/react-native-xcode.sh

# :: Add this line below ::
../node_modules/react-native-compressed-jsbundle/tool/compress-xcode.sh 
# :::::::::::::::::::::::::
```

Open `AppDelegate.m` and add the following:

```(objectivec)
// 1. Add the new import directive below other imports.
#import <react-native-compressed-jsbundle/IMOCompressedBundleLoader.h>

@implementation AppDelegate

/// ...snip snip snip...

// 2. Add the following lines below other methods:
- (void)loadSourceForBridge:(RCTBridge *)bridge onProgress:(RCTSourceLoadProgressBlock)onProgress onComplete:(RCTSourceLoadBlock)loadCallback {
  [IMOCompressedBundleLoader loadSourceForBridge:bridge bridgeDelegate:self onProgress:onProgress onComplete:loadCallback];
}

@end
```

You are good to go.

## Performance

This libary does add a bit of time to app startup due to the decompression step. However, it is quite small. I have
included some simple low-overhead tracing in the library, so you can see for yourself whether the tradeoff is
acceptable. Build your app in Release mode on your device and look into the Xcode console.

The `example` project gives a following trace on my iPhone XS:

