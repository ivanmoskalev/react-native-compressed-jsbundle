require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

Pod::Spec.new do |s|
  s.name         = "react-native-compressed-jsbundle"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.homepage     = package["homepage"]
  s.license      = package["license"]
  s.authors      = package["author"]

  s.platforms    = { :ios => "10.0" }
  s.source       = { :git => "https://github.com/ivanmoskalev/react-native-compressed-jsbundle.git", :tag => "#{s.version}" }

  s.source_files = "ios/**/*.{h,m,mm}", "brotli/c/common/*.{c,h}", "brotli/c/dec/*.{c,h}", "brotli/c/include/**/*.{h}"

  s.pod_target_xcconfig = {
    'HEADER_SEARCH_PATHS' => '$(PODS_TARGET_SRCROOT)/brotli/c/include'
  }

  s.dependency "React-Core"
end
