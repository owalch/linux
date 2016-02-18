#ifndef MY_DEFINITIONS_HEADER
#define MY_DEFINITIONS_HEADER

//******************************************************************************
// Author	M. Thaler, ZHAW, 1/2011
// Purpose	common definitions for ice cream teller
// File		commonDefs.h
//******************************************************************************

// define sempahores (file handle)
#define TELLER_SEMAPHOR     "/my_semaphor_1_name_simple_seq"
#define SUPPLIER_SEMAPHOR   "/my_semaphor_2_name_simple_seq"
#define COIN_SEMAPHOR       "/my_semaphor_3_name_simple_seq"


#define PRIZE           4          // number of coins
#define QUANTITY       10          // number of ice creams per delivery batch
#define CUSTOMERS       4          // number of CUSTOMERS
#define REFILLS        30          // number of refills by supplier
#define DELIVERY_RATE   3          // interval between deliveries (days)


//******************************************************************************

#endif

