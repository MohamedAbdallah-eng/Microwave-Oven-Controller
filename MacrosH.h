#define SET_BIT(reg,bit) (reg|=(1<<bit))
#define CLR_BIT(reg,bit) (reg&=~(1<<bit))
#define TOG_BIT(reg,bit) (reg^=(1<<bit))
#define READ_BIT(reg,bit) ((reg&(1<<bit)))>>bit
