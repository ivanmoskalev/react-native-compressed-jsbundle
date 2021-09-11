#import "IMOReactSource.h"

@implementation IMOReactSource

+ (instancetype)sourceWithUrl:(NSURL *)url data:(NSData *)data {
    IMOReactSource *source = [IMOReactSource new];
    source->_url = url;
    source->_data = data;
    source->_length = data.length;
    source->_filesChangedCount = RCTSourceFilesChangedCountNotBuiltByBundler;
    return source;
}

@end
