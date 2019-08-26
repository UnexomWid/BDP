<p align="center">
  <img src="img/logo.png" alt="BDP">
</p>

# About
BDP (_Binary Data Package_) is a basic 64 bit packaging format for binary data.

This is a cross-platform C++ implementation of BDP.

# License
BDP was created by [UnexomWid](http://unexomwid.me).

BDP and all pieces of software that interact with BDP are licensed under the [GNU GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html) license.

# Releases

>Note: versions with the suffix **R** are considered stable releases, while those with the suffix **D** are considered unstable.

None.

# BDP
BDP packages store _name-value_ pairs, where the name and the value contain binary data (_i.e. they can contain plain text, files etc_).

The maximum length/size of the names and values is determined by the package _header_.

> BDP is a **64 bit** format (_i.e. the maximum possible length/size of a name/value is **2^64 - 1**_).
>
> However, package names/values can be stored with an **8, 16, 32 or 64 bit** format.
>
> The name/value bit size is specified in the package _header_.

## Magic value
All BDP packages begin with the magic value `BDP`. If this value is missing, the package is marked as invalid.

The magic value is **24 bits** (**3 bytes**) long.

## Header
The header is stored after the magic value, and it is **8 bits** (**1 byte**) long. It contains the _name_ and _value_ **bit sizes**.

The first 4 bits (_nibble_) from right to left determine the _value_ bit size, and the last 4 bits (_nibble_) determine the _name_ bit size. Each nibble contains **exactly** 1 bit equal to `1`.

The bit size is determined based on the position of the bit which is equal to `1`, as follows:

* _Position 0:_ **8 bit** (_max 256_)
* _Position 1:_ **16 bit** (_max 65 536_)
* _Position 2:_ **32 bit** (_max 4 294 967 296_)
* _Position 3:_ **64 bit** (_max 18 446 744 073 709 551 616_)

Depending on the bit sizes, BDP packages can be classified into _16 types_, with the rule `BDP[NBS][VBS]`, where:

* **[NBS]** = _name bit size_
* **[VBS]** = _value bit size_

### Complete table of package types

| Package Type | Name Bit Size | Value Bit Size | Header   |
|--------------|---------------|----------------|----------|
| BDP88        | 8             | 8              | 00010001 |
| BDP816       | 8             | 16             | 00010010 |
| BDP832       | 8             | 32             | 00010100 |
| BDP864       | 8             | 64             | 00011000 |
| BDP168       | 16            | 8              | 00100001 |
| BDP1616      | 16            | 16             | 00100010 |
| BDP1632      | 16            | 32             | 00100100 |
| BDP1664      | 16            | 64             | 00101000 |
| BDP328       | 32            | 8              | 01000008 |
| BDP3216      | 32            | 16             | 01000010 |
| BDP3232      | 32            | 32             | 01000100 |
| BDP3264      | 32            | 64             | 01001000 |
| BDP648       | 64            | 8              | 10000001 |
| BDP6416      | 64            | 16             | 10000010 |
| BDP6432      | 64            | 32             | 10000100 |
| BDP6464      | 64            | 64             | 10001000 |

## Name-Value Pairs

The _name-value_ pairs are stored after the header, or after the previous pair, as follows:

`[name_bytes_length][name_bytes][value_bytes_length][value_bytes]`

The length of the name/value is stored in **exactly** `bitSize / 8` bytes (_e.g. if the name bit size is 16, the length of the name will be stored in **exactly 2 bytes**, even if 1 byte is enough_).

Therefore, the maximum length of a single name/value is `2^bitSize`.

## Example

This is an arbitrary **BDP832** package which contains information about a user (_2 name-value pairs_):

* The full name of the user
* The avatar (_16x16 PNG_) of the user

> Name Bit Size: **8**
>
> Value Bit Size: **32**

<p align="center">
   <img src="img/e832.png" alt="BDP">
</p>