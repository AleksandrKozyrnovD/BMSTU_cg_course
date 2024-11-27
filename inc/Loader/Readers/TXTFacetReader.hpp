#include "TXTFacetReader.h"
#include <utility>
#include <iostream>

TXTFacetReader::TXTFacetReader(const std::string& filename)
{
    file = fopen(filename.c_str(), "r");
    if (!file)
        throw std::exception();
}

TXTFacetReader::~TXTFacetReader()
{
    if (file)
        fclose(file);
}

#include <iostream>
Facet TXTFacetReader::read_facet()
{
    float x, y, z;
    uint32_t color;

    fscanf(file, "%f %f %f", &x, &y, &z);
    glm::vec3 A(x, y, z);

    fscanf(file, "%f %f %f", &x, &y, &z);
    glm::vec3 B(x, y, z);

    fscanf(file, "%f %f %f", &x, &y, &z);
    glm::vec3 C(x, y, z);

    //RGBA8888
    uint8_t r, g, b, a;
    fscanf(file, "%hhu %hhu %hhu %hhu", &r, &g, &b, &a);
    color = (r << 24) | (g << 16) | (b << 8) | a;

    int red = (color & 0xFF00000) >> 24;
    int green = (color & 0x00FF0000) >> 16;
    int blue = (color & 0x0000FF00) >> 8;
    int alpha = color & 0x000000FF;

    return Facet(A, B, C, color);
}

size_t TXTFacetReader::get_count()
{
    size_t count;
    fscanf(file, "%zu", &count);

    return count;
}