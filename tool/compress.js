const brotli = require('brotli');
const fs = require('fs');

const jsBundlePath = process.argv[2];
const jsBundleContent = fs.readFileSync(jsBundlePath);

console.log('[react-native-compressed-jsbundle] Compressing .jsbundle at', jsBundlePath);

fs.writeFileSync(jsBundlePath, brotli.compress(jsBundleContent));

console.log('[react-native-compressed-jsbundle] Wrote compressed bundle to', jsBundlePath);
