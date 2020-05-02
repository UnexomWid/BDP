# Documentation

This is the official documentation for the [C++17 BDP implementation](https://github.com/UnexomWid/BDP).

# Namespace

All of the functions and structures are inside the `BDP` namespace.

# Header

A structure which contains package information (e.g. the name length bit size).

## Constructor

```cpp
Header(uint8_t nlbs, uint8_t vlbs)
```

Initializes a new instance of the Header structure.

##### Params

- **nlbs** - the name length bit size, which determines the maximum name length. Must be `8`, `16`, `32` or `64`.
- **vlbs** - the value length bit size, which determines the maximum value length. Must be `8`, `16`, `32` or `64`.

##### Remarks

- if either **nlbs** or **vlbs** is `64`, but the library is not compiled for a 64-bit system, a `std::runtime_error` will be thrown

## Fields

```cpp
const size_t NAME_MAX_LENGTH;
const size_t VALUE_MAX_LENGTH;

const uint8_t NAME_LENGTH_BIT_SIZE;
const uint8_t VALUE_LENGTH_BIT_SIZE;

const uint8_t NAME_LENGTH_BYTE_SIZE;
const uint8_t VALUE_LENGTH_BYTE_SIZE;
```

- **NAME_MAX_LENGTH** - the maximum length that names stored in this package can have: `2 ^ NAME_LENGTH_BIT_SIZE - 1`

- **VALUE_MAX_LENGTH** - the maximum length that values stored in this package can have: `2 ^ VALUE_LENGTH_BIT_SIZE - 1`

- **NAME_LENGTH_BIT_SIZE** - the name length bit size, which determines the maximum name length

- **VALUE_LENGTH_BIT_SIZE** - the value length bit size, which determines the maximum value length

- **NAME_LENGTH_BYTE_SIZE** - the name length byte size: `NAME_LENGTH_BIT_SIZE / 8`

- **VALUE_LENGTH_BYTE_SIZE** - the value length bit size: `VALUE_LENGTH_BIT_SIZE / 8`

# Reading Data

Reading operations are done using the functions listed below.

## readHeader

```cpp
Header* readHeader(std::istream &input);
```

Reads a package header from a stream.

##### Params

- **input** - the stream from which to read the header

##### Returns

A pointer to the package header.

##### Remarks

 - this function reads a package header from the stream and returns a pointer to it
 
 - the header is required for reading data from the package
 
 ---
 
 ```cpp
Header* readHeader(const uint8_t* input)
```

Reads a package header from a byte array.

##### Params

- **input** - the byte array from which to read the header

##### Returns

A pointer to the package header

##### Remarks

 - this function reads a package header from the byte array and returns a pointer to it
 
 - the header is required for reading data from the package
 
## readName

```cpp
size_t readName(const Header* header,
                std::istream& input,
                uint8_t* name,
                size_t* nameLength)
```

Reads a name from an input stream and writes it to a byte array.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the name
- **name** - the byte array where to write the name. Must be large enough to contain the name
- **nameLength** - the memory location where to write the name length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the name length bytes.

##### Remarks

- the input should be a `BDP` package

- after reading the name, a value should be read, in order for the package to be read as intended

---

```cpp
size_t readName(const Header* header,
                const uint8_t* input,
                uint8_t* name,
                size_t* nameLength)
```

Reads a name from a byte array and writes it to another byte array.

##### Params

- **header** - a pointer to the package header
- **input** - the byte array from which to read the name
- **name** - the byte array where to write the name. Must be large enough to contain the name
- **nameLength** - the memory location where to write the name length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the name length bytes.

##### Remarks

- the input should be a `BDP` package

- after reading the name, a value should be read, in order for the package to be read as intended

---

```cpp
size_t readName(const Header* header,
                std::istream& input,
                std::ofstream& name,
                size_t* nameLength)
```

Reads a name from an input stream and writes it to another stream.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the name
- **name** - the stream where to write the name

##### Returns

How many bytes were read from the input, including the name length bytes.

##### Remarks

- the default buffer size will be used to copy data between the streams (`16384`)

- the input should be a `BDP` package

- after reading the name, a value should be read, in order for the package to be read as intended

---

```cpp
size_t readName(const Header* header,
                std::istream& input,
                std::ofstream& name,
                size_t* nameLength,
                size_t bufferSize)
```

Reads a name from an input stream and writes it to another stream, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the name
- **name** - the stream where to write the name
- **bufferSize** - the size of the buffer used to copy data between the streams

##### Returns

How many bytes were read from the input, including the name length bytes.

##### Remarks

- the specified buffer size will be used to copy data between the streams

- the input should be a `BDP` package

- after reading the name, a value should be read, in order for the package to be read as intended

---

```cpp
size_t readName(const Header* header,
                const uint8_t* input,
                std::ofstream& name,
                size_t* nameLength)
```

Reads a name from a byte array and writes it to a stream.

##### Params

- **header** - a pointer to the package header
- **input** - the byte array from which to read the name
- **name** - the stream where to write the name
- **nameLength** - the memory location where to write the name length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the name length bytes.

##### Remarks

- the input should be a `BDP` package

- after reading the name, a value should be read, in order for the package to be read as intended

## readValue

```cpp
size_t readValue(const Header* header,
                 std::istream& input,
                 uint8_t* value,
                 size_t* valueLength)
```

Reads a value from an input stream and writes it to a byte array.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the value
- **value** - the byte array where to write the value. Must be large enough to contain the value
- **valueLength** - the memory location where to write the value length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the value length bytes.

##### Remarks

- the input should be a `BDP` package

---

```cpp
size_t readValue(const Header* header,
                 const uint8_t* input,
                 uint8_t* value,
                 size_t* valueLength)
```

Reads a value from a byte array and writes it to another byte array.

##### Params

- **header** - a pointer to the package header
- **input** - the byte array from which to read the value
- **value** - the byte array where to write the value. Must be large enough to contain the value
- **valueLength** - the memory location where to write the value length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the value length bytes.

##### Remarks

- the input should be a `BDP` package

---

```cpp
size_t readValue(const Header* header,
                 std::istream& input,
                 std::ofstream& name,
                 size_t* nameLength)
```

Reads a value from an input stream and writes it to another stream.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the value
- **value** - the stream where to write the value

##### Returns

How many bytes were read from the input, including the value length bytes.

##### Remarks

- the default buffer size will be used to copy data between the streams (`16384`)

- the input should be a `BDP` package

---

```cpp
size_t readValue(const Header* header,
                 std::istream& input,
                 std::ofstream& value,
                 size_t* valueLength,
                 size_t bufferSize)
```

Reads a value from an input stream and writes it to another stream, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the value
- **value** - the stream where to write the value
- **bufferSize** - the size of the buffer used to copy data between the streams

##### Returns

How many bytes were read from the input, including the value length bytes.

##### Remarks

- the specified buffer size will be used to copy data between the streams

- the input should be a `BDP` package

---

```cpp
size_t readValue(const Header* header,
                 const uint8_t* input,
                 std::ofstream& value,
                 size_t* valueLength)
```

Reads a value from a byte array and writes it to a stream.

##### Params

- **header** - a pointer to the package header
- **input** - the byte array from which to read the value
- **value** - the stream where to write the value
- **valueLength** - the memory location where to write the value length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the value length bytes.

##### Remarks

- the input should be a `BDP` package

## readPair

```cpp
size_t readPair(const Header* header,
                std::istream& input,
                uint8_t* name,
                size_t* nameLength,
                uint8_t* value,
                size_t* valueLength)
```

Reads a name and a value from an input stream and writes them to a pair of byte arrays.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the pair
- **name** - the byte array where to write the name. Must be large enough to contain the name
- **nameLength** - the memory location where to write the name length. Can be `nullptr`
- **value** - the byte array where to write the value. Must be large enough to contain the value
- **valueLength** - the memory location where to write the value length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the name and value length bytes.

##### Remarks

- the input should be a `BDP` package

---

```cpp
size_t readPair(const Header* header,
                const uint8_t* input,
                uint8_t* name,
                size_t* nameLength,
                uint8_t* value,
                size_t* valueLength)
```

Reads a name and a value from a byte array and writes them to a pair of byte arrays.

##### Params

- **header** - a pointer to the package header
- **input** - the byte array from which to read the pair
- **name** - the byte array where to write the name. Must be large enough to contain the name
- **nameLength** - the memory location where to write the name length. Can be `nullptr`
- **value** - the byte array where to write the value. Must be large enough to contain the value
- **valueLength** - the memory location where to write the value length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the name and value length bytes.

##### Remarks

- the input should be a `BDP` package

---

```cpp
size_t readPair(const Header* header,
                std::istream& input,
                uint8_t* name,
                size_t* nameLength,
                std::ostream& value)
```

Reads a name and a value from an input stream and writes them to a pair of a byte array and a stream.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the pair
- **name** - the byte array where to write the name. Must be large enough to contain the name
- **nameLength** - the memory location where to write the name length. Can be `nullptr`
- **value** - the stream where to write the value

##### Returns

How many bytes were read from the input, including the name and value length bytes.

##### Remarks

- the default buffer size will be used to copy data between streams (`16384`)

- the input should be a `BDP` package

---

```cpp
size_t readPair(const Header* header,
                const uint8_t* input,
                uint8_t* name,
                size_t* nameLength,
                std::ostream& value,
                size_t* valueLength)
```

Reads a name and a value from a byte array and writes them to a pair of a byte array and a stream.

##### Params

- **header** - a pointer to the package header
- **input** - the byte array from which to read the pair
- **name** - the byte array where to write the name. Must be large enough to contain the name
- **nameLength** - the memory location where to write the name length. Can be `nullptr`
- **value** - the stream where to write the value
- **valueLength** - the memory location where to write the value length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the name and value length bytes.

##### Remarks

- the default buffer size will be used to copy data between streams (`16384`)

- the input should be a `BDP` package

---

```cpp
size_t readPair(const Header* header,
                std::istream &input,
                uint8_t* name,
                size_t* nameLength,
                std::ostream& value,
                size_t bufferSize)
```

Reads a name and a value from an input stream and writes them to a pair of a byte array and a stream, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the pair
- **name** - the byte array where to write the name. Must be large enough to contain the name
- **nameLength** - the memory location where to write the name length. Can be `nullptr`
- **value** - the stream where to write the value
- **bufferSize** - the size of the buffer used to copy the stream data

##### Returns

How many bytes were read from the input, including the name and value length bytes.

##### Remarks

- the specified buffer size will be used to copy data between streams

- the input should be a `BDP` package

---

```cpp
size_t readPair(const Header* header,
                std::istream& input,
                std::ostream& name,
                uint8_t* value,
                size_t* valueLength)
```

Reads a name and a value from an input stream and writes them to a pair of a stream and a byte array.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the pair
- **name** - the stream where to write the name
- **value** - the byte array where to write the value. Must be large enough to contain the value
- **valueLength** - the memory location where to write the value length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the name and value length bytes.

##### Remarks

- the default buffer size will be used to copy data between streams (`16384`)

- the input should be a `BDP` package

---

```cpp
size_t readPair(const Header* header,
                const uint8_t* input,
                std::ostream& name,
                size_t* nameLength,
                uint8_t* value,
                size_t* valueLength)
```

Reads a name and a value from a byte array and writes them to a pair of a stream and a byte array.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the pair
- **name** - the stream where to write the name
- **valueLength** - the memory location where to write the name length. Can be `nullptr`
- **value** - the byte array where to write the value. Must be large enough to contain the value
- **valueLength** - the memory location where to write the value length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the name and value length bytes.

##### Remarks

- the default buffer size will be used to copy data between streams (`16384`)

- the input should be a `BDP` package

---

```cpp
size_t readPair(const Header* header,
                std::istream& input,
                std::ostream& name,
                uint8_t* value,
                size_t* valueLength,
                size_t bufferSize)
```

Reads a name and a value from an input stream and writes them to a pair of a stream and a byte array, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the pair
- **name** - the stream where to write the name
- **value** - the byte array where to write the value. Must be large enough to contain the value
- **valueLength** - the memory location where to write the value length. Can be `nullptr`
- **bufferSize** - the size of the buffer used to copy data between the streams

##### Returns

How many bytes were read from the input, including the name and value length bytes.

##### Remarks

- the specified buffer size will be used to copy data between streams

- the input should be a `BDP` package

---

```cpp
size_t readPair(const Header* header,
                std::istream& input,
                std::ostream& name,
                std::ostream& value)
```

Reads a name and a value from an input stream and writes them to a pair of streams.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the pair
- **name** - the stream where to write the name
- **value** - the stream where to write the value

##### Returns

How many bytes were read from the input, including the name and value length bytes.

##### Remarks

- the default buffer size will be used to copy data between streams (`16384`)

- the input should be a `BDP` package

---

```cpp
size_t readPair(const Header* header,
                const uint8_t* input,
                std::ostream& name,
                size_t* nameLength,
                std::ostream& value,
                size_t* valueLength)
```

Reads a name and a value from a byte array and writes them to a pair of streams.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the pair
- **name** - the stream where to write the name
- **nameLength** - the memory location where to write the name length. Can be `nullptr`
- **value** - the stream where to write the value
- **valueLength** - the memory location where to write the value length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the name and value length bytes.

##### Remarks

- the default buffer size will be used to copy data between streams (`16384`)

- the input should be a `BDP` package

---

```cpp
size_t readPair(const Header* header,
                std::istream& input,
                std::ostream& name,
                std::ostream& value,
                size_t bufferSize)
```

Reads a name and a value from an input stream and writes them to a pair of streams, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **input** - the stream from which to read the pair
- **name** - the stream where to write the name
- **value** - the stream where to write the value
- **bufferSize** - the size of the buffer used to copy data between the streams

##### Returns

How many bytes were read from the input, including the name and value length bytes.

##### Remarks

- the specified buffer size will be used to copy data between streams

- the input should be a `BDP` package

## readData

This function is used by `readName`, `readValue` and `readPair`, which are wrappers.

You shouldn't use this function directly unless you know what you're doing.

Use `readName`, `readValue` and `readPair` instead.

```cpp
size_t readData(uint8_t lengthByteSize,
                std::istream& input,
                uint8_t*& output,
                size_t* outputLength)
```

Reads data from an input stream and writes it to a byte array.

##### Params

- **lengthByteSize** - the data length byte size
- **input** - the stream from which to read the data
- **output** - the byte array where to write the data. Must be large enough to contain the data
- **outputLength** - the memory location where to write the data length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the data length bytes.

##### Remarks

- the length byte size should be `1`, `2`, `4` or `8`.

---

```cpp
size_t readData(uint8_t lengthByteSize,
                const uint8_t* input,
                uint8_t*& output,
                size_t* outputLength)
```

Reads data from a byte array and writes it to a byte array.

##### Params

- **lengthByteSize** - the data length byte size
- **input** - the byte array from which to read the data
- **output** - the byte array where to write the data. Must be large enough to contain the data
- **outputLength** - the memory location where to write the data length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the data length bytes.

##### Remarks

- the length byte size should be `1`, `2`, `4` or `8`.

---

```cpp
size_t readData(uint8_t lengthByteSize,
                std::istream& input,
                std::ostream& output,
                size_t bufferSize)
```

Reads data from an input stream and writes it to another stream, using a specified buffer size.

##### Params

- **lengthByteSize** - the data length byte size
- **input** - the stream from which to read the data
- **output** - the stream where to write the data
- **bufferSize** - the size of the buffer used to copy data between the streams

##### Returns

How many bytes were read from the input, including the data length bytes.

##### Remarks

- the length byte size should be `1`, `2`, `4` or `8`.

---

```cpp
size_t readData(uint8_t lengthByteSize,
                const uint8_t* input,
                std::ostream& output,
                size_t* outputLength)
```

Reads data from a byte array and writes it to a stream, using a specified buffer size.

##### Params

- **lengthByteSize** - the data length byte size
- **input** - the byte array from which to read the data
- **output** - the stream where to write the data
- **outputLength** - the memory location where to write the data length. Can be `nullptr`

##### Returns

How many bytes were read from the input, including the data length bytes.

##### Remarks

- the length byte size should be `1`, `2`, `4` or `8`.

# Writing Data

Writing operations are done using the functions listed below.

## writeHeader

```cpp
Header* writeHeader(std::ostream& output,
                    uint8_t nameLengthBitSize,
                    uint8_t valueLengthBitSize)
```

Generates and writes a package header to a stream.

##### Params

- **output** - the stream where to write the header
- **nameLengthBitSize** - the package name length bit size
- **valueLengthBitSize** - the package value length bit size

##### Returns

A pointer to the generated package header.

##### Remarks

- the header is required for writing data to the package

---

```cpp
Header* writeHeader(uint8_t* output,
                    uint8_t nameLengthBitSize,
                    uint8_t valueLengthBitSize)
```

Generates and writes a package header to a byte array.

##### Params

- **output** - the byte array where to write the header
- **nameLengthBitSize** - the package name length bit size
- **valueLengthBitSize** - the package value length bit size

##### Returns

A pointer to the generated package header.

##### Remarks

- the header is required for writing data to the package

## writeName

```cpp
size_t writeName(const Header* header,
                 std::ostream& output,
                 const uint8_t* name,
                 size_t nameLength)
```

Writes a byte array representing a name to an output stream.

##### Params

- **header** - a pointer to the package header
- **output** - the stream where to write the header
- **name** - the byte array containing the name
- **nameLength** - the length of the byte array containing the name

##### Returns

How many bytes were written to the output, including the name length bytes.

##### Remarks

- after writing the name, a value should be written

---

```cpp
size_t writeName(const Header* header,
                 uint8_t* output,
                 const uint8_t* name,
                 size_t nameLength)
```

Writes a byte array representing a name to another byte array.

##### Params

- **header** - a pointer to the package header
- **output** - the byte array where to write the name. Must be large enough to contain the name and name length
- **name** - the byte array containing the name
- **nameLength** - the length of the byte array containing the name

##### Returns

How many bytes were written to the output, including the name length bytes.

##### Remarks

- after writing the name, a value should be written

---

```cpp
size_t writeName(const Header* header,
                 std::ostream& output,
                 std::istream& name)
```

Writes a stream representing a name to another stream.

##### Params

- **header** - a pointer to the package header
- **output** - the stream where to write the name
- **name** - the stream containing the name

##### Returns

How many bytes were written to the output, including the name length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum name length is reached

- the default buffer size will be used to copy data between the streams (`16384`)

- after writing the name, a value should be written

---

```cpp
size_t writeName(const Header* header,
                 std::ostream& output,
                 std::istream& name,
                 size_t bufferSize)
```

Writes a stream representing a name to another stream, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **output** - the stream where to write the name
- **name** - the stream containing the name
- **bufferSize** - the size of the buffer used to copy data between the streams

##### Returns

How many bytes were written to the output, including the name length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum name length is reached

- the specified buffer size will be used to copy data between the streams

- after writing the name, a value should be written

---

```cpp
size_t writeName(const Header* header,
                 uint8_t* output,
                 std::istream& name)
```

Writes a stream representing a name to a byte array.

##### Params

- **header** - a pointer to the package header
- **output** - the byte array where to write the name. Must be large enough to contain the name and name length
- **name** - the stream containing the name

##### Returns

How many bytes were written to the output, including the name length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum name length is reached

- the default buffer size will be used (`16382`)

- after writing the name, a value should be written

---

```cpp
size_t writeName(const Header* header,
                 uint8_t* output,
                 std::istream& name,
                 size_t bufferSize)
```

Writes a stream representing a name to a byte array, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **output** - the byte array where to write the name. Must be large enough to contain the name and name length
- **name** - the stream containing the name
- **bufferSize** - the size of the buffer

##### Returns

How many bytes were written to the output, including the name length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum name length is reached

- the specified buffer size will be used

- after writing the name, a value should be written

## writeValue

```cpp
size_t writeValue(const Header* header,
                  std::ostream& output,
                  const uint8_t* value,
                  size_t valueLength)
```

Writes a byte array representing a value to an output stream.

##### Params

- **header** - a pointer to the package header
- **output** - the stream where to write the header
- **value** - the byte array containing the value
- **valueLength** - the length of the byte array containing the value

##### Returns

How many bytes were written to the output, including the value length bytes.

---

```cpp
size_t writeValue(const Header* header,
                  uint8_t* output,
                  const uint8_t* value,
                  size_t valueLength)
```

Writes a byte array representing a value to another byte array.

##### Params

- **header** - a pointer to the package header
- **output** - the byte array where to write the value. Must be large enough to contain the value and value length
- **value** - the byte array containing the value
- **valueLength** - the length of the byte array containing the value

##### Returns

How many bytes were written to the output, including the value length bytes.

---

```cpp
size_t writeValue(const Header* header,
                  std::ostream& output,
                  std::istream& value)
```

Writes a stream representing a value to another stream.

##### Params

- **header** - a pointer to the package header
- **output** - the stream where to write the value
- **value** - the stream containing the value

##### Returns

How many bytes were written to the output, including the value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the default buffer size will be used to copy data between the streams (`16384`)

---

```cpp
size_t writeValue(const Header* header,
                  std::ostream& output,
                  std::istream& value,
                  size_t bufferSize)
```

Writes a stream representing a value to another stream, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **output** - the stream where to write the value
- **value** - the stream containing the value
- **bufferSize** - the size of the buffer used to copy data between the streams

##### Returns

How many bytes were written to the output, including the value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the specified buffer size will be used to copy data between the streams

---

```cpp
size_t writeValue(const Header* header,
                  uint8_t* output,
                  std::istream& value)
```

Writes a stream representing a value to a byte array.

##### Params

- **header** - a pointer to the package header
- **output** - the byte array where to write the value. Must be large enough to contain the value and value length
- **value** - the stream containing the value

##### Returns

How many bytes were written to the output, including the value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the default buffer size will be used (`16382`)

---

```cpp
size_t writeValue(const Header* header,
                  uint8_t* output,
                  std::istream& value,
                  size_t bufferSize)
```

Writes a stream representing a value to a byte array, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **output** - the byte array where to write the value. Must be large enough to contain the value and value length
- **value** - the stream containing the value
- **bufferSize** - the size of the buffer

##### Returns

How many bytes were written to the output, including the value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the specified buffer size will be used

## writePair

```cpp
size_t writePair(const Header* header,
                 std::ostream& output,
                 const uint8_t* name,
                 size_t nameLength,
                 const uint8_t* value,
                 size_t valueLength)
```

Writes a pair of a byte array representing a name, and a byte array representing a value, to a stream.

##### Params

- **header** - a pointer to the package header
- **output** - the stream where to write the pair
- **name** - the byte array containing the value
- **nameLength** - the length of the byte array containing the name
- **value** - the byte array containing the value
- **valueLength** - the length of the byte array containing the value

##### Returns

How many bytes were written to the output, including the name and value length bytes.

---

```cpp
size_t writePair(const Header* header,
                 uint8_t* output,
                 const uint8_t* name,
                 size_t nameLength,
                 const uint8_t* value,
                 size_t valueLength)
```

Writes a pair of a byte array representing a name, and a byte array representing a value, to another byte array.

##### Params

- **header** - a pointer to the package header
- **output** - the byte array where to write the pair. Must be large enough to contain the name, name length, value and value length
- **name** - the byte array containing the value
- **nameLength** - the length of the byte array containing the name
- **value** - the byte array containing the value
- **valueLength** - the length of the byte array containing the value

##### Returns

How many bytes were written to the output, including the name and value length bytes.

---

```cpp
size_t writePair(const Header* header,
                 std::ostream& output,
                 const uint8_t* name,
                 size_t nameLength,
                 std::istream& value)
```

Writes a pair of a byte array representing a name, and a stream representing a value, to another stream.

##### Params

- **header** - a pointer to the package header
- **output** - the stream where to write the pair
- **name** - the byte array containing the value
- **nameLength** - the length of the byte array containing the name
- **value** - the stream containing the value

##### Returns

How many bytes were written to the output, including the name and value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the default buffer size will be used to copy data between the streams (`16384`)

---

```cpp
size_t writePair(const Header* header,
                 uint8_t* output,
                 const uint8_t* name,
                 size_t nameLength,
                 std::istream& value)
```

Writes a pair of a byte array representing a name, and a stream representing a value, to another byte array.

##### Params

- **header** - a pointer to the package header
- **output** - the byte array where to write the pair. Must be large enough to contain the name, name length, value and value length
- **name** - the byte array containing the value
- **nameLength** - the length of the byte array containing the name
- **value** - the stream containing the value

##### Returns

How many bytes were written to the output, including the name and value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the default buffer size will be used (`16384`)

---

```cpp
size_t writePair(const Header* header,
                 std::ostream& output,
                 const uint8_t* name,
                 size_t nameLength,
                 std::istream& value,
                 size_t bufferSize)
```

Writes a pair of a byte array representing a name, and a stream representing a value, to another stream, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **output** - the stream where to write the pair
- **name** - the byte array containing the value
- **nameLength** - the length of the byte array containing the name
- **value** - the stream containing the value
- **bufferSize** - the size of the buffer used to copy data between the streams

##### Returns

How many bytes were written to the output, including the name and value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the specified buffer size will be used to copy data between the streams

---

```cpp
size_t writePair(const Header* header,
                 uint8_t* output,
                 const uint8_t* name,
                 size_t nameLength,
                 std::istream& value,
                 size_t bufferSize)
```

Writes a pair of a byte array representing a name, and a stream representing a value, to another byte array, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **output** - the byte array where to write the pair. Must be large enough to contain the name, name length, value and value length
- **name** - the byte array containing the value
- **nameLength** - the length of the byte array containing the name
- **value** - the stream containing the value
- **bufferSize** - the size of the buffer used to copy data between the streams

##### Returns

How many bytes were written to the output, including the name and value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the specified buffer size will be used to copy data between the streams

---

```cpp
size_t writePair(const Header* header,
                 std::ostream& output,
                 std::istream& name,
                 const uint8_t* value,
                 size_t valueLength)
```

Writes a pair of a stream representing a name, and a byte array representing a value, to another stream.

##### Params

- **header** - a pointer to the package header
- **output** - the stream where to write the pair
- **name** - the stream containing the value
- **value** - the byte array containing the value
- **valueLength** - the length of the byte array containing the value

##### Returns

How many bytes were written to the output, including the name and value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the default buffer size will be used to copy data between the streams (`16384`)

---

```cpp
size_t writePair(const Header* header,
                 uint8_t* output,
                 std::istream& name,
                 const uint8_t* value,
                 size_t valueLength)
```

Writes a pair of a stream representing a name, and a byte array representing a value, to another byte array.

##### Params

- **header** - a pointer to the package header
- **output** - the byte array where to write the pair. Must be large enough to contain the value and value length
- **name** - the stream containing the value
- **value** - the byte array containing the value
- **valueLength** - the length of the byte array containing the value

##### Returns

How many bytes were written to the output, including the name and value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the default buffer size will be used (`16384`)

---

```cpp
size_t writePair(const Header* header,
                 std::ostream& output,
                 std::istream& name,
                 const uint8_t* value,
                 size_t valueLength,
                 size_t bufferSize)
```

Writes a pair of a stream representing a name, and a byte array representing a value, to another stream, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **output** - the stream where to write the pair
- **name** - the stream containing the value
- **value** - the byte array containing the value
- **valueLength** - the length of the byte array containing the value
- **bufferSize** - the size of the buffer used to copy data between the streams

##### Returns

How many bytes were written to the output, including the name and value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the specified buffer size will be used to copy data between the stream

---

```cpp
size_t writePair(const Header* header,
                 uint8_t* output,
                 std::istream& name,
                 const uint8_t* value,
                 size_t valueLength,
                 size_t bufferSize)
```

Writes a pair of a stream representing a name, and a byte array representing a value, to another byte array, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **output** - the byte array where to write the pair. Must be large enough to contain the value and value length
- **name** - the stream containing the value
- **value** - the byte array containing the value
- **valueLength** - the length of the byte array containing the value
- **bufferSize** - the size of the buffer

##### Returns

How many bytes were written to the output, including the name and value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the specified buffer size will be used

---

```cpp
size_t writePair(const Header* header,
                 std::ostream& output,
                 std::istream& name,
                 std::istream& value)
```

Writes a pair of a stream representing a name, and a stream representing a value, to another stream.

##### Params

- **header** - a pointer to the package header
- **output** - the stream where to write the pair
- **name** - the stream containing the value
- **value** - the stream containing the value

##### Returns

How many bytes were written to the output, including the name and value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the default buffer size will be used to copy data between the streams (`16384`)

---

```cpp
size_t writePair(const Header* header,
                 uint8_t* output,
                 std::istream& name,
                 std::istream& value)
```

Writes a pair of a stream representing a name, and a stream representing a value, to a byte array.

##### Params

- **header** - a pointer to the package header
- **output** - the byte array where to write the pair. Must be large enough to contain the value and value length
- **name** - the stream containing the value
- **value** - the stream containing the value

##### Returns

How many bytes were written to the output, including the name and value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the default buffer size will be used (`16384`)

---

```cpp
size_t writePair(const Header* header,
                 std::ostream& output,
                 std::istream& name,
                 std::istream& value,
                 size_t bufferSize)
```

Writes a pair of a stream representing a name, and a stream representing a value, to another stream, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **output** - the stream where to write the pair
- **name** - the stream containing the value
- **value** - the stream containing the value
- **bufferSize** - the size of the buffer used to copy data between the streams

##### Returns

How many bytes were written to the output, including the name and value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the specified buffer size will be used to copy data between the streams

---

```cpp
size_t writePair(const Header* header,
                 uint8_t* output,
                 std::istream& name,
                 std::istream& value,
                 size_t bufferSize)
```

Writes a pair of a stream representing a name, and a stream representing a value, to a byte array, using a specified buffer size.

##### Params

- **header** - a pointer to the package header
- **output** - the byte array where to write the pair. Must be large enough to contain the value and value length
- **name** - the stream containing the value
- **value** - the stream containing the value
- **bufferSize** - the size of the buffer

##### Returns

How many bytes were written to the output, including the name and value length bytes.

##### Remarks

- the function will read from the input stream until either `EOF` or the maximum value length is reached

- the specified buffer size will be use

## writeData

This function is used by `writeName`, `writeValue` and `writePair`, which are wrappers.

You shouldn't use this function directly unless you know what you're doing.

Use `writeName`, `writeValue` and `writePair` instead.

```cpp
size_t writeData(size_t maxLength,
                 uint8_t lengthByteSize,
                 std::ostream& output,
                 const uint8_t* data,
                 size_t dataLength)
```

Writes a byte array representing data to a stream.

##### Params

- **maxLength** - the maximum data length
- **lengthByteSize** - the data length byte size
- **output** - the stream where to write the data
- **data** - the byte array containing the data
- **dataLength** - the length of the byte array containing the data

##### Returns

How many bytes were written to the output, including the data length bytes.

##### Remarks

- the length byte size should be `1`, `2`, `4` or `8`.

---

```cpp
size_t writeData(size_t maxLength,
                 uint8_t lengthByteSize,
                 uint8_t* output,
                 const uint8_t *data,
                 size_t dataLength)
```

Writes a byte array representing data to another byte array.

##### Params

- **maxLength** - the maximum data length
- **lengthByteSize** - the data length byte size
- **output** - the byte array where to write the data. Must be large enough to contain the data
- **data** - the byte array containing the data
- **dataLength** - the length of the byte array containing the data

##### Returns

How many bytes were written to the output, including the data length bytes.

##### Remarks

- the length byte size should be `1`, `2`, `4` or `8`.

---

```cpp
size_t writeData(size_t maxLength,
                 uint8_t lengthByteSize,
                 std::ostream& output,
                 std::istream& data,
                 size_t bufferSize)
```

Writes a stream representing data to another stream, using a specified buffer size.

##### Params

- **maxLength** - the maximum data length
- **lengthByteSize** - the data length byte size
- **output** - the stream where to write the data
- **data** - the stream containing the data
- **bufferSize** - the size of the buffer used to copy data between the streams

##### Returns

How many bytes were written to the output, including the data length bytes.

##### Remarks

- the specified buffer size will be used to copy data between the streams

- the length byte size should be `1`, `2`, `4` or `8`.

---

```cpp
size_t writeData(size_t maxLength,
                 uint8_t lengthByteSize,
                 uint8_t* output,
                 std::istream& data,
                 size_t bufferSize)
```

Writes a stream representing data to a byte array, using a specified buffer size.

##### Params

- **maxLength** - the maximum data length
- **lengthByteSize** - the data length byte size
- **output** - the byte array where to write the data. Must be large enough to contain the value and value length
- **data** - the stream containing the data
- **bufferSize** - the size of the buffer

##### Returns

How many bytes were written to the output, including the data length bytes.

##### Remarks

- the specified buffer size will be used

- the length byte size should be `1`, `2`, `4` or `8`.