#pragma once

namespace Domain::Entities
{
    struct RecordedSample
    {
        uint8_t *raw_data;
        size_t array_len;
        uint32_t sample_rate;
    };
}