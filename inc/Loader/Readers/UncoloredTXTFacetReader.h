#ifndef __UNCOLORED_TXT_FACET_READER_H__
#define __UNCOLORED_TXT_FACET_READER_H__

#include <string>

#include "AbstractFacetReader.h"

class UncoloredTXTFacetReader : public AbstractFacetReader
{
public:
    UncoloredTXTFacetReader() = delete;
    explicit UncoloredTXTFacetReader(const std::string& filename);
    ~UncoloredTXTFacetReader();

    Facet read_facet() override;
    size_t get_count() override;

protected:
    FILE *file;
};

#include "UncoloredTXTFacetReader.hpp"

#endif

