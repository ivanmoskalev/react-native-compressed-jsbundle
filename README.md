# Ship compressed JS bundles 
[Caution. Work in progress]
Doctors hate him! Reduce your app's size with one simple trick.

## Why?
Sometimes you need a very small `.app`, for example if you are building an [App Clip](https://developer.apple.com/app-clips/). App Clips have to be strictly less than 10 MB in their _uncompressed_ form. 

If you have already optimized image assets and got rid of native executable bloat, chances are, your `.jsbundle` is the largest file you have in your `.app`.

Why not `gzip` it and reduce its size roughly _in half_?

## How?
`react-native-compressed-jsbundle` provides a custom `.jsbundle` loader that decompresses it on the fly and feeds the decompressed data to React Native. This is similar to what browsers do, ungzipping the resources before using them.

## What's the catch?
- You'll need to update the React Native's build script step in Xcode. This library will take care of that.
- Your app startup time will probably take a small hit. (More likely, it will be an unnoticable overhead. But I'm still to measure that properly.)
