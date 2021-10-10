//copy input to output

#include"kernel/types.h"
#include"user/user.h"

int main(){
    char buff[64];

    while (1)
    {
        int n = read(0,buff,1+sizeof(buff));
        if(n <= 0)
            break;

        write(1,buff,n);
    }
    
    exit(0);
}