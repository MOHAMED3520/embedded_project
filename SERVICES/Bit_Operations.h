//**Bit access(Set,Clear,Get)**//
#define set_bit(reg,bit) reg|=(1<<bit)
#define clear_bit(reg,bit) reg&=~(1<<bit)
#define get_bit(reg,bit)   ((reg>>bit)&1)
#define clear(reg,value) reg&=~value
#define set(reg,value) reg|=value
