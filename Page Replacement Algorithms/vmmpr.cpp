/*
 Project: Page Replacement Algorithms
 Student Name: Donner Hanson, Michelle Yoon
 Student ID: 001276484
 Student Email: hanso127@mail.chapman.edu
 Date: 12/02/2020
 File: vmmpr.cpp
 Description: main
 
 Compilation:
 g++ -std=c++0x -Wall -Wextra -g vmmpr.cpp -o vmmpr;
 
 Run instructions:
 ./vmmpr <number string separated by commas>
 
 EXAMPLE:
 ./vmmpr 1, 2, 3, 4, 5, 3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2
 
 Functionality:
 Simulates Virtual Memory Page Swapping Algorithms
 User passes a number string as an argument to the program at the command line that determines the Page numbers in succession.
 The algorithms used to simulate page swaps are: First in First Out, Least Recently Used, and Optimal.
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// Default TLB size is maintained by the constant variable FRAMESIZE
const int FRAMESIZE = 4;


/*Page Class*/
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

/*containsPageNum function*/
bool containsPageNum(int search, Page* pgArr, int len) {
    for (int i(0); i < len; i++)
    {
        if (pgArr[i].getPageNum() == search) {
            return true;
        }
    }
    
    return false;
}// end of containsPageNum

/*leastRecentlyUsed function*/
int leastRecentlyUsed(Page* pgArr, int len) {
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
}// end of leastRecentlyUsed


/*getOptimalIndex function*/
int getOptimalIndex(Page* TLB, int len) {
    // we want to throw this out of the arr
    int mostDistance = TLB[0].getLastUsed();
    int indexRet = 0;
    for (int i(1); i < len; i++)
    {
        if (TLB[i].getLastUsed() > mostDistance) {
            mostDistance = TLB[i].getLastUsed();
            indexRet = i;
        }
    }
    return indexRet;
}// end of getOptimalIndex


