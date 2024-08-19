# Linked List of Words from a text file using BRIDGES API

Using the BRIDGES API from the University of North Carolina at Charlotte.

### Purpose: 
This programs reads in files that the user inputs word by word. The program then lowers 
and removes the punctuation from the word and inserts them into a linked list, in 
alphabetical order. The linked lists consists of BRIDGES SLelement. The SLelement includes 
the word that it read in, the number of times the word appears in the text, and the "next" 
pointer that points to either the SLelement or a null pointer. The linked list is in 
alphabetical order and is labeled with the word and the number of times it appears in the 
text.

### Input: 
The user will input a filename that contains the text that will be read. They
will also input two integers, high and low, as a range for the frequency of words repeated
in the text. 

### Output: 
The stats of all the words in the alphabetical order and frequency order. When it prints out 
the stats for alphabetical order, all the words that are only mentioned once will be printed
below the stats table and under "Words with frequency = 1". There will also be a link to the 
BRIDGES visualization of the linked list with each node labeled with its word and frequency. 
