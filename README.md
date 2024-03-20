# Search_Engine

Language: C++
Implement data sturcture: Trie

Goal:

Develop a data structure that contains the following functions, which allows users to search a specific word according to requirements :
1. Suffix Search: Search for strings with specific suffixes. (String ending with certain characters)
2. Wildcard Search: Implemented wildcard search functionality, which permits the use of placeholders in search queries for flexible data retrieval.
3. Full Search: Search for strings with exact matches.
4. Prefix Search: Search for strings with specific prefixes. (String starting with certain characters)


Input file:
1. query.txt
2. query_more.txt

Dataset (data.zip):
1. data (100 files)
2. data_more (1000 files)

command:
g++ -std=c++17 filename.cpp -o filename
.\filename [input_folder_path] [query_file_path] [output_file_name]
For example: .\filename data query.txt output.txt
