/**
 * Copyright (c) Ivan Moskalev
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef BrotliUtil_h
#define BrotliUtil_h

#include <vector>
#include <brotli/decode.h>

static inline NSData *_Nullable IMOTryDecompressingBrotli(NSData *_Nonnull input) {
    BrotliDecoderState *state = BrotliDecoderCreateInstance(NULL, NULL, NULL);
    
    if (!state) {
        return nil;
    }
    
    std::vector<uint8_t> buffer(input.length);
    
    // Inputs
    size_t availableIn = input.length;
    const uint8_t* nextIn = reinterpret_cast<const uint8_t*>(input.bytes);
    
    // Outputs
    size_t availableOut = buffer.size();
    uint8_t* nextOut = reinterpret_cast<uint8_t*>(buffer.data());

    BrotliDecoderResult result = BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT;
    
    while (result != BROTLI_DECODER_RESULT_SUCCESS && result != BROTLI_DECODER_RESULT_ERROR) {
        result = BrotliDecoderDecompressStream(
            state, &availableIn, &nextIn, &availableOut, &nextOut, nullptr
        );
        if (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT) {
            const size_t actuallyUsedMemory = buffer.size() - availableOut;
            const size_t memoryToAdd = buffer.size();
            availableOut += memoryToAdd;
            buffer.resize(buffer.size() + memoryToAdd);
            nextOut = reinterpret_cast<uint8_t*>(buffer.data()) + actuallyUsedMemory;
        } else if (result == BROTLI_DECODER_RESULT_SUCCESS) {
            const size_t actuallyUsedMemory = buffer.size() - availableOut;
            buffer.resize(actuallyUsedMemory);
            break;
        } else if (result == BROTLI_DECODER_RESULT_ERROR) {
            buffer.clear();
            break;
        }
    }

    BrotliDecoderDestroyInstance(state);

    if (result != BROTLI_DECODER_RESULT_SUCCESS) {
        return nil;
    }
    
    return [NSData dataWithBytes:&buffer[0] length:buffer.size()];
}



#endif /* BrotliUtil_h */
