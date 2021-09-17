/**
 * Copyright (c) Ivan Moskalev
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <XCTest/XCTest.h>

@interface Smoketests : XCTestCase

@end

@implementation Smoketests

- (void)setUp {
  self.continueAfterFailure = NO;
}

- (void)tearDown {
}

- (void)testExampleAppLaunchesAndJsBundleIsValid {
  // UI tests must launch the application that they test.
  XCUIApplication *app = [[XCUIApplication alloc] init];
  [app launch];
  XCTAssertNotNil(app.staticTexts[@"Hello from @ivanmoskalev/react-native-compressed-bundle! Json object contains 10000 elements."]);
}

@end
