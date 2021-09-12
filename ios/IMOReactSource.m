#import "IMOReactSource.h"

@interface IMOReactSource () {
    NSURL *_url;
    NSData *_data;
    NSUInteger _length;
    NSInteger _filesChangedCount;
}

@end

@implementation IMOReactSource

- (NSURL *)url {
    return _url;
}

- (NSData *)data {
    return _data;
}

- (NSUInteger)length {
    return _length;
}

- (NSInteger)filesChangedCount {
    return _filesChangedCount;
}

+ (instancetype)sourceWithUrl:(NSURL *)url data:(NSData *)data {
    IMOReactSource *source = [IMOReactSource new];
    source->_url = url;
    source->_data = data;
    source->_length = data.length;
    source->_filesChangedCount = RCTSourceFilesChangedCountNotBuiltByBundler;
    return source;
}

@end
