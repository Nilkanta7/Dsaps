Q1.
Seam Carving Image Resizer

This is a C++ implementation of the Seam Carving algorithm using OpenCV using c++. It allows content-aware image resizing by intelligently removing vertical and horizontal seams to reduce the width and height of an image while preserving important features.

# Working-
Energy Computation:
    Computes the energy map of the image using the gradient magnitude (Sobel operator).

Seam Identification:
    Finds vertical or horizontal seams with the lowest cumulative energy using dynamic programming.

Seam Removal:
    Removes the identified seam from the image.
    Can visualize the seam removal in real-time.

    Here we are writting one function that will reduce seam in width. for height seaming , first tranpose the entire matrix then apply seam by width the againg tranpose and save it in final output path

Resize Loop:
    Iteratively removes seams until the target width and height are achieved.


Compiling-
    g++ 2025201031_A1_Q1.cpp -o 2025201031_A1_Q1 `pkg-config --cflags --libs opencv4`


Run-
    ./2025201031_A1_Q1 <input_image> <output_image> <target_width> <target_height>




Q2.
# Trie-based Dictionary (Search, Autocomplete & Autocorrect)

This is a C++ implementation of a Trie (Prefix Tree) with the following features:

1.Word Insertion

2.Exact Word Search

3.Autocomplete (Prefix-based suggestions)

4.Autocorrect (Edit distance–based suggestions)

It can store words, search for them, suggest completions, and even handle misspelled queries with corrections.

for input
10 4
consider
filters
filers
entitled
tilers
litter
dames
filling
grasses
fitter
1 litter
1 dame
2 con
3 filter

Explanation-
10 → number of words to insert into the Trie
4 → number of queries

add thse 10 lettsers in the trie
consider
filters
filers
entitled
tilers
litter
dames
filling
grasses
fitter

now for query 1=searching

We check if "litter" exists in the Trie.
"litter" was inserted, so the result = 1


now for second query 1=searching

We check if "dame" exists in the Trie.
"dame" not exist, so the result = 0


now for third query 2=autocomplete
"consider" starts with "con"
output
1
consider

now for third query 3=autocoorrect with max edit distance = 3 (Levenshtein distance)
Now we compare "filter" with dictionary words. Candidates within edit distance ≤ 3:

"filters" →distance 1 (just an extra "s") 
"filers" →distance 2 (missing "t")
"fitter" → distance 2 (replace "l" with "t") 
output-
3
filters
filers
fitter

Compiling-
    g++ t2025201031_A1_Q2.cpp -o 2025201031_A1_Q2

Run-
    ./2025201031_A1_Q2       then give input in terminal
    or for giving input as ip.txt save the input in ip.txt and run
    ./2025201031_A1_Q2 < ip.txt










Q3.
Custom Map with Range Updates

This is a C++ program that implements a map-like data structure (called maap) using a sorted vector of key-value pairs. It supports efficient lower bound lookup, insertion, erasure, range updates, and queries with binary search.

It behaves somewhat like std::map, but is implemented manually to demonstrate how ordered key-value structures can be built with binary search.

Features

1.Insert / Update Key-Value Pair – Insert a key with value or update if it  already exists.

2.Erase – Remove a key from the structure.

3.Lower Bound (lb) – Find index of the first key greater than or equal to given value.

4.Value Query (valueat) – Get the value at a specific key or the previous smaller key.

5.Range Update – Updates a range [l, r) with a given height h.

6.Print – Print all stored key-value pairs.

for input
8
0 0 5 10
0 2 7 15
0 6 9 18
1
0 2 7 20
1
0 5 15 25
1

8=number of queries

i.0 0 5 10 =>Update range [0, 5) with height 10. map ->{(0,10),(5,0)}

ii.0 2 7 15=>Update range [2, 7) with height 15. map ->{(0,10),(2,15),(7,10)}

iii. 0 6 9 18=>Update range [6, 9) with height 18. map ->{(0,10),(2,15),(6,18),(9,0)}

iv. print the result
    0 10
    2 15
    6 18
    9 0

v.  0 2 7 20=>Update range [2, 7) with height 20. map ->{(0,10),(2,20),(7,18),(9,0)}

vi. print the result
    0 10
    2 20
    6 18
    9 0

 vii.  0 5 15 25=>Update range [5, 15) with height 25. map ->{(0,10),(2,20),(5,25),(15,0)} 

 viii. print the result
    0 10
    2 20
    5 25
    15 0





Compile-
    g++ 2025201031_A1_Q3.cpp -o 2025201031_A1_Q3

Run-
    ./2025201031_A1_Q2


