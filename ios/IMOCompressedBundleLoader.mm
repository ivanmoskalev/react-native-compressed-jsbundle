#import "IMOCompressedBundleLoader.h"
#import "BrotliUtil.h"
#import "TraceUtil.h"
#import "IMOReactSource.h"

#define FALLBACK_TO_DEFAULT_LOADER()             \
  [RCTJavaScriptLoader loadBundleAtURL:sourceUrl \
      onProgress:onProgress                      \
      onComplete:loadCallback];

@implementation IMOCompressedBundleLoader

+ (void)loadSourceForBridge:(RCTBridge *)bridge
             bridgeDelegate:(id<RCTBridgeDelegate>)delegate
                 onProgress:(RCTSourceLoadProgressBlock)onProgress
                 onComplete:(RCTSourceLoadBlock)loadCallback
{
    NSURL *sourceUrl = [delegate sourceURLForBridge:bridge];
    
    if (!sourceUrl.isFileURL) {
        FALLBACK_TO_DEFAULT_LOADER();
        return;
    }
    
    CFTimeInterval startTime = CACurrentMediaTime();
    
    NSData *compressedData = [[NSData alloc] initWithContentsOfURL:sourceUrl options:NSDataReadingMappedIfSafe error:nil];
    
    if (!compressedData) {
        FALLBACK_TO_DEFAULT_LOADER();
        return;
    }
    
    NSData *decompressedData = IMOTryDecompressingBrotli(compressedData);
    
    if (!decompressedData) {
        FALLBACK_TO_DEFAULT_LOADER();
        return;
    }
    
    IMOTraceDecompressionPerformance(startTime, compressedData.length, decompressedData.length);

    RCTSource *source = [IMOReactSource sourceWithUrl:sourceUrl data:decompressedData];
    loadCallback(nil, source);
}
@end
