#ifndef LEARN_UTILITIES_H
#define LEARN_UTILITIES_H

#include <numbers>
#include <vector>

namespace utilities {

    void create_circle(std::vector<float> &buffer, float x, float y, float radius, int triangles_count = 100) {
        float current_pos = 0;
        float sector = 2 * std::numbers::pi / triangles_count;
        buffer.reserve(triangles_count * 3);

        for (size_t i = 0; i < triangles_count; ++i) {
            buffer.insert(buffer.end(), {x, y,
                                         cos(current_pos) * radius + x, sin(current_pos) * radius + y,
                                         cos(current_pos + sector) * radius + x, sin(current_pos + sector) * radius + y});
            current_pos += sector;
        }
    }

} // namespace utilities

#endif//LEARN_UTILITIES_H
