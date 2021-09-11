/**
 * Copyright (c) Ivan Moskalev
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef BrotliUtil_h
#define BrotliUtil_h

#include <brotli/decode.h>

static inline NSData *_Nullable IMOTryDecompressingBrotli(NSData *_Nonnull inputData) {
    size_t available_in = inputData.length;
    const uint8_t *next_in = (const uint8_t *)inputData.bytes;

    const int decompressionBufferSize = 8192;
    uint8_t* decompressedBuffer = (uint8_t*) malloc(decompressionBufferSize * sizeof(uint8_t));
    BOOL usedDecompressedBufferInResult = NO;

    NSMutableData *resultData = nil;

    BrotliDecoderState *s = BrotliDecoderCreateInstance(NULL, NULL, NULL);
    BrotliDecoderResult result = BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT;

    size_t total_out = 0;

    /* Loop while the decoder wants more space to output. */
    while (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT) {
        size_t available_out = decompressionBufferSize;
        uint8_t *next_out = decompressedBuffer;

        result = BrotliDecoderDecompressStream(s, &available_in, &next_in, &available_out, &next_out, &total_out);

        const size_t written = decompressionBufferSize - available_out;

        if (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT || result == BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT) {
            /* Partial result, so accumulate in `resultData` */
            if (resultData == nil) {
                resultData = [NSMutableData dataWithBytes:decompressedBuffer length:written];
            } else {
                [resultData appendBytes:decompressedBuffer length:written];
            }
        } else if (result == BROTLI_DECODER_RESULT_SUCCESS) {
            /* Complete result, so either append to existing buffer or create the final result buffer */
            if (resultData) {
                [resultData appendBytes:decompressedBuffer length:written];
            } else {
                resultData = (NSMutableData*) [NSData dataWithBytesNoCopy:decompressedBuffer length:total_out freeWhenDone:YES];
                usedDecompressedBufferInResult = YES;
            }
        }
    }

    BrotliDecoderDestroyInstance(s);

    if (!usedDecompressedBufferInResult) {
        free(decompressedBuffer);
    }

    if (result == BROTLI_DECODER_RESULT_SUCCESS) {
        return resultData;
    } else {
        return nil;
    }
}



#endif /* BrotliUtil_h */
