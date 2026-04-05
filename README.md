# MP3 Tag Reader and Editor in C

## Overview

This project implements a **MP3 Tag Reader and Editor** in the C programming language.
It reads and modifies metadata stored in MP3 files using the **ID3v2.3 tag format**.

The program allows users to view and edit information such as song title, artist name, album name, and year.

---

## Features

* Read MP3 metadata tags
* Display song information
* Edit ID3v2 tags
* Menu-driven interface
* Efficient file handling in C

---

## Technologies Used

* C Programming
* File Handling
* Structures
* String Manipulation

---

## Project Structure

```
MP3-Tag-Reader-C
├── main.c
├── read_tag.c
├── edit_tag.c
├── tag.h
├── Makefile
└── README.md
```

---

## How to Compile

Use the following command:

```
gcc main.c read_tag.c edit_tag.c -o mp3_tag_reader
```

---

## How to Run

```
./mp3_tag_reader sample.mp3
```

---

## Example Output

```
MP3 TAG INFORMATION
Title  : Example Song
Artist : Example Artist
Album  : Example Album
Year   : 2023
```

---

## Future Improvements

* Support for more ID3 frames
* Better user interface
* Error handling improvements

---

## Author

Shriram Vishwanath Pai
