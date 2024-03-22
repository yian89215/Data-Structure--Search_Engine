# Search Engine using Trie Data Structure

## Overview

This project implements a search engine using the Trie data structure in C++. The search engine provides various functionalities to efficiently search for strings based on different criteria such as suffixes, wildcards, full matches, and prefixes.

## Features

1. **Suffix Search**: Allows users to search for strings with specific suffixes, i.e., strings ending with certain characters.
2. **Wildcard Search**: Implements wildcard search functionality, enabling the use of placeholders in search queries for flexible data retrieval.
3. **Full Search**: Facilitates searching for strings with exact matches.
4. **Prefix Search**: Enables users to search for strings with specific prefixes, i.e., strings starting with certain characters.

## Input and Output

### Input Files

1. `query.txt` or `query_more.txt`: Files containing search queries to be performed on the dataset.
2. Dataset folder: Contains multiple files (`data/` or `data_more/`) serving as the dataset for search operations.

### Output

The search results will be saved to an output file specified during execution.

## Compilation

Compile the program using the following command:

```bash
g++ -std=c++17 filename.cpp -o filename
./filename [input_folder_path] [query_file_path] [output_file_name]  ( ./filename data query.txt output.txt)
