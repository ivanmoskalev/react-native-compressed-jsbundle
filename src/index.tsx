import { NativeModules } from 'react-native';

type ReactNativeCompressedJsbundleType = {
  multiply(a: number, b: number): Promise<number>;
};

const { ReactNativeCompressedJsbundle } = NativeModules;

export default ReactNativeCompressedJsbundle as ReactNativeCompressedJsbundleType;
