#pragma once

#include <memory>
#include <string>
#include <utility>

#include <ABI46_0_0jsi/ABI46_0_0jsi.h>

#include "JsiSkRuntimeEffect.h"
#include "JsiSkHostObjects.h"

namespace ABI46_0_0RNSkia {

using namespace ABI46_0_0facebook;

class JsiSkRuntimeEffectFactory : public JsiSkHostObject {
public:
  JSI_HOST_FUNCTION(Make) {
    auto sksl = arguments[0].asString(runtime).utf8(runtime);
    auto result = SkRuntimeEffect::MakeForShader(SkString(sksl));
    auto effect = result.effect;
    auto errorText = result.errorText;
    if (!effect) {
      jsi::detail::throwJSError(
          runtime,
          std::string("Error in sksl:\n" + std::string(errorText.c_str()))
              .c_str());
      return jsi::Value::null();
    }
    return jsi::Object::createFromHostObject(
        runtime, std::make_shared<JsiSkRuntimeEffect>(getContext(), std::move(effect)));
  }

  JSI_EXPORT_FUNCTIONS(
    JSI_EXPORT_FUNC(JsiSkRuntimeEffectFactory, Make)
  )

  JsiSkRuntimeEffectFactory(std::shared_ptr<ABI46_0_0RNSkPlatformContext> context)
      : JsiSkHostObject(std::move(context)) {}
};

} // namespace ABI46_0_0RNSkia
