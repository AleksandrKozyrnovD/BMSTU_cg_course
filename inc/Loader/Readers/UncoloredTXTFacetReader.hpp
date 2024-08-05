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
    float x, y, z;
    fscanf(file, "%f %f %f", &x, &y, &z);
    glm::vec3 A(x, y, z);

    fscanf(file, "%f %f %f", &x, &y, &z);
    glm::vec3 B(x, y, z);

    fscanf(file, "%f %f %f", &x, &y, &z);
    glm::vec3 C(x, y, z);

    return Facet(A, B, C);
}

size_t UncoloredTXTFacetReader::get_count()
{
    size_t count;
    fscanf(file, "%zu", &count);

    return count;
}

