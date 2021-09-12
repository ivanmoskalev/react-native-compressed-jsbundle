#import <Foundation/Foundation.h>
#import <React/RCTBridge.h>

@interface IMOReactSource : RCTSource

+ (instancetype)sourceWithUrl:(NSURL *)url data:(NSData *)data;

@end
