void my_function() {
    volatile int dummy = 0;
    dummy = dummy + 1;
}

int main() {
    int a = 15;
    int b = 20;

    int add_res = a + b;
    int sub_res = b - a;
    int and_res = a & b;
    int or_res  = a | b;
    int xor_res = a ^ b;

    int sll_res = a << 2;  
    int sra_res = b >> 1;  

    
    if (a == 15) {       
        a = a + 1;
    }
    if (a != b) {        
        a = a + 2;
    }
    if (a < b) {         
        b = a;
    }

    my_function();

    int arr[3] = {100, 200, 300}; 
    int load_val = arr[1];        
    arr[2] = load_val;                     

    return 0;
}