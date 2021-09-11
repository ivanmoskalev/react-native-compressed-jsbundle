#import <Foundation/Foundation.h>
#import <React/RCTBridge.h>

@interface IMOReactSource : RCTSource {
 @public
  NSURL *_url;
  NSData *_data;
  NSUInteger _length;
  NSInteger _filesChangedCount;
}

+ (instancetype)sourceWithUrl:(NSURL *)url data:(NSData *)data;

@end