/************************************************/
/* MAIN                                         */
/************************************************/
int main(int argc, const char * argv[]) {
    
    /* argument checking */
    if (argc < 2) {
        cout << "Program usage: ./executable -arg_string\n";
        exit(-1);
    }
    
    // get c string to c++ string format
    string num_string = "";
    for (int i(1); i < argc; i++) {
        num_string += argv[i];
    }
    
    cout << "\n";
    
    // display the user int string
    cout << "User Input String: " << num_string << "\n\n";
    
    // remove commas
    num_string.erase(remove(num_string.begin(), num_string.end(), ','), num_string.end());
    // get length of string
    int arr_len = (int)num_string.length();
    // create dynamic fixed size c int array
    
    // Error handling- maxiumum 40 numbers
    if (arr_len > 40) {
        cout << "Error: Input maxiumum of 40 numbers" << endl;
        exit(-2);
    }
    
    int *pnum_arr;
    pnum_arr = new int[arr_len+1];
    // convert chars to nums
    for(int i(0); i < arr_len; i++) {
        char num = num_string[i];
        pnum_arr[i] = num - '0';
        // number bound checking -> 0-9
        if (pnum_arr[i] >= 10 || pnum_arr[i] < 0)
        {
            cout << "Input contains a number not between 0 and 9 inclusive or a non digit character\n";
            exit(-3);
        }
        
    }
    
    char percent_sign = '%';
    // display the TLB size
    cout << "FRAMESIZE: " << FRAMESIZE <<"\n";
    
    /* FIFO */
    cout << "\n\n";
    cout << "FIFO hit table \n";
    
    // initialize outputs
    int hit_total = 0;
    double hit_rate = 0;
    // initialize tlb
    Page TLB [FRAMESIZE];
    
    for (int i(0); i < arr_len; i++) {
        int pnum = pnum_arr[i];
        // if not in TLB - FIFO alg
        if (!containsPageNum(pnum, TLB, FRAMESIZE)) {
            cout << "* ";
            for(int j(0); j < FRAMESIZE; j++) {
                if (j < FRAMESIZE - 1) {
                    // pop off front by overriding curr
                    // with next from beg. to last - 1
                    TLB[j] = TLB[j+1];
                    TLB[j].incLastUsed();
                }
                else {
                    // set last element to
                    // the "not found" page - back queue
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
                    cout << "H ";
                }
                else{
                    // increment the last time count
                    TLB[j].incLastUsed();
                }
            }
        }
    } /* end FIFO for loop */
    
    cout << "\n";
    
    // print the user int string
    for (int i(0); i < arr_len; i++) {
        if (i < arr_len - 1)
            cout << pnum_arr[i] << " ";
        else
            cout << pnum_arr[i] << "\n";
    }
    
    /* Output FIFO results */
    hit_rate = ((double)hit_total/(double)arr_len) * 100;
    printf("Input Page String Length: %d\n", arr_len);
    printf("FIFO Hit Total: %d\n", hit_total);
    printf("FIFO Fault Total: %d\n", arr_len - hit_total);
    printf("FIFO Hit Rate: %.2f %c\n", hit_rate, percent_sign);
    /* END FIFO */
    
    
    /* BEGIN LRU */
    cout << "\n\n";
    cout << "LRU hit table \n";
    
    // initialize outputs
    hit_total = 0;
    hit_rate = 0.0;
    
    // reset all TLB elements
    for (int i(0); i < FRAMESIZE; i++)
    {
        TLB[i].Reset();
    }
    
    for (int i(0); i < arr_len; i++) {
        int pnum = pnum_arr[i];
        // if not in TLB - FIFO alg
        int lru_page_index = -1;
        if (!containsPageNum(pnum, TLB, FRAMESIZE)) {
            cout << "* ";
            // find least recently used page - gives the index in TLB
            lru_page_index = leastRecentlyUsed(TLB, FRAMESIZE);
            // "swap" the page and initialize to 0
            TLB[lru_page_index].setPageNum(pnum);
            // will increment to 0 in next step along with all other values
            TLB[lru_page_index].setLastUsed(-1);
            for(int j(0); j < FRAMESIZE; j++) {
                TLB[j].incLastUsed(); // increment all TLB values
                
            }
        }
        else {
            // we know tlb contains - update last used
            // and increment hits
            for(int j(0); j < FRAMESIZE; j++) {
                if (TLB[j].getPageNum() == pnum) {
                    TLB[j].setLastUsed(0); // reusing page reset to 0
                    cout << "H ";
                    hit_total++;
                }
                else{
                    // increment the last time count
                    TLB[j].incLastUsed();
                }
            }
        }
    } /* end LRU for loop */
    
    cout << "\n";
    
    // print the user int string
    for (int i(0); i < arr_len; i++) {
        if (i < arr_len - 1)
            cout << pnum_arr[i] << " ";
        else
            cout << pnum_arr[i] << "\n";
    }
    
    /* Output LRU results */
    hit_rate = ((double)hit_total/(double)arr_len) * 100;
    printf("Input Page String Length: %d\n", arr_len);
    printf("LRU Hit Total: %d\n", hit_total);
    printf("LRU Fault Total: %d\n", arr_len - hit_total);
    printf("LRU Hit Rate: %.2f %c\n", hit_rate, percent_sign);
    /* END LRU */
    
    
    /* BEGIN OPTIMAL */
    cout << "\n\n";
    
    // initialize outputs
    hit_total = 0;
    hit_rate = 0.0;
    
    cout << "OPTIMAL hit table \n";
    // reset all TLB elements and totals
    for (int i(0); i < FRAMESIZE; i++)
    {
        TLB[i].Reset();
    }
    
    for (int curr_pnum_index(0); curr_pnum_index < arr_len; curr_pnum_index++) {
        
        if (!containsPageNum(pnum_arr[curr_pnum_index],
                             TLB, FRAMESIZE)) {
            // add new - if not contains
            for(int i(0); i < FRAMESIZE; i++) { // TLB numbers
                for(int j(curr_pnum_index); j < arr_len; j++) {
                    // check with the reamianing user int string
                    if (TLB[i].getPageNum() == pnum_arr[j]) {
                        // if the page number exist in the TLB
                        
                        break;
                    }
                    else
                        TLB[i].incLastUsed(); // increment count
                }
            }
            
            // assign the farthest index
            int optimalTossOut = getOptimalIndex(TLB, FRAMESIZE);
            //cout << "optimalTossOut index: ----   " << optimalTossOut << "  -----\n";
            
            cout << "* ";
            
            // swap TLB number with the user int string current page input
            TLB[optimalTossOut].setPageNum(pnum_arr[curr_pnum_index]);
            //cout << "pnum_arr[curr_pnum_index] " << pnum_arr[curr_pnum_index] << "\n";
            
            // reset all distances
            for (int k(0); k < FRAMESIZE; k++)
                TLB[k].setLastUsed(0);
            
        } else{
            cout << "H ";
            hit_total++;
            //cout << "Hit Total Count : " << hit_total<< "\n";
        }
    }/* end OPTIMAL for loop */
    
    cout << "\n";
    
    // print the user int string
    for (int i(0); i < arr_len; i++) {
        if (i < arr_len - 1)
            cout << pnum_arr[i] << " ";
        else
            cout << pnum_arr[i] << "\n";
    }
    
    /* Output OPTIMAL results */
    hit_rate = ((double)hit_total/(double)arr_len) * 100;
    printf("Input Page String Length: %d\n", arr_len);
    printf("OPTIMAL Hit Total: %d\n", hit_total);
    printf("OPTIMAL Fault Total: %d\n", arr_len - hit_total);
    printf("OPTIMAL Hit Rate: %.2f %c\n", hit_rate, percent_sign);
    /* END OPTIMAL */
    
    delete [] pnum_arr;
    return 0;
}//end of main
