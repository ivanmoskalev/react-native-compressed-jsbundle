/**
 * Copyright (c) Ivan Moskalev
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef TraceHelper_h
#define TraceHelper_h

#import <Foundation/Foundation.h>

#ifdef TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

static inline BOOL IMOIsReleaseBuild() {
#ifdef DEBUG
    return NO;
#else
    return YES;
#endif
}

static inline NSString* IMODeviceInfoString() {
#ifdef TARGET_OS_IPHONE
    UIDevice *device = UIDevice.currentDevice;
    return [NSString stringWithFormat:@"Device OS: %@ %@\nDevice model: %@", device.systemName, device.systemVersion, device.model];
#elif TARGET_OS_SIMULATOR
    return @"Device OS: iOS Simulator";
#else
    return @"Device OS: macOS";
#endif
}

static inline void IMOTraceDecompressionPerformance(CFTimeInterval startTime, NSUInteger compressedSize, NSUInteger originalSize) {
    CFTimeInterval endTime = CACurrentMediaTime();
    NSLog(
          @"[react-native-compressed-jsbundle] Decompression time overhead: %g s\nOriginal size: %g KB\nCompressed size: %g KB\nBackend: brotli\nIs release build: %d\n%@",
          endTime - startTime,
          (double)originalSize / 1024,
          (double)compressedSize/ 1024,
          IMOIsReleaseBuild(),
          IMODeviceInfoString()
          );
}

#endif /* TraceHelper_h */
