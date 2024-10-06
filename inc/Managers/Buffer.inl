#ifndef __BUFFER_INL__
#define __BUFFER_INL__

#include <cstdint>
#include <vector>
#include <stdint.h>

namespace ControlSystem
{
    struct Buffer
    {
        static int width, height;
        static int shadow_res;

        static std::vector<std::vector<float>> original_buffer; // original frame buffer with no depth
        static std::vector<std::vector<float>> depth_buffer;



        static std::vector<std::vector<uint32_t>> original_frame_buffer; //filled with single color
        static std::vector<std::vector<uint32_t>> frame_buffer;

        static std::vector<std::vector<float>> light_depth_buffer;
        static std::vector<std::vector<float>> original_light_depth;
        static std::vector<std::vector<uint32_t>> original_light_frame;
        static std::vector<std::vector<uint32_t>> light_frame_buffer;

        //добавить специальный буффер, который сделает з-буффер нерегулярным

    };
}
#endif
