const brotli = require('brotli');
const fs = require('fs');
const path = require('path');

try {
    const jsBundlePath = path.join(process.env.CONFIGURATION_BUILD_DIR, process.env.UNLOCALIZED_RESOURCES_FOLDER_PATH, 'main.jsbundle');
    const jsBundleContent = fs.readFileSync(jsBundlePath);
    console.log('[react-native-compressed-jsbundle] Compressing .jsbundle at', jsBundlePath);
    fs.writeFileSync(jsBundlePath, brotli.compress(jsBundleContent));
    console.log('[react-native-compressed-jsbundle] Wrote compressed bundle to', jsBundlePath);
} catch (error) {
    console.log('[react-native-compressed-jsbundle] Failed to compress jsbundle!', error);
}
