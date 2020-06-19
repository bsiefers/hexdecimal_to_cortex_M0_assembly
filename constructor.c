#include <stdio.h>
#include <stdlib.h>

#define Rn(x) ((x) & 0x7)
#define Rd(x) (((x) >> 3) & 0x7)
#define Ops1(x) (((x) >> 6) & 0xf)
#define Ops2(x) (((x) >> 8) & 0x3)
#define toInt()
int main(){
  char* hexStrings[4];
  char* opname[]   = {"ands", "eors", "lsls", "lsrs", "asrs", "adcs", "sbcs", "rors", "tst", 
                      "rsbs", "cmps", "cmns", "orrs", "mul", "bics", "mvns"};
  char* regnames[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", 
                      "r9", "r10", "r11", "r12", "r13", "r14", "r15", "pc"};
  int inst;
  printf(".text\n.syntax unified\n.thumb\n");
  while(scanf("%x", &inst) == 1){
    if(inst & 0x4000){ 
      if((inst >> 10) & 0x1){
        //ROW 6
        if(!((inst >> 8) & 0x3)){
          printf("\tadd %s, %s\n",  regnames[Rn(inst)], regnames[(inst >> 3) & 0xf]);
        }else if((inst >> 8) & 0x1){
          printf("\tcmp %s, %s\n",  regnames[Rn(inst)], regnames[(inst >> 3) & 0xf]);
        }else{
          printf("\tmov %s, %s\n",  regnames[Rn(inst)], regnames[(inst >> 3) & 0xf]);  
        }
      }else{
        //ROW 5
        printf("\t%s %s, %s\n", opname[Ops1(inst)], regnames[Rn(inst)], regnames[Rd(inst)]);
      }
    }else if((inst >> 13) & 0x1){
        //ROW 4
        if(!((inst >> 11) & 0x3)){
          printf("\tmovs %s, %d\n", regnames[((inst >> 8) & 0x7)], inst & 0x7f);
        }else if(((inst >> 11) & 0x3) == 1){
          printf("\tcmp %s, %d\n", regnames[((inst >> 8) & 0x7)], inst & 0x7f);
        }else if(((inst >> 11) & 0x3) == 2){
          printf("\tadds %s, %d\n", regnames[((inst >> 8) & 0x7)], inst & 0x7f);
        }else{
          printf("\tsubs %s, %d\n", regnames[((inst >> 8) & 0x7)], inst & 0x7f);
        }
    }else{
      if(inst & 0x1800 || inst & 0x1c00){
        if((inst >> 10 & 0x1)){
          //ROW 3
          if((inst >> 9) & 0x1){
            printf("\tsubs %s, %s, %d\n", regnames[Rn(inst)], regnames[Rd(inst)], (inst >> 6) & 0x7);
          }else{
            printf("\tadds %s, %s, %d\n", regnames[Rn(inst)], regnames[Rd(inst)], (inst >> 6) & 0x7);
          }
        }else{
          //ROW 2
          if(!((inst >> 9) & 0x1)){
            printf("\tadds %s, %s, r%d\n", regnames[Rn(inst)], regnames[Rd(inst)], ((inst >> 6) & 0x7));
          }else{
            printf("\tsubs %s, %s, r%d\n", regnames[Rn(inst)], regnames[Rd(inst)], ((inst >> 6) & 0x7));
          }
        }
      }else{
        //ROW 1
        if(!((inst >> 11) & 0x3)){
          //OP CODE 00
          if(!((inst >> 6) & 0x1f)){
            printf("\tmovs %s, %s\n", regnames[Rn(inst)], regnames[Rd(inst)]);
          }else{
            printf("\tlsls %s, %s\n", regnames[Rn(inst)], regnames[Rd(inst)]);
          }
        }else if((inst >> 11) & 0x2){
          printf("\tlrs %s, %s\n", regnames[Rn(inst)], regnames[Rd(inst)]);
        }else{
          printf("\tasrs %s, %s\n", regnames[Rn(inst)], regnames[Rd(inst)]);
        }
      }
    }   
  }
  return 0;
}
