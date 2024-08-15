#ifndef __TXT_FACET_READER_H__
#define __TXT_FACET_READER_H__

#include <string>

#include "AbstractFacetReader.h"

class TXTFacetReader : public AbstractFacetReader
{
public:
    TXTFacetReader() = delete;
    explicit TXTFacetReader(const std::string& filename);
    ~TXTFacetReader();

    Facet read_facet() override;
    size_t get_count() override;

protected:
    FILE *file;
};

#include "TXTFacetReader.hpp"

#endif

