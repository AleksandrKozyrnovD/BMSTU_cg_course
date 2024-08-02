#include "UncoloredTXTFacetReader.h"
#include <exception>

UncoloredTXTFacetReader::UncoloredTXTFacetReader(const std::string& filename)
{
    file = fopen(filename.c_str(), "r");
    if (!file)
        throw std::exception();
}

UncoloredTXTFacetReader::~UncoloredTXTFacetReader()
{
    if (file)
        fclose(file);
}

Facet UncoloredTXTFacetReader::read_facet()
{
    float x, y, z, w;
    fscanf(file, "%f %f %f %f", &x, &y, &z, &w);
    Point A(glm::vec4(x, y, z, w));

    fscanf(file, "%f %f %f %f", &x, &y, &z, &w);
    Point B(glm::vec4(x, y, z, w));

    fscanf(file, "%f %f %f %f", &x, &y, &z, &w);
    Point C(glm::vec4(x, y, z, w));

    return Facet(A, B, C);
}

size_t UncoloredTXTFacetReader::get_count()
{
    size_t count;
    fscanf(file, "%zu", &count);

    return count;
}

