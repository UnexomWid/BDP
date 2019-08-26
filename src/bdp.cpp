/*
 * BDP - A basic 64 bit packaging format for binary data.
 * Copyright (C) 2019  UnexomWid

 * bdp.h - Contains the declaration of the library.

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "bdp.h"

bdp::Header::Header(uint8_t nlbs, uint8_t vlbs) : NAME_MAX_LENGTH(getMaxLength(nlbs)),
                                                  VALUE_MAX_LENGTH(getMaxLength(vlbs)),
                                                  NAME_LENGTH_BIT_SIZE(nlbs),
                                                  VALUE_LENGTH_BIT_SIZE(vlbs),
                                                  NAME_LENGTH_BYTE_SIZE(nlbs / 8u),
                                                  VALUE_LENGTH_BYTE_SIZE(vlbs / 8u) { }

bdp::Header bdp::writeHeader(std::ostream &output, uint8_t nameLengthBitSize, uint8_t valueLengthBitSize) {
    if (nameLengthBitSize != 8u && nameLengthBitSize != 16u && nameLengthBitSize != 32u && nameLengthBitSize != 64u)
        throw std::invalid_argument("nameLengthBitSize");
    if (valueLengthBitSize != 8u && valueLengthBitSize != 16u && valueLengthBitSize != 32u && valueLengthBitSize != 64u)
        throw std::invalid_argument("valueLengthBitSize");

    uint8_t lengthBitSizes = (((nameLengthBitSize) << 1u) | (valueLengthBitSize >> 3u));

    output.write(MAGIC_VALUE, MAGIC_VALUE_LENGTH);
    output.write((char*) (&lengthBitSizes), 1u);

    return bdp::Header(nameLengthBitSize, valueLengthBitSize);
}

void bdp::writeName(const bdp::Header &header, std::ostream &output, const uint8_t* name, uint64_t nameLength) {
    writeData(header.NAME_MAX_LENGTH, header.NAME_LENGTH_BYTE_SIZE, output, name, nameLength);
}
void bdp::writeName(const bdp::Header &header, std::ostream &output, std::istream &name) {
    writeData(header.NAME_MAX_LENGTH, header.NAME_LENGTH_BYTE_SIZE, output, name, DEFAULT_BUFFER_SIZE);
}
void bdp::writeName(const bdp::Header &header, std::ostream &output, std::istream &name, uint64_t bufferSize) {
    writeData(header.NAME_MAX_LENGTH, header.NAME_LENGTH_BYTE_SIZE, output, name, bufferSize);
}

void bdp::writeValue(const bdp::Header &header, std::ostream &output, const uint8_t* value, uint64_t valueLength) {
    writeData(header.VALUE_MAX_LENGTH, header.VALUE_LENGTH_BYTE_SIZE, output, value, valueLength);
}
void bdp::writeValue(const bdp::Header &header, std::ostream &output, std::istream &value) {
    writeData(header.VALUE_MAX_LENGTH, header.VALUE_LENGTH_BYTE_SIZE, output, value, DEFAULT_BUFFER_SIZE);
}
void bdp::writeValue(const bdp::Header &header, std::ostream &output, std::istream &value, uint64_t bufferSize) {
    writeData(header.VALUE_MAX_LENGTH, header.VALUE_LENGTH_BYTE_SIZE, output, value, bufferSize);
}

void bdp::writePair(const bdp::Header &header, std::ostream &output, const uint8_t* name, uint64_t nameLength, const uint8_t* value, uint64_t valueLength) {
    writeName(header, output, name, nameLength);
    writeValue(header, output, value, valueLength);
}
void bdp::writePair(const bdp::Header &header, std::ostream &output, const uint8_t* name, uint64_t nameLength, std::istream &value) {
    writeName(header, output, name, nameLength);
    writeValue(header, output, value);
}
void bdp::writePair(const bdp::Header &header, std::ostream &output, const uint8_t* name, uint64_t nameLength, std::istream &value, uint64_t bufferSize) {
    writeName(header, output, name, nameLength);
    writeValue(header, output, value, bufferSize);
}
void bdp::writePair(const bdp::Header &header, std::ostream &output, std::istream &name, const uint8_t* value, uint64_t valueLength) {
    writeName(header, output, name);
    writeValue(header, output, value, valueLength);
}
void bdp::writePair(const bdp::Header &header, std::ostream &output, std::istream &name, const uint8_t* value, uint64_t valueLength, uint64_t bufferSize) {
    writeName(header, output, name, bufferSize);
    writeValue(header, output, value, valueLength);
}
void bdp::writePair(const bdp::Header &header, std::ostream &output, std::istream &name, std::istream &value) {
    writeName(header, output, name);
    writeValue(header, output, value);
}
void bdp::writePair(const bdp::Header &header, std::ostream &output, std::istream &name, std::istream &value, uint64_t bufferSize) {
    writeName(header, output, name, bufferSize);
    writeValue(header, output, value, bufferSize);
}

void bdp::writeData(uint64_t maxLength, uint8_t lengthByteSize, std::ostream &output, const uint8_t* data, uint64_t dataLength) {
    uint8_t* dataLengthBytes;
    uintToBytes(dataLength, lengthByteSize, dataLengthBytes);

    output.write((char*) (&dataLengthBytes[0]), lengthByteSize);
    output.write((char*) (&data[0]), dataLength);
}
void bdp::writeData(uint64_t maxLength, uint8_t lengthByteSize, std::ostream &output, std::istream &data, uint64_t bufferSize) {
    uint64_t inputLength = 0u;

    uint8_t* inputLengthBytes;
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

bdp::Header bdp::readHeader(std::istream &input) {
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
            nameLengthBitSize = i == 7u ? 64u :
                                 i == 6u ? 32u :
                                 i == 5u ? 16u :
                                 8u;
            break;
        }
    }
    for(uint8_t i = 3u; i >= 0u; --i) {
        if (lengthBitSizes[0] & (1u << i)) {
            valueLengthBitSize = i == 3u ? 64u :
                                 i == 2u ? 32u :
                                 i == 1u ? 16u :
                                 8u;
            break;
        }
    }

    free(lengthBitSizes);
    free(magic);

    return bdp::Header(nameLengthBitSize, valueLengthBitSize);
}

void bdp::readName(const bdp::Header &header, std::istream &input, uint8_t* &name, uint64_t &nameLength) {
    readData(header.NAME_LENGTH_BYTE_SIZE, input, name, nameLength);
}
void bdp::readName(const bdp::Header &header, std::istream &input, std::ostream &name) {
    readData(header.NAME_LENGTH_BYTE_SIZE, input, name, DEFAULT_BUFFER_SIZE);
}
void bdp::readName(const bdp::Header &header, std::istream &input, std::ostream &name, uint64_t bufferSize) {
    readData(header.NAME_LENGTH_BYTE_SIZE, input, name, bufferSize);
}

void bdp::readValue(const bdp::Header &header, std::istream &input, uint8_t* &value, uint64_t &valueLength) {
    readData(header.VALUE_LENGTH_BYTE_SIZE, input, value, valueLength);
}
void bdp::readValue(const bdp::Header &header, std::istream &input, std::ostream &value) {
    readData(header.VALUE_LENGTH_BYTE_SIZE, input, value, DEFAULT_BUFFER_SIZE);
}
void bdp::readValue(const bdp::Header &header, std::istream &input, std::ostream &value, uint64_t bufferSize) {
    readData(header.VALUE_LENGTH_BYTE_SIZE, input, value, bufferSize);
}

void bdp::readPair(const bdp::Header &header, std::istream &input, uint8_t* &name, uint64_t &nameLength, uint8_t* &value, uint64_t &valueLength) {
    readName(header, input, name, nameLength);
    readValue(header, input, value, valueLength);
}
void bdp::readPair(const bdp::Header &header, std::istream &input, uint8_t* &name, uint64_t &nameLength, std::ostream &value) {
    readName(header, input, name, nameLength);
    readValue(header, input, value);
}
void bdp::readPair(const bdp::Header &header, std::istream &input, uint8_t* &name, uint64_t &nameLength, std::ostream &value, uint64_t bufferSize) {
    readName(header, input, name, nameLength);
    readValue(header, input, value, bufferSize);
}
void bdp::readPair(const bdp::Header &header, std::istream &input, std::ostream &name, uint8_t* &value, uint64_t &valueLength) {
    readName(header, input, name);
    readValue(header, input, value, valueLength);
}
void bdp::readPair(const bdp::Header &header, std::istream &input, std::ostream &name, uint8_t* &value, uint64_t &valueLength, uint64_t bufferSize) {
    readName(header, input, name, bufferSize);
    readValue(header, input, value, valueLength);
}
void bdp::readPair(const bdp::Header &header, std::istream &input, std::ostream &name, std::ostream &value) {
    readName(header, input, name);
    readValue(header, input, value);
}
void bdp::readPair(const bdp::Header &header, std::istream &input, std::ostream &name, std::ostream &value, uint64_t bufferSize) {
    readName(header, input, name, bufferSize);
    readValue(header, input, value, bufferSize);
}

void bdp::readData(uint8_t lengthByteSize, std::istream &input, uint8_t* &output, uint64_t &outputLength) {
    uint8_t* outputLengthBytes = (uint8_t*) malloc(lengthByteSize);
    input.read((char*) &(outputLengthBytes[0]), lengthByteSize);

    outputLength = 0u;
    bytesToUInt(outputLengthBytes, lengthByteSize, outputLength);

    try { free(output); } catch(std::exception &e) { }
    output = (uint8_t*) malloc(outputLength);

    input.read((char*) (&output[0]), outputLength);

    free(outputLengthBytes);
}
void bdp::readData(uint8_t lengthByteSize, std::istream &input, std::ostream &output, uint64_t bufferSize) {
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

uint64_t bdp::getMaxLength(uint8_t lengthBitSize) {
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

void bdp::uintToBytes(uint64_t value, uint8_t byteCount, uint8_t *&destination) {
    free(destination);
    destination = (uint8_t *) malloc(byteCount);
    for (uint8_t i = 0; i < byteCount; ++i)
        destination[i] = (uint8_t) (value >> (8u * (byteCount - i - 1u)));
}

void bdp::bytesToUInt(const uint8_t *bytes, uint8_t byteCount, uint64_t &destination) {
    destination = 0u;
    for (uint8_t i = 0; i < byteCount; ++i)
        destination |= (((uint64_t) bytes[i]) << (8u * (byteCount - i - 1u)));
}