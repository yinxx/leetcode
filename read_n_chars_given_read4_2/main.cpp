#include <iostream>
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
private:
    static const int BUFFER_SIZE = 4;
    char cache[BUFFER_SIZE];
    int size;
    int offset;
    bool done;

public:
    Solution(){
        size = 0;
        offset = 0;
        done = false;
    }
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int total = n;
        int idx = 0;
        
        while(n > 0){
            // First read whatever is left from the cache:
            int to_read = std::min(n, size);
            memcpy(buf + idx, cache + offset, to_read);
            n -= to_read;
            idx += to_read;
            offset += to_read;
            size -= to_read;

            if(done) return idx;
            if(size) continue;
            
            // Otherwise, we need to load another batch via read4.
            size = read4(cache);
            offset = 0;
            if(size < 4) // we've reached an end.
                done = true;
        }
        return total;
    }
};
