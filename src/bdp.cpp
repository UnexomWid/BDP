/**
 * BDP (https://github.com/UnexomWid/BDP)
 *
 * This project is licensed under the MIT license.
 * Copyright (c) 2019 UnexomWid (https://uw.exom.dev)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "bdp.h"

/// The magic BDP value, which is located at the beginning of every BDP package.
const char* MAGIC_VALUE = "BDP";
/// The magic BDP value length.
const uint8_t MAGIC_VALUE_LENGTH = 3u;
/// The default size of the buffer used to copy data from one stream to another.
const uint64_t DEFAULT_BUFFER_SIZE = 16384u;

BDP::Header::Header(uint8_t nlbs, uint8_t vlbs) : NAME_MAX_LENGTH(getMaxLength(nlbs)),
                                                  VALUE_MAX_LENGTH(getMaxLength(vlbs)),
                                                  NAME_LENGTH_BIT_SIZE(nlbs),
                                                  VALUE_LENGTH_BIT_SIZE(vlbs),
                                                  NAME_LENGTH_BYTE_SIZE(nlbs / 8u),
                                                  VALUE_LENGTH_BYTE_SIZE(vlbs / 8u) { }

BDP::Header* BDP::writeHeader(std::ostream &output, uint8_t nameLengthBitSize, uint8_t valueLengthBitSize) {
    if (nameLengthBitSize != 8u && nameLengthBitSize != 16u && nameLengthBitSize != 32u && nameLengthBitSize != 64u)
        throw std::invalid_argument("nameLengthBitSize");
    if (valueLengthBitSize != 8u && valueLengthBitSize != 16u && valueLengthBitSize != 32u && valueLengthBitSize != 64u)
        throw std::invalid_argument("valueLengthBitSize");

    uint8_t lengthBitSizes = (((nameLengthBitSize) << 1u) | (valueLengthBitSize >> 3u));

    output.write(MAGIC_VALUE, MAGIC_VALUE_LENGTH);
    output.write((char*) (&lengthBitSizes), 1u);

    return new BDP::Header(nameLengthBitSize, valueLengthBitSize);
}

BDP::Header* BDP::writeHeader(uint8_t* output, uint8_t nameLengthBitSize, uint8_t valueLengthBitSize) {
    if (nameLengthBitSize != 8u && nameLengthBitSize != 16u && nameLengthBitSize != 32u && nameLengthBitSize != 64u)
        throw std::invalid_argument("nameLengthBitSize");
    if (valueLengthBitSize != 8u && valueLengthBitSize != 16u && valueLengthBitSize != 32u && valueLengthBitSize != 64u)
        throw std::invalid_argument("valueLengthBitSize");

    uint8_t lengthBitSizes = (((nameLengthBitSize) << 1u) | (valueLengthBitSize >> 3u));

    memcpy(output, MAGIC_VALUE, MAGIC_VALUE_LENGTH);
    memcpy(output + MAGIC_VALUE_LENGTH, &lengthBitSizes, 1u);

    return new BDP::Header(nameLengthBitSize, valueLengthBitSize);
}

void BDP::writeName(const BDP::Header &header, std::ostream &output, const uint8_t* name, uint64_t nameLength) {
    writeData(header.NAME_MAX_LENGTH, header.NAME_LENGTH_BYTE_SIZE, output, name, nameLength);
}
void BDP::writeName(const BDP::Header &header, uint8_t* output, const uint8_t* name, uint64_t nameLength) {
    writeData(header.NAME_MAX_LENGTH, header.NAME_LENGTH_BYTE_SIZE, output, name, nameLength);
}
void BDP::writeName(const BDP::Header &header, std::ostream &output, std::istream &name) {
    writeData(header.NAME_MAX_LENGTH, header.NAME_LENGTH_BYTE_SIZE, output, name, DEFAULT_BUFFER_SIZE);
}
void BDP::writeName(const BDP::Header &header, std::ostream &output, std::istream &name, uint64_t bufferSize) {
    writeData(header.NAME_MAX_LENGTH, header.NAME_LENGTH_BYTE_SIZE, output, name, bufferSize);
}
void BDP::writeName(const BDP::Header &header, uint8_t* output, std::istream &name) {
    writeData(header.NAME_MAX_LENGTH, header.NAME_LENGTH_BYTE_SIZE, output, name, DEFAULT_BUFFER_SIZE);
}
void BDP::writeName(const BDP::Header &header, uint8_t* output, std::istream &name, uint64_t bufferSize) {
    writeData(header.NAME_MAX_LENGTH, header.NAME_LENGTH_BYTE_SIZE, output, name, bufferSize);
}

void BDP::writeValue(const BDP::Header &header, std::ostream &output, const uint8_t* value, uint64_t valueLength) {
    writeData(header.VALUE_MAX_LENGTH, header.VALUE_LENGTH_BYTE_SIZE, output, value, valueLength);
}
void BDP::writeValue(const BDP::Header &header, uint8_t* output, const uint8_t* value, uint64_t valueLength) {
    writeData(header.VALUE_MAX_LENGTH, header.VALUE_LENGTH_BYTE_SIZE, output, value, valueLength);
}
void BDP::writeValue(const BDP::Header &header, std::ostream &output, std::istream &value) {
    writeData(header.VALUE_MAX_LENGTH, header.VALUE_LENGTH_BYTE_SIZE, output, value, DEFAULT_BUFFER_SIZE);
}
void BDP::writeValue(const BDP::Header &header, std::ostream &output, std::istream &value, uint64_t bufferSize) {
    writeData(header.VALUE_MAX_LENGTH, header.VALUE_LENGTH_BYTE_SIZE, output, value, bufferSize);
}
void BDP::writeValue(const BDP::Header &header, uint8_t* output, std::istream &value) {
    writeData(header.VALUE_MAX_LENGTH, header.VALUE_LENGTH_BYTE_SIZE, output, value, DEFAULT_BUFFER_SIZE);
}
void BDP::writeValue(const BDP::Header &header, uint8_t* output, std::istream &value, uint64_t bufferSize) {
    writeData(header.VALUE_MAX_LENGTH, header.VALUE_LENGTH_BYTE_SIZE, output, value, bufferSize);
}

void BDP::writePair(const BDP::Header &header, std::ostream &output, const uint8_t* name, uint64_t nameLength, const uint8_t* value, uint64_t valueLength) {
    writeName(header, output, name, nameLength);
    writeValue(header, output, value, valueLength);
}
void BDP::writePair(const BDP::Header &header, uint8_t* output, const uint8_t* name, uint64_t nameLength, const uint8_t* value, uint64_t valueLength) {
    writeName(header, output, name, nameLength);
    writeValue(header, output, value, valueLength);
}
void BDP::writePair(const BDP::Header &header, std::ostream &output, const uint8_t* name, uint64_t nameLength, std::istream &value) {
    writeName(header, output, name, nameLength);
    writeValue(header, output, value);
}
void BDP::writePair(const BDP::Header &header, uint8_t* output, const uint8_t* name, uint64_t nameLength, std::istream &value) {
    writeName(header, output, name, nameLength);
    writeValue(header, output, value);
}
void BDP::writePair(const BDP::Header &header, std::ostream &output, const uint8_t* name, uint64_t nameLength, std::istream &value, uint64_t bufferSize) {
    writeName(header, output, name, nameLength);
    writeValue(header, output, value, bufferSize);
}
void BDP::writePair(const BDP::Header &header, uint8_t* output, const uint8_t* name, uint64_t nameLength, std::istream &value, uint64_t bufferSize) {
    writeName(header, output, name, nameLength);
    writeValue(header, output, value, bufferSize);
}
void BDP::writePair(const BDP::Header &header, std::ostream &output, std::istream &name, const uint8_t* value, uint64_t valueLength) {
    writeName(header, output, name);
    writeValue(header, output, value, valueLength);
}
void BDP::writePair(const BDP::Header &header, uint8_t* output, std::istream &name, const uint8_t* value, uint64_t valueLength) {
    writeName(header, output, name);
    writeValue(header, output, value, valueLength);
}
void BDP::writePair(const BDP::Header &header, std::ostream &output, std::istream &name, const uint8_t* value, uint64_t valueLength, uint64_t bufferSize) {
    writeName(header, output, name, bufferSize);
    writeValue(header, output, value, valueLength);
}
void BDP::writePair(const BDP::Header &header, uint8_t* output, std::istream &name, const uint8_t* value, uint64_t valueLength, uint64_t bufferSize) {
    writeName(header, output, name, bufferSize);
    writeValue(header, output, value, valueLength);
}
void BDP::writePair(const BDP::Header &header, std::ostream &output, std::istream &name, std::istream &value) {
    writeName(header, output, name);
    writeValue(header, output, value);
}
void BDP::writePair(const BDP::Header &header, uint8_t* output, std::istream &name, std::istream &value) {
    writeName(header, output, name);
    writeValue(header, output, value);
}
void BDP::writePair(const BDP::Header &header, std::ostream &output, std::istream &name, std::istream &value, uint64_t bufferSize) {
    writeName(header, output, name, bufferSize);
    writeValue(header, output, value, bufferSize);
}
void BDP::writePair(const BDP::Header &header, uint8_t* output, std::istream &name, std::istream &value, uint64_t bufferSize) {
    writeName(header, output, name, bufferSize);
    writeValue(header, output, value, bufferSize);
}

void BDP::writeData(uint64_t maxLength, uint8_t lengthByteSize, std::ostream &output, const uint8_t* data, uint64_t dataLength) {
    uint8_t* dataLengthBytes = (uint8_t*) malloc(lengthByteSize);
    uintToBytes(dataLength, lengthByteSize, dataLengthBytes);

    output.write((char*) (&dataLengthBytes[0]), lengthByteSize);
    output.write((char*) (&data[0]), dataLength);
}
void BDP::writeData(uint64_t maxLength, uint8_t lengthByteSize, uint8_t* output, const uint8_t* data, uint64_t dataLength) {
    uint8_t* dataLengthBytes = (uint8_t*) malloc(lengthByteSize);
    uintToBytes(dataLength, lengthByteSize, dataLengthBytes);

    memcpy(output, dataLengthBytes, lengthByteSize);
    memcpy(output + lengthByteSize, data, dataLength);
}
void BDP::writeData(uint64_t maxLength, uint8_t lengthByteSize, std::ostream &output, std::istream &data, uint64_t bufferSize) {
    uint64_t inputLength = 0u;

    uint8_t* inputLengthBytes = (uint8_t*) malloc(lengthByteSize);
    uintToBytes(inputLength, lengthByteSize, inputLengthBytes);

    std::streampos lastPos = output.tellp();

    // Write a placeholder value, as the actual length is unknown yet.
    output.write((char*) (&inputLengthBytes[0]), lengthByteSize);

    char* buffer = (char*) malloc(bufferSize);
    uint64_t diff;
    uint64_t nextLength;

    while((diff = maxLength - inputLength) != 0u && !data.eof()) {
        nextLength = diff < bufferSize ? diff : bufferSize;
        data.read(buffer, nextLength);
        output.write(buffer, data.gcount());
        inputLength += data.gcount();
    }

    free(buffer);

    std::streampos endPos = output.tellp();
    output.seekp(lastPos);

    // Write the actual length.
    uintToBytes(inputLength, lengthByteSize, inputLengthBytes);
    output.write((char*) (&inputLengthBytes[0]), lengthByteSize);

    output.seekp(endPos);
}
void BDP::writeData(uint64_t maxLength, uint8_t lengthByteSize, uint8_t* output, std::istream &data, uint64_t bufferSize) {
    uint64_t inputLength = 0u;

    uint8_t* inputLengthBytes = (uint8_t*) malloc(lengthByteSize);
    uintToBytes(inputLength, lengthByteSize, inputLengthBytes);

    uint64_t index = 0;

    // Write a placeholder value, as the actual length is unknown yet.
    memcpy(output, inputLengthBytes, lengthByteSize);

    index += lengthByteSize;

    uint64_t diff;
    uint64_t nextLength;

    while((diff = maxLength - inputLength) != 0u && !data.eof()) {
        nextLength = diff < bufferSize ? diff : bufferSize;
        data.read((char*) (output + index), nextLength);

        index += data.gcount();
        inputLength += data.gcount();
    }

    // Write the actual length.
    uintToBytes(inputLength, lengthByteSize, inputLengthBytes);
    memcpy(output, inputLengthBytes, lengthByteSize);
}

BDP::Header* BDP::readHeader(std::istream &input) {
    char* magic = (char*) malloc(MAGIC_VALUE_LENGTH + 1u);
    input.read(magic, MAGIC_VALUE_LENGTH);

    magic[MAGIC_VALUE_LENGTH] = '\0';

    if(strcmp(magic, MAGIC_VALUE) != 0)
        throw std::invalid_argument("input");

    uint8_t nameLengthBitSize = 8u;
    uint8_t valueLengthBitSize = 32u;

    uint8_t *lengthBitSizes = (uint8_t*) malloc(1u);
    input.read((char*) (&lengthBitSizes[0]), 1u);

    for(uint8_t i = 7u; i >= 4u; --i) {
        if(lengthBitSizes[0] & (1u << i)) {
            if(i == 7u)
                nameLengthBitSize = 64u;
            else if(i == 6u)
                nameLengthBitSize = 32u;
            else if(i == 5u)
                nameLengthBitSize = 16u;
            else nameLengthBitSize = 8u;

            break;
        }
    }
    for(uint8_t i = 3u; i >= 0u; --i) {
        if (lengthBitSizes[0] & (1u << i)) {
            if(i == 3u)
                valueLengthBitSize = 64u;
            else if(i == 2u)
                valueLengthBitSize = 32u;
            else if(i == 1u)
                valueLengthBitSize = 16u;
            else valueLengthBitSize = 8u;

            break;
        }
    }

    free(lengthBitSizes);
    free(magic);

    return new BDP::Header(nameLengthBitSize, valueLengthBitSize);
}
BDP::Header* BDP::readHeader(uint8_t* input) {
    uint64_t index = 0;

    char* magic = (char*) malloc(MAGIC_VALUE_LENGTH + 1u);
    memcpy(magic, input, MAGIC_VALUE_LENGTH);

    index += MAGIC_VALUE_LENGTH;
    magic[MAGIC_VALUE_LENGTH] = '\0';

    if(strcmp(magic, MAGIC_VALUE) != 0)
        throw std::invalid_argument("input");

    uint8_t nameLengthBitSize = 8u;
    uint8_t valueLengthBitSize = 32u;

    uint8_t *lengthBitSizes = (uint8_t*) malloc(1u);
    memcpy(lengthBitSizes, input + index, 1);
    ++index;

    for(uint8_t i = 7u; i >= 4u; --i) {
        if(lengthBitSizes[0] & (1u << i)) {
            if(i == 7u)
                nameLengthBitSize = 64u;
            else if(i == 6u)
                nameLengthBitSize = 32u;
            else if(i == 5u)
                nameLengthBitSize = 16u;
            else nameLengthBitSize = 8u;
            break;
        }
    }
    for(uint8_t i = 3u; i >= 0u; --i) {
        if (lengthBitSizes[0] & (1u << i)) {
            if(i == 3u)
                valueLengthBitSize = 64u;
            else if(i == 2u)
                valueLengthBitSize = 32u;
            else if(i == 1u)
                valueLengthBitSize = 16u;
            else valueLengthBitSize = 8u;
            break;
        }
    }

    free(lengthBitSizes);
    free(magic);

    return new BDP::Header(nameLengthBitSize, valueLengthBitSize);
}

void BDP::readName(const BDP::Header &header, std::istream &input, uint8_t* &name, uint64_t &nameLength) {
    readData(header.NAME_LENGTH_BYTE_SIZE, input, name, nameLength);
}
void BDP::readName(const BDP::Header &header, uint8_t* input, uint8_t* &name, uint64_t &nameLength) {
    readData(header.NAME_LENGTH_BYTE_SIZE, input, name, nameLength);
}
void BDP::readName(const BDP::Header &header, std::istream &input, std::ostream &name) {
    readData(header.NAME_LENGTH_BYTE_SIZE, input, name, DEFAULT_BUFFER_SIZE);
}
void BDP::readName(const BDP::Header &header, std::istream &input, std::ostream &name, uint64_t bufferSize) {
    readData(header.NAME_LENGTH_BYTE_SIZE, input, name, bufferSize);
}
void BDP::readName(const BDP::Header &header, uint8_t* input, std::ostream &name, uint64_t &nameLength) {
    readData(header.NAME_LENGTH_BYTE_SIZE, input, name, nameLength);
}

void BDP::readValue(const BDP::Header &header, std::istream &input, uint8_t* &value, uint64_t &valueLength) {
    readData(header.VALUE_LENGTH_BYTE_SIZE, input, value, valueLength);
}
void BDP::readValue(const BDP::Header &header, uint8_t* input, uint8_t* &value, uint64_t &valueLength) {
    readData(header.VALUE_LENGTH_BYTE_SIZE, input, value, valueLength);
}
void BDP::readValue(const BDP::Header &header, std::istream &input, std::ostream &value) {
    readData(header.VALUE_LENGTH_BYTE_SIZE, input, value, DEFAULT_BUFFER_SIZE);
}
void BDP::readValue(const BDP::Header &header, std::istream &input, std::ostream &value, uint64_t bufferSize) {
    readData(header.VALUE_LENGTH_BYTE_SIZE, input, value, bufferSize);
}
void BDP::readValue(const BDP::Header &header, uint8_t* input, std::ostream &value, uint64_t &valueLength) {
    readData(header.VALUE_LENGTH_BYTE_SIZE, input, value, valueLength);
}

void BDP::readPair(const BDP::Header &header, std::istream &input, uint8_t* &name, uint64_t &nameLength, uint8_t* &value, uint64_t &valueLength) {
    readName(header, input, name, nameLength);
    readValue(header, input, value, valueLength);
}
void BDP::readPair(const BDP::Header &header, uint8_t* input, uint8_t* &name, uint64_t &nameLength, uint8_t* &value, uint64_t &valueLength) {
    readName(header, input, name, nameLength);
    readValue(header, input, value, valueLength);
}
void BDP::readPair(const BDP::Header &header, std::istream &input, uint8_t* &name, uint64_t &nameLength, std::ostream &value) {
    readName(header, input, name, nameLength);
    readValue(header, input, value);
}
void BDP::readPair(const BDP::Header &header, uint8_t* input, uint8_t* &name, uint64_t &nameLength, std::ostream &value, uint64_t &valueLength) {
    readName(header, input, name, nameLength);
    readValue(header, input, value, valueLength);
}
void BDP::readPair(const BDP::Header &header, std::istream &input, uint8_t* &name, uint64_t &nameLength, std::ostream &value, uint64_t bufferSize) {
    readName(header, input, name, nameLength);
    readValue(header, input, value, bufferSize);
}
void BDP::readPair(const BDP::Header &header, std::istream &input, std::ostream &name, uint8_t* &value, uint64_t &valueLength) {
    readName(header, input, name);
    readValue(header, input, value, valueLength);
}
void BDP::readPair(const BDP::Header &header, uint8_t* input, std::ostream &name, uint64_t &nameLength, uint8_t* &value, uint64_t &valueLength) {
    readName(header, input, name, nameLength);
    readValue(header, input, value, valueLength);
}
void BDP::readPair(const BDP::Header &header, std::istream &input, std::ostream &name, uint8_t* &value, uint64_t &valueLength, uint64_t bufferSize) {
    readName(header, input, name, bufferSize);
    readValue(header, input, value, valueLength);
}
void BDP::readPair(const BDP::Header &header, std::istream &input, std::ostream &name, std::ostream &value) {
    readName(header, input, name);
    readValue(header, input, value);
}
void BDP::readPair(const BDP::Header &header, uint8_t* input, std::ostream &name, uint64_t &nameLength, std::ostream &value, uint64_t &valueLength) {
    readName(header, input, name, nameLength);
    readValue(header, input, value, valueLength);
}
void BDP::readPair(const BDP::Header &header, std::istream &input, std::ostream &name, std::ostream &value, uint64_t bufferSize) {
    readName(header, input, name, bufferSize);
    readValue(header, input, value, bufferSize);
}

void BDP::readData(uint8_t lengthByteSize, std::istream &input, uint8_t* &output, uint64_t &outputLength) {
    uint8_t* outputLengthBytes = (uint8_t*) malloc(lengthByteSize);
    input.read((char*) &(outputLengthBytes[0]), lengthByteSize);

    outputLength = 0u;
    bytesToUInt(outputLengthBytes, lengthByteSize, outputLength);

    input.read((char*) (&output[0]), outputLength);

    free(outputLengthBytes);
}
void BDP::readData(uint8_t lengthByteSize, uint8_t* input, uint8_t* &output, uint64_t &outputLength) {
    uint8_t* outputLengthBytes = (uint8_t*) malloc(lengthByteSize);
    memcpy(outputLengthBytes, input, lengthByteSize);

    outputLength = 0u;
    bytesToUInt(outputLengthBytes, lengthByteSize, outputLength);

    memcpy(output, input + lengthByteSize, outputLength);

    free(outputLengthBytes);
}
void BDP::readData(uint8_t lengthByteSize, std::istream &input, std::ostream &output, uint64_t bufferSize) {
    uint8_t* outputLengthBytes = (uint8_t*) malloc(lengthByteSize);
    input.read((char*) &(outputLengthBytes[0]), lengthByteSize);

    uint64_t outputLength = 0u;
    bytesToUInt(outputLengthBytes, lengthByteSize, outputLength);

    char* buffer = (char*) malloc(bufferSize);
    uint64_t nextLength;

    while(outputLength > 0u && !input.eof()) {
        nextLength = outputLength < bufferSize ? outputLength : bufferSize;
        input.read(buffer, nextLength);
        output.write(buffer, input.gcount());
        outputLength -= input.gcount();
    }

    free(buffer);
}
void BDP::readData(uint8_t lengthByteSize, uint8_t* input, std::ostream &output, uint64_t &outputLength) {
    uint8_t* outputLengthBytes = (uint8_t*) malloc(lengthByteSize);
    memcpy(outputLengthBytes, input, lengthByteSize);

    outputLength = 0u;
    bytesToUInt(outputLengthBytes, lengthByteSize, outputLength);

    output.write((char*) (input + lengthByteSize), outputLength);
}

uint64_t BDP::getMaxLength(uint8_t lengthBitSize) {
    if(lengthBitSize == 8u)
        return (uint8_t) - 1;
    if(lengthBitSize == 16u)
        return (uint16_t) - 1;
    if(lengthBitSize == 32u)
        return (uint32_t) - 1;
    if(lengthBitSize == 64u)
        return (uint64_t) - 1;

    throw std::invalid_argument("lengthBitSize");
}

void BDP::uintToBytes(uint64_t value, uint8_t byteCount, uint8_t *&destination) {
    for (uint8_t i = 0; i < byteCount; ++i)
        destination[i] = (uint8_t) (value >> (8u * (byteCount - i - 1u)));
}

void BDP::bytesToUInt(const uint8_t *bytes, uint8_t byteCount, uint64_t &destination) {
    destination = 0u;
    for (uint8_t i = 0; i < byteCount; ++i)
        destination |= (((uint64_t) bytes[i]) << (8u * (byteCount - i - 1u)));
}