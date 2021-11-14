//
//  BitGenerator.c
//  Hapi
//
//  Created by Mihnea Stefan on 12.11.2021.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MTP 64

typedef struct{
    
    uint8_t positions[MTP];
    uint8_t taps;
    
}Polynomial;


typedef struct{
    
    Polynomial polynomial;
    uint64_t registers;
    
}LFSR;


inline static bool FindBitValue(uint64_t number, int position){
    return (number &(1 << (position - 1))) >> (position - 1);
}

inline static bool ProduceBit(LFSR *lfsr){

    bool gateResult =FindBitValue( lfsr->registers , lfsr->polynomial.positions[0]);
    
    for(int i=1;i < lfsr->polynomial.taps; i++)
        gateResult^= FindBitValue( lfsr->registers , lfsr->polynomial.positions[i]);
    
    lfsr->registers>>=1;
    if(gateResult)
        lfsr->registers|=UINT64_MAX/2+1;
    return FindBitValue(lfsr->registers, 0);
}


void PushPosition(Polynomial *p, uint8_t position){
    p->positions[p->taps] = position;
    p->taps++;
}

void PopulatePolynomial(Polynomial *p, uint64_t number){
    p->taps = 0;
    for(int i =0; i<64;i++)
        if(FindBitValue(number, i))
            PushPosition(p, i);
}

uint64_t* GenerateBits(uint64_t seed[4], uint64_t length){
    uint64_t* buffer;
    uint64_t counter = 0;
    LFSR reg[4];
    
    if(length%64 != 0)
        length = length + (64 - (length % 64));
       
    buffer = (uint64_t*)malloc(length/64 * sizeof(uint64_t));

    for(int i=0;i < 4 ; i++){
        reg[i].registers = seed[i];
        PopulatePolynomial(&reg[i].polynomial, seed[i]);
    }
        
    while(counter != length){
        bool output = ProduceBit(&reg[0]) ^ ProduceBit(&reg[1]);
        
        if(ProduceBit(&reg[3]) == true){
            output^=ProduceBit(&reg[2]);
            buffer[counter/64]>>=1;
            if(output)
                buffer[counter/64]|=UINT64_MAX/2+1;
            
        }else{
            buffer[counter/64]>>=1;
            if(output)
                buffer[counter/64]|=UINT64_MAX/2+1;
        }
        
        counter++;
    }

    return buffer;
}
