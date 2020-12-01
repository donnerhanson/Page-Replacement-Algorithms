//
//  main.cpp
//  Page Replacement Algorithms
//
//  Created by Donner Hanson on 11/30/20.
//  Copyright © 2020 Donner Hanson. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <string>


using namespace std;

const int FRAMESIZE = 4;

int main(int argc, const char * argv[]) {
    
    
    if (argc < 2)
    {
        cout << "Program usage: ./executable -arg_string\n";
        exit(-1);
    }
    
    // initialize tlb
    int TLB [FRAMESIZE];
    for (int i(0); i < FRAMESIZE; i++) {
        TLB[i] = -1;
    }
    
    // get string to easy format
    string num_string = "";
    for (int i(1); i < argc; i++)
    {
        num_string += argv[i];
    }
    
    // remove commas
    num_string.erase(remove(num_string.begin(), num_string.end(), ','), num_string.end());
    // get length of string
    int arr_len = (int)num_string.length();
    //cout << num_string;
    //cout << "\n";
    
    // create fixed size c array
    int *arr;
    arr = new int[arr_len+1];
    // convert chars to nums
    cout << "input string: ";
    for(int i(0); i < arr_len; i++)
    {
        char num = num_string[i];
        arr[i] = num - '0';
        if (arr[i] >= 10 || arr[i] < 0)
        {
            cout << "input contains a number not between 0 and 9 inclusive\n";
            exit(-2);
        }
        
        if (i < arr_len - 1)
            cout << arr[i] << ", ";
        else
            cout << arr[i] << "\n";
    }
    
    
    
    delete [] arr;
    return 0;
}
