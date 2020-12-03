
 <!--
 *** To avoid retyping too much info. Do a search and replace for the following:
 *** donnerhanson, Page Replacement Algorithms
, donnerhanson, hanso127@mail.chapman.edu
 -->





 <!-- PROJECT SHIELDS -->
 <!--
 *** I'm using markdown "reference style" links for readability.
 *** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
 *** See the bottom of this document for the declaration of the reference variables
 *** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
 *** https://www.markdownguide.org/basic-syntax/#reference-style-links
 -->

 [![LinkedIn][linkedin-shield]][linkedin-url]



 <!-- PROJECT LOGO -->
 <br />

   <h3 align="center">Page Replacement Algorithms</h3>

   <p align="center">
    A Simulation Demonstrating Virtual Memory Paging Algorithms in an OS
     <br />
   </p>
 </p>



 <!-- TABLE OF CONTENTS -->
 ## Table of Contents

 * [About the Program](#about-the-program)
 * [Getting Started](#getting-started)
   * [Prerequisites](#prerequisites)
   * [Installation](#installation)
 * [Usage](#usage)
 * [Example](#example)
 * [Contact](#contact)



 <!-- ABOUT THE PROGRAM -->
 ## About The Program

 This program Simulates Virtual Memory Page Swapping Algorithms.  
 The user passes a number string as an argument to the program at the command line that determines the Page numbers hit or miss (Page Fault) in succession.
 The algorithms used to simulate page swaps are: First in First Out, Least Recently Used, and Optimal.  

The program will exit if an incorrectly formatted string is passed, or if non-digit numeric values  
less than 0 or greater than 9 are passed.

 <!-- GETTING STARTED -->
 ## Getting Started

 To get a local copy up and running follow these simple steps.  

 ### Prerequisites  
 * Machine Requirements:   
 ```sh  
 GCC, the GNU compiler  
 C++ language  
 Tested on Windows 10 and Mac OS Mojave  
 ```  

 ### Installation  

 1. Clone the repo  
 ```sh  
 git clone https://github.com/donnerhanson/Page-Replacement-Algorithms  
 ```  
 2. Compilation  
 Navigate to the location of the cloned program Page Replacement Algorithms
 directory.  

compile using the command  

 ```sh   
 g++ -std=c++98 -Wall -Wextra -g vmmpr.cpp -o vmmpr;  
 ```

 <!-- USAGE EXAMPLES -->
 ## Usage

 1. After completing the installation and compilation instructions, start the program within the Page Replacement Algorithms directory by running the command in a bash shell.   

 ```sh  
   ./vmmpr 1, 2, 3, 4, 5, 3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2  
 ```  

To run and save the output  

 ```sh  
  ./vmmpr 1, 2, 3, 4, 5, 3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2 > output.txt  
 ```  

 ## Example  

 <!--1. Example: [text to display](pdf or filename here)  -->

```sh  
User Input String: 1,2,3,4,5,3,4,1,6,7,8,7,8,9,7,8,9,5,4,5,4,2  

FRAMESIZE: 4  

FIFO hit table  
 *  *  *  *  *  H  H  *  *  *  *  H  H  *  H  H  H  *  *  H  H  *  
 1  2  3  4  5  3  4  1  6  7  8  7  8  9  7  8  9  5  4  5  4  2  
Input Page String Length: 22  
FIFO Hit Total: 9  
FIFO Fault Total: 13  
FIFO Hit Rate: 40.91 %  

LRU hit table  
 *  *  *  *  *  H  H  *  *  *  *  H  H  *  H  H  H  *  *  H  H  *  
 1  2  3  4  5  3  4  1  6  7  8  7  8  9  7  8  9  5  4  5  4  2  
Input Page String Length: 22  
LRU Hit Total: 9  
LRU Fault Total: 13  
LRU Hit Rate: 40.91 %  

optimal hit table
 *  *  *  *  *  H  H  H  *  *  *  H  H  *  H  H  H  H  *  H  H  *  
 1  2  3  4  5  3  4  1  6  7  8  7  8  9  7  8  9  5  4  5  4  2  
Input Page String Length: 22  
OPTIMAL Hit Total: 11  
OPTIMAL Fault Total: 11  
OPTIMAL Hit Rate: 50.00 %  

```



 <!-- CONTACT -->
 ## Contact

 Donner Hanson - [@hansondonner](https://twitter.com/hansondonner) - hanso127@mail.chapman.edu - ChapmanID - 001276484  

Michelle Yoon  

 Project Link: [https://github.com/donnerhanson/Page-Replacement-Algorithms](https://github.com/donnerhanson/Page-Replacement-Algorithms)  

 <!-- MARKDOWN LINKS & IMAGES -->
 <!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

 [linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555  
 [linkedin-url]: https://linkedin.com/in/donner-hanson  
