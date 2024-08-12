#ifndef __BUFFER_INL__
#define __BUFFER_INL__

#include <vector>

namespace ControlSystem
{
    struct Buffer
    {
        static int width, height;
        static std::vector<std::vector<float>> original_buffer; // original frame buffer with no depth
        static std::vector<std::vector<float>> depth_buffer;

        static std::vector<std::vector<size_t>> original_frame_buffer; //filled with single color
        static std::vector<std::vector<size_t>> frame_buffer;
    };
}
#endif
