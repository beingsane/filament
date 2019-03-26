/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TNT_FILABRIDGE_SIBGENERATOR_H
#define TNT_FILABRIDGE_SIBGENERATOR_H

#include <private/filament/EngineEnums.h>
#include <backend/DriverEnums.h>

#include <stdint.h>
#include <stddef.h>

namespace filament {

class SamplerInterfaceBlock;

class SibGenerator {
public:
    static SamplerInterfaceBlock const& getPerViewSib() noexcept;
    static SamplerInterfaceBlock const& getPostProcessSib() noexcept;
    static SamplerInterfaceBlock const* getSib(uint8_t bindingPoint) noexcept;
};

struct PerViewSib {
    // indices of each samplers in this SamplerInterfaceBlock (see: getSib())
    static constexpr size_t SHADOW_MAP     = 0;
    static constexpr size_t RECORDS        = 1;
    static constexpr size_t FROXELS        = 2;
    static constexpr size_t IBL_DFG_LUT    = 3;
    static constexpr size_t IBL_SPECULAR   = 4;

    static constexpr size_t SAMPLER_COUNT = 5;
};

struct PostProcessSib {
    // indices of each samplers in this SamplerInterfaceBlock (see: getSib())
    static constexpr size_t COLOR_BUFFER   = 0;

    static constexpr size_t SAMPLER_COUNT = 1;
};

// Returns the binding point of the first sampler for the given backend API.
inline constexpr uint8_t getSamplerBindingsStart(driver::Backend api) noexcept {
    switch (api) {
        default:
        case driver::Backend::VULKAN:
            // The Vulkan backend has single namespace for uniforms and samplers.
            // To avoid collision, the sampler bindings start after the last UBO binding.
            return filament::BindingPoints::COUNT;

        case driver::Backend::OPENGL:
        case driver::Backend::METAL:
            // Metal has a separate namespace for uniforms and samplers- collisions aren't an issue.
            return 0;
    }
}

}
#endif // TNT_FILABRIDGE_SIBGENERATOR_H
