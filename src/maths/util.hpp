#pragma once

#include <stdint.h>

#include <ctime>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

namespace util {
    constexpr inline float EPSILON = 1e-6f;

    class PseudoRandom {
        unsigned short seed;
    public:
        PseudoRandom() {
            seed = static_cast<unsigned short>(time(0));
        }

        int rand() {
            seed = (seed + 0x7ed5 + (seed << 6));
            seed = (seed ^ 0xc23c ^ (seed >> 9));
            seed = (seed + 0x1656 + (seed << 3));
            seed = ((seed + 0xa264) ^ (seed << 4));
            seed = (seed + 0xfd70 - (seed << 3));
            seed = (seed ^ 0xba49 ^ (seed >> 8));

            return static_cast<int>(seed);
        }

        int32_t rand32() {
            return (rand() << 16) | rand();
        }

        uint32_t randU32() {
            return (rand() << 16) | rand();
        }

        int64_t rand64() {
            uint64_t x = randU32();
            uint64_t y = randU32();
            return (x << 32ULL) | y;
        }

        uint64_t randU64() {
            uint64_t x = randU32();
            uint64_t y = randU32();
            return (x << 32ULL) | y;
        }

        float randFloat() {
            return randU32() / static_cast<float>(UINT32_MAX);
        }

        double randDouble() {
            return randU64() / static_cast<double>(UINT64_MAX);
        }

        void setSeed(int number) {
            seed = (static_cast<unsigned short>(number * 23729) ^ 
                    static_cast<unsigned short>(number + 16786));
            rand();
        }
        void setSeed(int number1, int number2) {
            seed = ((static_cast<unsigned short>(number1 * 23729) |
                    static_cast<unsigned short>(number2 % 16786)) ^
                    static_cast<unsigned short>(number2 * number1));
            rand();
        }
    };
    
    /// @brief Find nearest point on segment to given
    /// @param a segment point A
    /// @param b segment point B
    /// @param point given point (may be anywhere)
    /// @return nearest point on the segment to given point 
    inline glm::vec3 closest_point_on_segment(
        glm::vec3 a, glm::vec3 b, const glm::vec3& point
    ) {
        auto vec = b - a;
        float da = glm::distance2(point, a);
        float db = glm::distance2(point, b);
        float len = glm::length2(vec);
        float t = (((da - db) / len) * 0.5f + 0.5f);
        t = std::min(1.0f, std::max(0.0f, t));
        return a + vec * t;
    }
}
