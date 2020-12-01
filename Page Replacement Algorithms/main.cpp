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

// 7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1 - to test against notes - passing
using namespace std;




class Page {
public:
    // default set to initial when no params passed
    Page() : lastUsed(0), pageNum(-1) {};
    // param constructor
    Page(int pageNum, int lastUsed) {
        this->lastUsed = lastUsed;
        this->pageNum = pageNum;
    }
    // copy constructor
    Page(const Page &other) {
        pageNum = other.getPageNum();
        lastUsed = other.getLastUsed();
    }
    // reset
    void Reset() {
        lastUsed = 0;
        pageNum = -1;
    }
    // getters and setters
    int getPageNum() const {
        return pageNum;
    }
    void setPageNum(int pnum){
        pageNum = pnum;
    }
    
    int getLastUsed() const {
        return lastUsed;
    }
    void setLastUsed(int lused) {
        lastUsed = lused;
    }
    void incLastUsed() {
        lastUsed++;
    }
    friend ostream &operator<<( ostream &output, const Page &P ) {
        output << "PageNum : " << P.pageNum << " Last Used : " << P.lastUsed;
        return output;
    }
private:
    int lastUsed;
    int pageNum;
} ;


bool containsPageNum(int search, Page* pgArr, int len)
{
    for (int i(0); i < len; i++)
    {
        if (pgArr[i].getPageNum() == search) {
            return true;
        }
    }
    
    return false;
}


int leastRecentlyUsed(Page* pgArr, int len)
{
    int prev = 0;
    int indexRet = 0;
    for (int i(0); i < len; i++)
    {
        if (pgArr[i].getLastUsed() > prev) {
            prev = pgArr[i].getLastUsed();
            indexRet = i;
        }
    }
    return indexRet;
}

const int FRAMESIZE = 3;

/************************************************/
/* MAIN                                         */
/************************************************/
int main(int argc, const char * argv[]) {
    
    /* argument checking */
    if (argc < 2)
    {
        cout << "Program usage: ./executable -arg_string\n";
        exit(-1);
    }
    
    // get c string to c++ string format
    string num_string = "";
    for (int i(1); i < argc; i++)
    {
        num_string += argv[i];
    }
    
    // remove commas
    num_string.erase(remove(num_string.begin(), num_string.end(), ','), num_string.end());
    // get length of string
    int arr_len = (int)num_string.length();

    // create dynamic fixed size c int array
    int *pnum_arr;
    pnum_arr = new int[arr_len+1];
    // convert chars to nums
    for(int i(0); i < arr_len; i++)
    {
        char num = num_string[i];
        pnum_arr[i] = num - '0';
        // number bound checking -> 0-9
        if (pnum_arr[i] >= 10 || pnum_arr[i] < 0)
        {
            cout << "input contains a number not between 0 and 9 inclusive or a non digit character\n";
            exit(-2);
        }
        
        /*
         // print the string
         if (i < arr_len - 1)
         cout << arr[i] << ", ";
         else
         cout << arr[i] << "\n";
         */
    }
    
    /* FIFO */
    
    int hit_total = 0;
    double hit_rate = 0;
    // initialize tlb
    Page TLB [FRAMESIZE];
    
    for (int i(0); i < arr_len; i++) {
        int pnum = pnum_arr[i];
        // if not in TLB - FIFO alg
        if (!containsPageNum(pnum, TLB, FRAMESIZE)) {
            for(int j(0); j < FRAMESIZE; j++) {
                if (j < FRAMESIZE - 1) {
                    TLB[j] = TLB[j+1];
                    TLB[j].incLastUsed();
                }
                else {
                    TLB[j].setLastUsed(0);
                    TLB[j].setPageNum(pnum);
                }
            }
        }
        else {
            // we know tlb contains - update last used
            // and increment hits
            for(int j(0); j < FRAMESIZE; j++) {
                if (TLB[j].getPageNum() == pnum) {
                    TLB[j].setLastUsed(0);
                    hit_total++;
                }
            }
        }
    }
    
    hit_rate = ((double)hit_total/(double)arr_len) * 100;
    printf("Input Page String Length: %d\n", arr_len);
    printf("FIFO Hit Total: %d\n", hit_total);
    printf("FIFO Fault Total: %d\n", arr_len - hit_total);
    printf("FIFO Hit Rate: %.2f\n", hit_rate);
    /* END FIFO */
    
    
    /* BEGIN LRU */
    hit_total = 0;
    hit_rate = 0.0;
    // reset all TLB elements
    // reuse array
    
    
    
    /* END LRU */
    
    delete [] pnum_arr;
    return 0;
}
