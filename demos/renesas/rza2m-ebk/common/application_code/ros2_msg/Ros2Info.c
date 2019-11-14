// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file Ros2Info.c
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#include "Ros2Info.h"

#include <ucdr/microcdr.h>
#include <string.h>

bool MultiArrayDimension_serialize_topic(ucdrBuffer* writer, const MultiArrayDimension* topic)
{
    (void) ucdr_serialize_string(writer, topic->label);

    (void) ucdr_serialize_uint32_t(writer, topic->size);

    (void) ucdr_serialize_uint32_t(writer, topic->stride);

    return !writer->error;
}

bool MultiArrayDimension_deserialize_topic(ucdrBuffer* reader, MultiArrayDimension* topic)
{
    (void) ucdr_deserialize_string(reader, topic->label, 255);

    (void) ucdr_deserialize_uint32_t(reader, &topic->size);

    (void) ucdr_deserialize_uint32_t(reader, &topic->stride);

    return !reader->error;
}

uint32_t MultiArrayDimension_size_of_topic(const MultiArrayDimension* topic, uint32_t size)
{
    uint32_t previousSize = size;
    size += ucdr_alignment(size, 4) + 4 + (uint32_t)strlen(topic->label) + 1;

    size += ucdr_alignment(size, 4) + 4;

    size += ucdr_alignment(size, 4) + 4;

    return size - previousSize;
}

bool MultiArrayLayout_serialize_topic(ucdrBuffer* writer, const MultiArrayLayout* topic)
{
    (void) ucdr_serialize_uint32_t(writer, topic->dim_size);
    for(int i = 0; i < topic->dim_size; ++i)
    {
        (void) MultiArrayDimension_serialize_topic(writer, &topic->dim[i]);
    }

    (void) ucdr_serialize_uint32_t(writer, topic->data_offset);

    return !writer->error;
}

bool MultiArrayLayout_deserialize_topic(ucdrBuffer* reader, MultiArrayLayout* topic)
{
    (void) ucdr_deserialize_uint32_t(reader, &topic->dim_size);
    if(topic->dim_size > 1)
    {
        reader->error = true;
    }
    else
    {
        for(int i = 0; i < topic->dim_size; ++i)
        {
            (void) MultiArrayDimension_deserialize_topic(reader, &topic->dim[i]);
        }
    }

    (void) ucdr_deserialize_uint32_t(reader, &topic->data_offset);

    return !reader->error;
}

uint32_t MultiArrayLayout_size_of_topic(const MultiArrayLayout* topic, uint32_t size)
{
    uint32_t previousSize = size;
    size += ucdr_alignment(size, 4) + 4;
    for(int i = 0; i < topic->dim_size; ++i)
    {
        size += MultiArrayDimension_size_of_topic(&topic->dim[i], size);
    }

    size += ucdr_alignment(size, 4) + 4;

    return size - previousSize;
}

bool Ros2Info_serialize_topic(ucdrBuffer* writer, const Ros2Info* topic)
{
    (void) MultiArrayLayout_serialize_topic(writer, &topic->layout);
#ifdef NEVER
    (void) ucdr_serialize_sequence_double(writer, topic->info, topic->info_size);
#else
    (void) ucdr_serialize_uint32_t( writer, topic->info_size );
    *((uint32_t *)writer->iterator) = 0;
    writer->iterator += sizeof(uint32_t);
    ucdr_array_to_buffer( writer, &topic->info[0], sizeof(double) * topic->info_size, sizeof(double) * topic->info_size );
#endif

    return !writer->error;
}

bool Ros2Info_deserialize_topic(ucdrBuffer* reader, Ros2Info* topic)
{
    (void) MultiArrayLayout_deserialize_topic(reader, &topic->layout);
#ifdef NEVER
    (void) ucdr_deserialize_sequence_double(reader, topic->info, 100, &topic->info_size);
#else
    (void) ucdr_deserialize_uint32_t( reader, &topic->info_size );
    reader->iterator += sizeof(uint32_t);
    ucdr_buffer_to_array( reader, topic->info, 100, sizeof(double) * topic->info_size );
#endif

    return !reader->error;
}

uint32_t Ros2Info_size_of_topic(const Ros2Info* topic, uint32_t size)
{
    uint32_t previousSize = size;
    size += MultiArrayLayout_size_of_topic(&topic->layout, size);
    size += ucdr_alignment(size, 4) + 4;
    size += ucdr_alignment(size, 8) + topic->info_size * 8;

    return size - previousSize;
}
