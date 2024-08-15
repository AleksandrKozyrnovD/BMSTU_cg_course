#include "TXTFacetReader.h"

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

    fscanf(file, "%x", &color);


    return Facet(A, B, C, color);
}

size_t TXTFacetReader::get_count()
{
    size_t count;
    fscanf(file, "%zu", &count);

    return count;
}