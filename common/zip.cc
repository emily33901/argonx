#include <precompiled.hh>

#include "zip.hh"

#include <archive.h>
#include <archive_entry.h>

u8 *Zip::Deflate(u8 *in, size_t startingSize, size_t finalSize) {
    auto buffer  = new unsigned char[finalSize];
    auto archive = archive_read_new();

    auto result = archive_read_support_filter_all(archive); // I don't see deflate so using all
    assert(result == ARCHIVE_OK);

    result = archive_read_support_format_zip(archive);
    assert(result == ARCHIVE_OK);

    result = archive_read_open_memory(archive, in, startingSize);
    assert(result == ARCHIVE_OK);

    archive_entry *entry;
    result = archive_read_next_header(archive, &entry);
    assert(result == ARCHIVE_OK);
    assert(archive_entry_pathname(entry) == std::string("z"));
    assert(archive_entry_size(entry) == finalSize);

    auto length = archive_read_data(archive, buffer, finalSize);
    assert(length == finalSize);

    assert(archive_read_next_header(archive, &entry) == ARCHIVE_EOF);

    result = archive_read_free(archive);
    assert(result == ARCHIVE_OK);

    return buffer;
}