#ifndef __ABSTRACT_FACET_READER_H__
#define __ABSTRACT_FACET_READER_H__

#include "ModelType/Facet.h"

class AbstractFacetReader
{
public:
    AbstractFacetReader() = default;
    virtual ~AbstractFacetReader() = default;

    virtual Facet read_facet() = 0;
    virtual size_t get_count() = 0;
};

#endif // __ABSTRACT_FACET_READER_H__