/*Ordem opcodes do livro "Z80 Family CPU User Manual" */

/*nop*/
case 0x00:
case 0x40:
case 0x49:
case 0x52: //LD D,D
case 0x5B: //LD E,E
case 0x64: //LD H,H
case 0x6D: //LD L,L
case 0x7F:

#ifdef DEBUG
printf("\n mnemonic:NOP\n");
printf("**************************\n");
#endif
break;

/**********************8 bit Loads*****************/

/*LD r,r'*/
case 0x41:////LD B,C

#ifdef DEBUG
printf("\n mnemonic:LD B,C\n");
printf("**************************\n");
#endif
B = C;
break;
case 0x42:////LD B,D

#ifdef DEBUG
printf("\n mnemonic:LD B,D\n");
printf("**************************\n");
#endif
B = D;
break;
case 0x43:////LD B,E

#ifdef DEBUG
printf("\n mnemonic:LD B,E\n");
printf("**************************\n");
#endif
B = E;
break;
case 0x44:////LD B,H

#ifdef DEBUG
printf("\n mnemonic:LD B,H\n");
printf("**************************\n");
#endif
B = H;
break;
case 0x45:////LD B,L

#ifdef DEBUG
printf("\n mnemonic:LD B,L\n");
printf("**************************\n");
#endif
B = L;
break;
case 0x47:////LD B,A

#ifdef DEBUG
printf("\n mnemonic:LD B,A\n");
printf("**************************\n");
#endif
B = A;
break;
case 0x48: ////LD C,B

#ifdef DEBUG
printf("\n mnemonic:LD C,B\n");
printf("**************************\n");
#endif
C = B;
break;
case 0x4A: ////LD C,D

#ifdef DEBUG
printf("\n mnemonic:LD C,D\n");
printf("**************************\n");
#endif
C = D;
break;
case 0x4B: ////LD C,E

#ifdef DEBUG
printf("\n mnemonic:LD C,E\n");
printf("**************************\n");
#endif
C = E;
break;
case 0x4C: ////LD C,H

#ifdef DEBUG
printf("\n mnemonic:LD C,H\n");
printf("**************************\n");
#endif
C = H;
break;
case 0x4D: ////LD C,L

#ifdef DEBUG
printf("\n mnemonic:LD C,L\n");
printf("**************************\n");
#endif
C = L;
break;
case 0x4F: ////LD C,A

#ifdef DEBUG
printf("\n mnemonic:LD C,A\n");
printf("**************************\n");
#endif
C = A;
break;
case 0x50: ////LD D,B

#ifdef DEBUG
printf("\n mnemonic:LD D,B\n");
printf("**************************\n");
#endif
D = B;
break;
case 0x51: ////LD D,C

#ifdef DEBUG
printf("\n mnemonic:LD D,C\n");
printf("**************************\n");
#endif
D = C;
break;
case 0x53: ////LD D,E

#ifdef DEBUG
printf("\n mnemonic:LD D,E\n");
printf("**************************\n");
#endif
D = E;
break;
case 0x54: ////LD D,H

#ifdef DEBUG
printf("\n mnemonic:LD D,H\n");
printf("**************************\n");
#endif
D = H;
break;
case 0x55: ////LD D,L
#ifdef DEBUG
printf("\n mnemonic:LD D,L\n");
printf("**************************\n");
#endif
D = L;
break;

case 0x57: ////LD D,A
#ifdef DEBUG
printf("\n mnemonic:LD D,A\n");
printf("**************************\n");
#endif
D = A;
break;
case 0x58: ////LD E,B

#ifdef DEBUG
printf("\n mnemonic:LD E,B\n");
printf("**************************\n");
#endif
E = B;
break;
case 0x59: ////LD E,C

#ifdef DEBUG
printf("\n mnemonic:LD E,C\n");
printf("**************************\n");
#endif
E = C;
break;
case 0x5A: ////LD E,D

#ifdef DEBUG
printf("\n mnemonic:LD E,D\n");
printf("**************************\n");
#endif
E = D;
break;
case 0x5C: ////LD E,H

#ifdef DEBUG
printf("\n mnemonic:LD E,H\n");
printf("**************************\n");
#endif
E = H;
break;
case 0x5D: ////LD E,L

#ifdef DEBUG
printf("\n mnemonic:LD E,L\n");
printf("**************************\n");
#endif
E = L;
break;
case 0x5F: ////LD E,A

#ifdef DEBUG
printf("\n mnemonic:LD E,A\n");
printf("**************************\n");
#endif
E = A;
break;
case 0x60: ////LD H,B

#ifdef DEBUG
printf("\n mnemonic:LD H,B\n");
printf("**************************\n");
#endif
H = B;
break;
case 0x61: ////LD H,C

#ifdef DEBUG
printf("\n mnemonic:LD H,C\n");
printf("**************************\n");
#endif
H = C;
break;
case 0x62: ////LD H,D

#ifdef DEBUG
printf("\n mnemonic:LD H,D\n");
printf("**************************\n");
#endif
H = D;
break;
case 0x63: ////LD H,E

#ifdef DEBUG
printf("\n mnemonic:LD H,E\n");
printf("**************************\n");
#endif
H = E;
break;
case 0x65: ////LD H,L

#ifdef DEBUG
printf("\n mnemonic:LD H,L\n");
printf("**************************\n");
#endif
H = L;
break;
case 0x67: ////LD H,A

#ifdef DEBUG
printf("\n mnemonic:LD H,A\n");
printf("**************************\n");
#endif
H = A;
break;
case 0x68: ////LD L,B

#ifdef DEBUG
printf("\n mnemonic:LD L,B\n");
printf("**************************\n");
#endif
L = B;
break;
case 0x69: ////LD L,C

#ifdef DEBUG
printf("\n mnemonic:LD L,C\n");
printf("**************************\n");
#endif
L = C;
break;
case 0x6A: ////LD L,D

#ifdef DEBUG
printf("\n mnemonic:LD L,D\n");
printf("**************************\n");
#endif
L = D;
break;
case 0x6B: ////LD L,E

#ifdef DEBUG
printf("\n mnemonic:LD L,E\n");
printf("**************************\n");
#endif
L = E;
break;
case 0x6C: ////LD L,H

#ifdef DEBUG
printf("\n mnemonic:LD L,H\n");
printf("**************************\n");
#endif
L = H;
break;
case 0x78:////LD A,B

#ifdef DEBUG
printf("\n mnemonic:LD A,B\n");
printf("**************************\n");
#endif
A = B;
break;
case 0x79:////LD A,C

#ifdef DEBUG
printf("\n mnemonic:LD A,C\n");
printf("**************************\n");
#endif
A = C;
break;
case 0x7A:////LD A,D

#ifdef DEBUG
printf("\n mnemonic:LD A,D\n");
printf("**************************\n");
#endif
A = D;
break;
case 0x7B:////LD A,E

#ifdef DEBUG
printf("\n mnemonic:LD A,E\n");
printf("**************************\n");
#endif
A = E;
break;
case 0x7C:////LD A,H

#ifdef DEBUG
printf("\n mnemonic:LD A,H\n");
printf("**************************\n");
#endif
A = H;
break;
case 0x7D:////LD A,L

#ifdef DEBUG
printf("\n mnemonic:LD A,L\n");
printf("**************************\n");
#endif
A = L;
break;

/*LD r,n*/
case 0x06: //LD B,n
B = readMem(pc++);
#ifdef DEBUG
printf(" %02x\n",B);
printf("mnemonic:LD B,%02x\n",B);
printf("**************************\n");
#endif

break;
case 0x0E: //LD C,n
C = readMem(pc++);
#ifdef DEBUG
printf(" %02x\n",C);
printf("mnemonic:LD C,%02x\n",C);
printf("**************************\n");
#endif

break;
case 0x16: //LD D,n
D = readMem(pc++);
#ifdef DEBUG
printf(" %02x\n",D);
printf("mnemonic:LD D,%02x\n",D);
printf("**************************\n");
#endif

break;
case 0x1E: //LD E,n
E = readMem(pc++);
#ifdef DEBUG
printf(" %02x\n",E);
printf("mnemonic:LD E,%02x\n",E);
printf("**************************\n");
#endif

break;
case 0x26: //LD H,n
H = readMem(pc++);
#ifdef DEBUG
printf(" %02x\n",H);
printf("mnemonic:LD H,%02x\n",H);
printf("**************************\n");
#endif

break;
case 0x2E: //LD L,n
L = readMem(pc++);
#ifdef DEBUG
printf(" %02x\n",L);
printf("mnemonic:LD L,%02x\n",L);
printf("**************************\n");
#endif

break;
    case 0x3E: //LD A,n
        A = readMem(pc++);
#ifdef DEBUG
        printf(" %02x\n",A);
        printf("mnemonic:LD A,%02x\n",A);
        printf("**************************\n");
#endif

        break;

        /*LD r,(HL)*/
    case 0x46: //LD B,(HL)
        B = readMem(HL);
#ifdef DEBUG
        printf("\nmnemonic:LD B,HL\n");
        printf("**************************\n");
#endif

        break;
    case 0x4E: //LD C,(HL)
        C = readMem(HL);
#ifdef DEBUG
        printf("\nmnemonic:LD C,HL\n");
        printf("**************************\n");
#endif

        break;
    case 0x56: //LD D,(HL)
        D = readMem(HL);
#ifdef DEBUG
        printf("\nmnemonic:LD D,HL\n");
        printf("**************************\n");
#endif

        break;
    case 0x5E: //LD E,(HL)
        E = readMem(HL);
#ifdef DEBUG
        printf("\nmnemonic:LD E,HL\n");
        printf("**************************\n");
#endif

        break;
    case 0x66: //LD H,(HL)
        H = readMem(HL);
#ifdef DEBUG
        printf("\nmnemonic:LD H,HL\n");
        printf("**************************\n");
#endif

        break;
    case 0x6E: //LD L,(HL)
        L = readMem(HL);
#ifdef DEBUG
        printf("\nmnemonic:LD L,HL\n");
        printf("**************************\n");
#endif

        break;
    case 0x7E: //LD A,(HL)
        A = readMem(HL);
#ifdef DEBUG
        printf("\nmnemonic:LD A,HL\n");
        printf("**************************\n");
#endif

        break;

        /*LD (HL),r*/
    case 0x70: //LD (HL),B

#ifdef DEBUG
        printf("\nmnemonic:LD (HL),B\n");
        printf("**************************\n");
#endif
        writeMem(HL, B);
        break;
    case 0x71://LD (HL),C

#ifdef DEBUG
        printf("\nmnemonic:LD (HL),C\n");
        printf("**************************\n");
#endif
        writeMem(HL, C);
        break;
    case 0x72://LD (HL),D

#ifdef DEBUG
        printf("\nmnemonic:LD (HL),D\n");
        printf("**************************\n");
#endif
        writeMem(HL, D);
        break;
    case 0x73://LD (HL),E

#ifdef DEBUG
        printf("\nmnemonic:LD (HL),E\n");
        printf("**************************\n");
#endif
        writeMem(HL, E);
        break;
    case 0x74://LD (HL),H

#ifdef DEBUG
        printf("\nmnemonic:LD (HL),H\n");
        printf("**************************\n");
#endif
        writeMem(HL, H);
        break;
    case 0x75://LD (HL),L

#ifdef DEBUG
        printf("\nmnemonic:LD (HL),L\n");
        printf("**************************\n");
#endif
        writeMem(HL, L);
        break;
    case 0x77://LD (HL),A

#ifdef DEBUG
        printf("\nmnemonic:LD (HL),A\n");
        printf("**************************\n");
#endif
        writeMem(HL, A);
        break;

        /*LD (HL), n*/
    case 0x36:
        writeMem(HL, readMem(pc++));
#ifdef DEBUG
        printf("\nmnemonic:LD (HL),%02x\n",readMem(pc-1));
        printf("**************************\n");
#endif
        break;

        /*LD A,(BC)*/
    case 0x0A:

#ifdef DEBUG
        printf("\nmnemonic:LD A,(BC)\n");
        printf("**************************\n");
#endif
        A = readMem(BC);
        break;
        /*LD A,(DE)*/
    case 0x1A:
#ifdef DEBUG
        printf("\nmnemonic:LD A,(DE)\n");
        printf("**************************\n");
#endif
        A = readMem(DE);
        break;

        /*LD(BC),A*/
    case 0x02:

#ifdef DEBUG
        printf("\nmnemonic:LD (BC),A\n");
        printf("**************************\n");
#endif
        writeMem(BC, A);
        break;
        /*LD(DE),A*/
    case 0x12:

#ifdef DEBUG
        printf("\nmnemonic:LD (DE),A\n");
        printf("**************************\n");
#endif
        writeMem(DE, A);
        break;

        /*instrucoes especificas gameboy*/

        /*opcode      Z80             GMB    */
        /*3A      LD   A,(nn)     LDD  A,(HL)*/
        /*ldd  A,(HL)      3A         8 ---- A=(HL), HL=HL-1*/
    case 0x3A://LDD A,(HL)
#ifdef DEBUG
        printf("\nmnemonic:LDD A,(HL)\n");
        printf("**************************\n");
#endif
        A = readMem(HL);
        HL--;
        break;

        /*opcode      Z80             GMB    */
        /*32      LD   (nn),A     LDD  (HL),A*/
        /*ldd  (HL),A      32         8 ---- (HL)=A, HL=HL-1*/
    case 0x32:
#ifdef DEBUG
        printf("\nmnemonic:LDD (HL),A\n");
        printf("**************************\n");
#endif
        writeMem(HL, A);
        HL--;
        break;

        /*opcode      Z80             GMB    */
        /* EA      JP   PE,nn      LD   (nn),A*/
        /*ld   (nn),A      EA        16 ----*/
    case 0xEA:
        address = readMem(pc+1);
        address = address << 8;
        address = address | readMem(pc);
        writeMem(address,A);
#ifdef DEBUG
        printf("%02x %02x",readMem(pc),readMem(pc+1));
        printf("\nmnemonic:LD (%04x),A\n",address);
        printf("**************************\n");
#endif
        pc+=2;
        break;

        /*opcode      Z80             GMB    */
        /*FA      JP   M,nn       LD   A,(nn)*/
        /*ld   A,(nn)      FA        16 ----*/
    case 0xFA:
        address = readMem(pc+1);
        address = address << 8;
        address=address | readMem(pc);
        A=readMem(address);
#ifdef DEBUG
        printf("%02x %02x",readMem(pc),readMem(pc+1));
        printf("\nmnemonic:LD A,(%04x)\n",address);
        printf("**************************\n");
#endif
        pc+=2;
        break;

        /*opcode      Z80             GMB    */
        /*E0      RET  PO         LD   (FF00+n),A*/
        /*ld   (FF00+n),A  E0 nn     12 ---- write to io-port n (memory FF00+n)*/
    case 0xE0:
        writeMem(0xFF00+readMem(pc++),A);
#ifdef DEBUG
        printf("%02x",readMem(pc-1));
        printf("\nmnemonic:LD (FF00+%02x),A\n",readMem(pc-1));
        printf("**************************\n");
#endif
        break;

        /*opcode      Z80             GMB    */
        /*F0      RET  P          LD   A,(FF00+n)*/
        /*ld   A,(FF00+n)  F0 nn     12 ---- read from io-port n (memory FF00+n)*/
    case 0xF0:
        A=readMem(0xFF00+readMem(pc++));
#ifdef DEBUG
        printf("%02x",readMem(pc-1));
        printf("\nmnemonic:LD A,(FF00+%02x)\n",readMem(pc-1));
        printf("**************************\n");
#endif
        break;

        /*opcode      Z80             GMB    */
        /*E2      JP   PO,nn      LD   (FF00+C),A*/
        /*ld   (FF00+C),A  E2         8 ---- write to io-port C (memory FF00+C)*/
    case 0xE2:
        writeMem(0xFF00+C,A);
#ifdef DEBUG
        printf("\nmnemonic:LD (FF00+C),A\n");
        printf("**************************\n");
#endif
        break;

        /*opcode      Z80             GMB    */
        /*F2      JP   P,nn       LD   A,(FF00+C*/
        /*ld   A,(FF00+C)  F2         8 ---- read from io-port C (memory FF00+C)*/
    case 0xF2:
        A=readMem(0xFF00+C);
#ifdef DEBUG
        printf("\nmnemonic:LD A,(FF00+C)\n");
        printf("**************************\n");
#endif
        break;

        /*opcode      Z80             GMB    */
        /*22      LD   (nn),HL    LDI  (HL),A*/
        /*ldi  (HL),A      22         8 ---- (HL)=A, HL=HL+1*/
    case 0x22:
        writeMem(HL,A);
        HL++;
#ifdef DEBUG
        printf("\nmnemonic:LDI (HL),A\n");
        printf("**************************\n");
#endif
        break;

        /*opcode      Z80             GMB    */
        /*2A      LD   HL,(nn)    LDI  A,(HL)*/
        /*ldi  A,(HL)      2A         8 ---- A=(HL), HL=HL+1*/
    case 0x2A:
        A=readMem(HL);
        HL++;
#ifdef DEBUG
        printf("\nmnemonic:LDI A,(HL)\n");
        printf("**************************\n");
#endif
        break;

        /**********************16 bit Loads*****************/

        /*LD rr,nn*/
    case 0x01 ://LD BC,nn
        C=readMem(pc++);
        B=readMem(pc++);
#ifdef DEBUG
        printf("%02x %02x",C,B);
        printf("\nmnemonic:LD BC,%04x\n",BC);
        printf("**************************\n");
#endif
        break;
    case 0x11 : //LD DE,nn
        E=readMem(pc++);
        D=readMem(pc++);
#ifdef DEBUG
        printf("%02x %02x",E,D);
        printf("\nmnemonic:LD DE,%04x\n",DE);
        printf("**************************\n");
#endif
        break;
    case 0x21: //LD HL,nn
        L=readMem(pc++);
        H=readMem(pc++);
#ifdef DEBUG
        printf("%02x %02x",L,H);
        printf("\nmnemonic:LD HL,%04x\n",HL);
        printf("**************************\n");
#endif
        break;
    case 0x31: //LD SP,nn
        gbcpu.sp.Byte.l = readMem(pc++);
        gbcpu.sp.Byte.h = readMem(pc++);
#ifdef DEBUG
        printf("%02x %02x",readMem(pc-2),readMem(pc-1));
        printf("\nmnemonic:LD SP,%04x\n",SP);
        printf("**************************\n");
#endif
        break;

        /*  ld   SP,HL */
    case 0xF9:
        SP=HL;
#ifdef DEBUG
        printf("\nmnemonic:LD SP,HL\n");
        printf("**************************\n");
#endif
        break;
        /*LD (nn),SP */
    case 0x08:
        address = readMem(pc+1);
        address = address << 8;
        address=address | readMem(pc);
        writeMem(address,gbcpu.sp.Byte.l);
        writeMem(address+1,gbcpu.sp.Byte.h);
#ifdef DEBUG
        printf("%02x %02x",readMem(pc),readMem(pc+1));
        printf("\nmnemonic:LD (%04x),SP\n",address);
        printf("**************************\n");
#endif
        //TODO : esquecido ? pc+=2
        pc+=2;
        break;

        /*push rr*/
    case 0xF5 ://PUSH AF
        writeMem(SP-2,F);
        writeMem(SP-1,A);
        SP-=2;
#ifdef DEBUG
        printf("\nmnemonic:PUSH AF\n");
        printf("**************************\n");
#endif
        break;
    case 0xC5 ://PUSH BC
        writeMem(SP-2,C);
        writeMem(SP-1,B);
        SP-=2;
#ifdef DEBUG
        printf("\nmnemonic:PUSH BC\n");
        printf("**************************\n");
#endif
        break;
    case 0xD5 ://PUSH DE
        writeMem(SP-2,E);
        writeMem(SP-1,D);
        SP-=2;
#ifdef DEBUG
        printf("\nmnemonic:PUSH DE\n");
        printf("**************************\n");
#endif
        break;
    case 0xE5 ://PUSH HL
        writeMem(SP-2,L);
        writeMem(SP-1,H);
        SP-=2;
#ifdef DEBUG
        printf("\nmnemonic:PUSH HL\n");
        printf("**************************\n");
#endif
        break;

        /*pop  rr*/
    case 0xF1: //POP AF
        F=readMem(SP);
        A=readMem(SP+1);
        SP+=2;
#ifdef DEBUG
        printf("\nmnemonic:POP AF\n");
        printf("**************************\n");
#endif
        break;
    case 0xC1: //POP BC
        C=readMem(SP);
        B=readMem(SP+1);
        SP+=2;
#ifdef DEBUG
        printf("\nmnemonic:POP BC\n");
        printf("**************************\n");
#endif
        break;
    case 0xD1: //POP DE
        E=readMem(SP);
        D=readMem(SP+1);
        SP+=2;
#ifdef DEBUG
        printf("\nmnemonic:POP DE\n");
        printf("**************************\n");
#endif
        break;
    case 0xE1: //POP HL
        L=readMem(SP);
        H=readMem(SP+1);
        SP+=2;
#ifdef DEBUG
        printf("\nmnemonic:POP HL\n");
        printf("**************************\n");
#endif
        break;

        /*****************GMB 8bit-Arithmetic/logical Commands*********************/

        /*add  A,r*/
    case 0x80: //ADD A,B

#ifdef DEBUG
        printf("\nmnemonic:ADD A,B\n");
        printf("**************************\n");
#endif
        ADD_A(B);
        break;
    case 0x81: //ADD A,C

#ifdef DEBUG
        printf("\nmnemonic:ADD A,C\n");
        printf("**************************\n");
#endif
        ADD_A(C);
        break;
    case 0x82: //ADD A,D

#ifdef DEBUG
        printf("\nmnemonic:ADD A,D\n");
        printf("**************************\n");
#endif
        ADD_A(D);
        break;
    case 0x83: //ADD A,E

#ifdef DEBUG
        printf("\nmnemonic:ADD A,E\n");
        printf("**************************\n");
#endif
        ADD_A(E);
        break;
    case 0x84: //ADD A,H

#ifdef DEBUG
        printf("\nmnemonic:ADD A,H\n");
        printf("**************************\n");
#endif
        ADD_A(H);
        break;
    case 0x85: //ADD A,L

#ifdef DEBUG
        printf("\nmnemonic:ADD A,L\n");
        printf("**************************\n");
#endif
        ADD_A(L);
        break;
    case 0x87: //ADD A,A

#ifdef DEBUG
        printf("\nmnemonic:ADD A,A\n");
        printf("**************************\n");
#endif
        ADD_A(A);
        break;

        /*add A,n*/
    case 0xC6:
        ADD_A(readMem(pc++));
#ifdef DEBUG
        printf("%02x",readMem(pc-1));
        printf("\nmnemonic:ADD A,%02x\n",readMem(pc-1));
        printf("**************************\n");
#endif
        break;
        /*add A,(HL)*/
    case 0x86:
#ifdef DEBUG
        printf("\nmnemonic:ADD A,(HL)\n");
        printf("**************************\n");
#endif
        ADD_A(readMem(HL));
        break;

        /*ADC A,r*/
    case 0x8F: //ADC A,A

#ifdef DEBUG
        printf("\nmnemonic:ADC A,A\n");
        printf("**************************\n");
#endif
        ADC_A(A);
        break;
    case 0x88: //ADC A,B

#ifdef DEBUG
        printf("\nmnemonic:ADC A,B\n");
        printf("**************************\n");
#endif
        ADC_A(B);
        break;
    case 0x89: //ADC A,C

#ifdef DEBUG
        printf("\nmnemonic:ADC A,C\n");
        printf("**************************\n");
#endif
        ADC_A(C);
        break;
    case 0x8A: //ADC A,D

#ifdef DEBUG
        printf("\nmnemonic:ADC A,D\n");
        printf("**************************\n");
#endif
        ADC_A(D);
        break;
    case 0x8B: //ADC A,E

#ifdef DEBUG
        printf("\nmnemonic:ADC A,E\n");
        printf("**************************\n");
#endif
        ADC_A(E);
        break;
    case 0x8C: //ADC A,H

#ifdef DEBUG
        printf("\nmnemonic:ADC A,H\n");
        printf("**************************\n");
#endif
        ADC_A(H);
        break;
    case 0x8D: //ADC A,L

#ifdef DEBUG
        printf("\nmnemonic:ADC A,L\n");
        printf("**************************\n");
#endif
        ADC_A(L);
        break;

        /*ADC A,n*/
    case 0xCE:
        ADC_A(readMem(pc++));
#ifdef DEBUG
        printf("%02x",readMem(pc-1));
        printf("\nmnemonic:ADC A,%02x\n",readMem(pc-1));
        printf("**************************\n");
#endif
        break;

        /*ADC A,(HL)*/
    case 0x8E:
        ADC_A(readMem(HL));
#ifdef DEBUG
        printf("\nmnemonic:ADC A,(HL)\n");
        printf("**************************\n");
#endif
        break;

        /*SUB A,r */
    case 0x90: //SUB B

#ifdef DEBUG
        printf("\nmnemonic:SUB A,B\n");
        printf("**************************\n");
#endif
        SUB_A(B);
        break;
    case 0x91: //SUB C

#ifdef DEBUG
        printf("\nmnemonic:SUB A,C\n");
        printf("**************************\n");
#endif
        SUB_A(C);
        break;
    case 0x92: //SUB D

#ifdef DEBUG
        printf("\nmnemonic:SUB A,D\n");
        printf("**************************\n");
#endif
        SUB_A(D);
        break;
    case 0x93: //SUB E

#ifdef DEBUG
        printf("\nmnemonic:SUB A,E\n");
        printf("**************************\n");
#endif
        SUB_A(E);
        break;
    case 0x94: //SUB H

#ifdef DEBUG
        printf("\nmnemonic:SUB A,H\n");
        printf("**************************\n");
#endif
        SUB_A(H);
        break;
    case 0x95: //SUB L

#ifdef DEBUG
        printf("\nmnemonic:SUB A,L\n");
        printf("**************************\n");
#endif
        SUB_A(L);
        break;
    case 0x97: //SUB A

#ifdef DEBUG
        printf("\nmnemonic:SUB A,A\n");
        printf("**************************\n");
#endif
        SUB_A(A);
        break;

        /*SUB A,(HL) */
    case 0x96:
#ifdef DEBUG
        printf("\nmnemonic:SUB A,(HL)\n");
        printf("**************************\n");
#endif
        SUB_A(readMem(HL));
        break;
        /*SUB A,n*/
    case 0xD6:
        SUB_A(readMem(pc++));
#ifdef DEBUG
        printf("%02x",readMem(pc-1));
        printf("\nmnemonic:SUB A,%02x\n",readMem(pc-1));
        printf("**************************\n");
#endif
        break;

        /*SBC A,r*/
    case 0x98: //SBC B

#ifdef DEBUG
        printf("\nmnemonic:SBC A,B\n");
        printf("**************************\n");
#endif
        SBC_A(B);
        break;
    case 0x99: //SBC C

#ifdef DEBUG
        printf("\nmnemonic:SBC A,C\n");
        printf("**************************\n");
#endif
        SBC_A(C);
        break;
    case 0x9A: //SBC D

#ifdef DEBUG
        printf("\nmnemonic:SBC A,D\n");
        printf("**************************\n");
#endif
        SBC_A(D);
        break;
    case 0x9B: //SBC E

#ifdef DEBUG
        printf("\nmnemonic:SBC A,E\n");
        printf("**************************\n");
#endif
        SBC_A(E);
        break;
    case 0x9C: //SBC H

#ifdef DEBUG
        printf("\nmnemonic:SBC A,H\n");
        printf("**************************\n");
#endif
        SBC_A(H);
        break;
    case 0x9D: //SBC L

#ifdef DEBUG
        printf("\nmnemonic:SBC A,L\n");
        printf("**************************\n");
#endif
        SBC_A(L);
        break;
    case 0x9F: //SBC A

#ifdef DEBUG
        printf("\nmnemonic:SBC A,A\n");
        printf("**************************\n");
#endif
        SBC_A(A);
        break;

        /*SBC A,(HL) */
    case 0x9E:
        SBC_A(readMem(HL));
#ifdef DEBUG
        printf("\nmnemonic:SBC A,(HL)\n");
        printf("**************************\n");
#endif
        break;
        /*SBC A,n*/
    case 0xDE:
        SBC_A(readMem(pc++));
#ifdef DEBUG
        printf("%02x",readMem(pc-1));
        printf("\nmnemonic:SBC A,%02x\n",readMem(pc-1));
        printf("**************************\n");
#endif
        break;

        /*AND A,r */
    case 0xA0: //AND B

#ifdef DEBUG
        printf("\nmnemonic:AND A,B\n");
        printf("**************************\n");
#endif
        AND_A(B);
        break;
    case 0xA1: //AND C

#ifdef DEBUG
        printf("\nmnemonic:AND A,C\n");
        printf("**************************\n");
#endif
        AND_A(C);
        break;
    case 0xA2: //AND D

#ifdef DEBUG
        printf("\nmnemonic:AND A,D\n");
        printf("**************************\n");
#endif
        AND_A(D);
        break;
    case 0xA3: //AND E

#ifdef DEBUG
        printf("\nmnemonic:AND A,E\n");
        printf("**************************\n");
#endif
        AND_A(E);
        break;
    case 0xA4: //AND H

#ifdef DEBUG
        printf("\nmnemonic:AND A,H\n");
        printf("**************************\n");
#endif
        AND_A(H);
        break;
    case 0xA5: //AND L

#ifdef DEBUG
        printf("\nmnemonic:AND A,L\n");
        printf("**************************\n");
#endif
        AND_A(L);
        break;
    case 0xA7: //AND A

#ifdef DEBUG
        printf("\nmnemonic:AND A,A\n");
        printf("**************************\n");
#endif
        AND_A(A);
        break;

        /*AND A,(HL) */
    case 0xA6:
#ifdef DEBUG
        printf("\nmnemonic:AND A,(HL)\n");
        printf("**************************\n");
#endif
        AND_A(readMem(HL));
        break;
        /*AND A,n*/
    case 0xE6:
        AND_A(readMem(pc++));
#ifdef DEBUG
        printf("%02x",readMem(pc-1));
        printf("\nmnemonic:AND A,%02x\n",readMem(pc-1));
        printf("**************************\n");
#endif
        break;

        /*XOR A,r */
    case 0xA8: //XOR B

#ifdef DEBUG
        printf("\nmnemonic:XOR A,B\n");
        printf("**************************\n");
#endif
        XOR_A(B);
        break;
    case 0xA9: //XOR C

#ifdef DEBUG
        printf("\nmnemonic:XOR A,C\n");
        printf("**************************\n");
#endif
        XOR_A(C);
        break;
    case 0xAA: //XOR D

#ifdef DEBUG
        printf("\nmnemonic:XOR A,D\n");
        printf("**************************\n");
#endif
        XOR_A(D);
        break;
    case 0xAB: //XOR E

#ifdef DEBUG
        printf("\nmnemonic:XOR A,E\n");
        printf("**************************\n");
#endif
        XOR_A(E);
        break;
    case 0xAC: //XOR H

#ifdef DEBUG
        printf("\nmnemonic:XOR A,H\n");
        printf("**************************\n");
#endif
        XOR_A(H);
        break;
    case 0xAD: //XOR L

#ifdef DEBUG
        printf("\nmnemonic:XOR A,L\n");
        printf("**************************\n");
#endif
        XOR_A(L);
        break;
    case 0xAF: //XOR A

#ifdef DEBUG
        printf("\nmnemonic:XOR A,A\n");
        printf("**************************\n");
#endif
        XOR_A(A);
        break;

        /*XOR A,(HL) */
    case 0xAE:
        XOR_A(readMem(HL));
#ifdef DEBUG
        printf("\nmnemonic:XOR A,(HL)\n");
        printf("**************************\n");
#endif
        break;
        /*XOR A,n*/
    case 0xEE:
        XOR_A(readMem(pc++));
#ifdef DEBUG
        printf("%02x",readMem(pc-1));
        printf("\nmnemonic:XOR A,%02x\n",readMem(pc-1));
        printf("**************************\n");
#endif
        break;

        /*OR A,r */
    case 0xB0: //OR B

#ifdef DEBUG
        printf("\nmnemonic:OR A,B\n");
        printf("**************************\n");
#endif
        OR_A(B);
        break;
    case 0xB1: //OR C

#ifdef DEBUG
        printf("\nmnemonic:OR A,C\n");
        printf("**************************\n");
#endif
        OR_A(C);
        break;
    case 0xB2: //OR D

#ifdef DEBUG
        printf("\nmnemonic:OR A,D\n");
        printf("**************************\n");
#endif
        OR_A(D);
        break;
    case 0xB3: //OR E

#ifdef DEBUG
        printf("\nmnemonic:OR A,E\n");
        printf("**************************\n");
#endif
        OR_A(E);
        break;
    case 0xB4: //OR H

#ifdef DEBUG
        printf("\nmnemonic:OR A,H\n");
        printf("**************************\n");
#endif
        OR_A(H);
        break;
    case 0xB5: //OR L

#ifdef DEBUG
        printf("\nmnemonic:OR A,L\n");
        printf("**************************\n");
#endif
        OR_A(L);
        break;
    case 0xB7: //OR A

#ifdef DEBUG
        printf("\nmnemonic:OR A,A\n");
        printf("**************************\n");
#endif
        OR_A(A);
        break;

        /*OR A,(HL) */
    case 0xB6:
        OR_A(readMem(HL));
#ifdef DEBUG
        printf("\nmnemonic:OR A,(HL)\n");
        printf("**************************\n");
#endif
        break;

        /*OR A,n*/
    case 0xF6:
        OR_A(readMem(pc++));
#ifdef DEBUG
        printf("%02x",readMem(pc-1));
        printf("\nmnemonic:OR A,%02x\n",readMem(pc-1));
        printf("**************************\n");
#endif
        break;

        /*CP A,r */
    case 0xB8: //CP B

#ifdef DEBUG
        printf("\nmnemonic:CP A,B\n");
        printf("**************************\n");
#endif
        CP_A(B);
        break;
    case 0xB9: //CP C

#ifdef DEBUG
        printf("\nmnemonic:CP A,C\n");
        printf("**************************\n");
#endif
        CP_A(C);
        break;
    case 0xBA: //CP D

#ifdef DEBUG
        printf("\nmnemonic:CP A,D\n");
        printf("**************************\n");
#endif
        CP_A(D);
        break;
    case 0xBB: //CP E

#ifdef DEBUG
        printf("\nmnemonic:CP A,E\n");
        printf("**************************\n");
#endif
        CP_A(E);
        break;
    case 0xBC: //CP H

#ifdef DEBUG
        printf("\nmnemonic:CP A,H\n");
        printf("**************************\n");
#endif
        CP_A(H);
        break;
    case 0xBD: //CP L

#ifdef DEBUG
        printf("\nmnemonic:CP A,L\n");
        printf("**************************\n");
#endif
        CP_A(L);
        break;
    case 0xBF: //CP A

#ifdef DEBUG
        printf("\nmnemonic:CP A,A\n");
        printf("**************************\n");
#endif
        CP_A(A);
        break;

        /*CP A,(HL) */
    case 0xBE:
        CP_A(readMem(HL));
#ifdef DEBUG
        printf("\nmnemonic:CP A,(HL)\n");
        printf("**************************\n");
#endif
        break;

        /*CP A,n*/
    case 0xFE:
        CP_A(readMem(pc++));
#ifdef DEBUG
        printf("%02x",readMem(pc-1));
        printf("\nmnemonic:CP A,%02x\n",readMem(pc-1));
        printf("**************************\n");
#endif
        break;

        /*INC r */
    case 0x04: //INC B

#ifdef DEBUG
        printf("\nmnemonic:INC B\n");
        printf("**************************\n");
#endif
        INC(B);
        break;
    case 0x0C: //INC C

#ifdef DEBUG
        printf("\nmnemonic:INC C\n");
        printf("**************************\n");
#endif
        INC(C);
        break;
    case 0x14: //INC D

#ifdef DEBUG
        printf("\nmnemonic:INC D\n");
        printf("**************************\n");
#endif
        INC(D);
        break;
    case 0x1C: //INC E

#ifdef DEBUG
        printf("\nmnemonic:INC E\n");
        printf("**************************\n");
#endif
        INC(E);
        break;
    case 0x24: //INC H

#ifdef DEBUG
        printf("\nmnemonic:INC H\n");
        printf("**************************\n");
#endif
        INC(H);
        break;
    case 0x2C: //INC L

#ifdef DEBUG
        printf("\nmnemonic:INC L\n");
        printf("**************************\n");
#endif
        INC(L);
        break;
    case 0x3C: //INC A

#ifdef DEBUG
        printf("\nmnemonic:INC A\n");
        printf("**************************\n");
#endif
        INC(A);
        break;

        /*INC (HL) */
    case 0x34:
        tempbyte=readMem(HL);
        INC(tempbyte);
        writeMem(HL,tempbyte);
#ifdef DEBUG
        printf("\nmnemonic:INC (HL)\n");
        printf("**************************\n");
#endif
        break;

        /*DEC r */
    case 0x05: //DEC B

#ifdef DEBUG
        printf("\nmnemonic:DEC B\n");
        printf("**************************\n");
#endif
        DEC(B);
        break;
    case 0x0D: //DEC C

#ifdef DEBUG
        printf("\nmnemonic:DEC C\n");
        printf("**************************\n");
#endif
        DEC(C);
        break;
    case 0x15: //DEC D

#ifdef DEBUG
        printf("\nmnemonic:DEC D\n");
        printf("**************************\n");
#endif
        DEC(D);
        break;
    case 0x1D: //DEC E

#ifdef DEBUG
        printf("\nmnemonic:DEC E\n");
        printf("**************************\n");
#endif
        DEC(E);
        break;
    case 0x25: //DEC H

#ifdef DEBUG
        printf("\nmnemonic:DEC H\n");
        printf("**************************\n");
#endif
        DEC(H);
        break;
    case 0x2D: //DEC L

#ifdef DEBUG
        printf("\nmnemonic:DEC L\n");
        printf("**************************\n");
#endif
        DEC(L);
        break;
    case 0x3D: //DEC A

#ifdef DEBUG
        printf("\nmnemonic:DEC A\n");
        printf("**************************\n");
#endif
        DEC(A);
        break;

        /*DEC (HL) */
    case 0x35:
        tempbyte=readMem(HL);
        DEC(tempbyte);
        writeMem(HL,tempbyte);
#ifdef DEBUG
        printf("\nmnemonic:DEC (HL)\n");
        printf("**************************\n");
#endif
        break;

        /*DAA */
    case 0x27:
        //TODO: verificar valor
        opAux.Byte.h = (F & 0x70) >> 4;
        opAux.Byte.l = A;
        AF= DAALookup[opAux.Word];
#ifdef DEBUG
        printf("\nmnemonic:DAA\n");
        printf("**************************\n");
#endif
        break;

        /*CPL*/
    case 0x2F:
        A = A ^ 0xFF;
        F |= H_FLAG;
        F |= N_FLAG;
#ifdef DEBUG
        printf("\nmnemonic:CPL\n");
        printf("**************************\n");
#endif
        break;

        /*****************GMB 16bit-Arithmetic/logical Commands*********************/

        /*ADD HL,rr*/
    case 0x09: //ADD HL,BC

#ifdef DEBUG
        printf("\nmnemonic:ADD HL,BC\n");
        printf("**************************\n");
#endif
        ADD_HL(BC);
        break;

    case 0x19: //ADD HL,DE
#ifdef DEBUG
        printf("\nmnemonic:ADD HL,DE\n");
        printf("**************************\n");
#endif
        ADD_HL(DE);
        break;

    case 0x29: //ADD HL,HL
#ifdef DEBUG
        printf("\nmnemonic:ADD HL,HL\n");
        printf("**************************\n");
#endif
        ADD_HL(HL);
        break;

    case 0x39: //ADD HL,SP
#ifdef DEBUG
        printf("\nmnemonic:ADD HL,SP\n");
        printf("**************************\n");
#endif
        ADD_HL(SP);
        break;

        /*ADD SP,n */
        //TODO: por verificar (signed byte)
    case 0xE8:
        signedtempbyte = readMem(pc++);
        ADD_SP(signedtempbyte);
#ifdef DEBUG
        printf("%02x",signedtempbyte);
        printf("\nmnemonic:CP A,%d\n",signedtempbyte);
        printf("**************************\n");
#endif
        break;

        /*INC rr*/
    case 0x03: //INC BC

#ifdef DEBUG
        printf("\nmnemonic:INC BC\n");
        printf("**************************\n");
#endif
        BC+=1;
        break;
    case 0x13: //INC DE

#ifdef DEBUG
        printf("\nmnemonic:INC DE\n");
        printf("**************************\n");
#endif
        DE+=1;
        break;
    case 0x23: //INC HL

#ifdef DEBUG
        printf("\nmnemonic:INC HL\n");
        printf("**************************\n");
#endif
        HL+=1;
        break;
    case 0x33: //INC SP

#ifdef DEBUG
        printf("\nmnemonic:INC SP\n");
        printf("**************************\n");
#endif
        SP+=1;
        break;

        /*DEC rr*/
    case 0x0B: //DEC BC

#ifdef DEBUG
        printf("\nmnemonic:DEC BC\n");
        printf("**************************\n");
#endif
        BC-=1;
        break;
    case 0x1B: //DEC DE

#ifdef DEBUG
        printf("\nmnemonic:DEC DE\n");
        printf("**************************\n");
#endif
        DE-=1;
        break;
    case 0x2B: //DEC HL

#ifdef DEBUG
        printf("\nmnemonic:DEC HL\n");
        printf("**************************\n");
#endif
        HL-=1;
        break;
    case 0x3B: //DEC SP

#ifdef DEBUG
        printf("\nmnemonic:DEC SP\n");
        printf("**************************\n");
#endif
        SP-=1;
        break;

        /*LD HL,SP+n*/
        //TODO: por verificar (signed byte)
    case 0xF8:
        signedtempbyte=readMem(pc++);
        LD_HLSP(signedtempbyte);
#ifdef DEBUG
        printf("%02x",signedtempbyte);
        printf("\nmnemonic:LD HL,SP+%d\n",signedtempbyte);
        printf("**************************\n");
#endif
        break;

        /*****************GMB Rotate- , Shift- and Singlebit Operation Commands*********************/

    case 0x07: //RLCA
        F = (A & 0x80) >> 3;
        A = (A << 1) | (A >> 7);
#ifdef DEBUG
        printf("\nmnemonic:RLCA\n");
        printf("**************************\n");
#endif
        break;

    case 0x17: //RLA
        opAux.Byte.l=A;
        opAux.Byte.h=(F&C_FLAG)>>4;
        opAux.Word = ((opAux.Word << 1)|(opAux.Word >> 8)) & 0x1FF;
        A=opAux.Byte.l;
        F=opAux.Byte.h << 4;
#ifdef DEBUG
        printf("\nmnemonic:RLA\n");
        printf("**************************\n");
#endif
        break;

    case 0x0F: //RRCA
        F = (A & 0x1) << 4;
        A = (A >> 1) | (A << 7);
#ifdef DEBUG
        printf("\nmnemonic:RRCA\n");
        printf("**************************\n");
#endif
        break;

    case 0x1F: //RRA
        opAux.Word =  (A << 1) | ((F & C_FLAG) >> 4);
        opAux.Word = ((opAux.Word >> 1) | (opAux.Word << 8)) & 0x1FF;
        F = (opAux.Word & 0x1) << 4 ;
        A = opAux.Word >> 1;
#ifdef DEBUG
        printf("\nmnemonic:RRA\n");
        printf("**************************\n");
#endif
        break;

        /*rotate and shifts CB Opcodes */
    case 0xCB:

            OpCode= readMem(pc++);
        Counter -= CyclesCB[OpCode];
        gbcpu.cyclecounter += CyclesCB[OpCode];
#ifdef DEBUG
        printf("%02x",OpCode);
        CyclesCBCount[OpCode]++;
#endif

        switch (OpCode) {

            /*RLC  r*/
        case 0x00: //RLC B

#ifdef DEBUG
            printf("\nmnemonic:RLC B\n");
            printf("**************************\n");
#endif
            RLC(B);
            break;

        case 0x01://RLC C

#ifdef DEBUG
            printf("\nmnemonic:RLC C\n");
            printf("**************************\n");
#endif
            RLC(C);
            break;

        case 0x02://RLC D

#ifdef DEBUG
            printf("\nmnemonic:RLC D\n");
            printf("**************************\n");
#endif
            RLC(D);
            break;

        case 0x03://RLC E

#ifdef DEBUG
            printf("\nmnemonic:RLC E\n");
            printf("**************************\n");
#endif
            RLC(E);
            break;

        case 0x04://RLC H

#ifdef DEBUG
            printf("\nmnemonic:RLC H\n");
            printf("**************************\n");
#endif
            RLC(H);
            break;

        case 0x05://RLC L

#ifdef DEBUG
            printf("\nmnemonic:RLC L\n");
            printf("**************************\n");
#endif
            RLC (L);
            break;

        case 0x06://RLC (HL)
            tempbyte=readMem(HL);
            RLC(tempbyte);
            writeMem(HL,tempbyte);
#ifdef DEBUG
            printf("\nmnemonic:RLC (HL)\n");
            printf("**************************\n");
#endif
            break;

        case 0x07: //RLC A

#ifdef DEBUG
            printf("\nmnemonic:RLC A\n");
            printf("**************************\n");
#endif
            RLC (A);
            break;

            /*RL   r*/
        case 0x10: //RL B

#ifdef DEBUG
            printf("\nmnemonic:RL B\n");
            printf("**************************\n");
#endif
            RL(B);
            break;

        case 0x11://RL C

#ifdef DEBUG
            printf("\nmnemonic:RL C\n");
            printf("**************************\n");
#endif
            RL(C);
            break;

        case 0x12://RL D

#ifdef DEBUG
            printf("\nmnemonic:RL D\n");
            printf("**************************\n");
#endif
            RL(D);
            break;

        case 0x13://RL E

#ifdef DEBUG
            printf("\nmnemonic:RL E\n");
            printf("**************************\n");
#endif
            RL(E);
            break;

        case 0x14://RL H

#ifdef DEBUG
            printf("\nmnemonic:RL H\n");
            printf("**************************\n");
#endif
            RL(H);
            break;

        case 0x15://RL L

#ifdef DEBUG
            printf("\nmnemonic:RL L\n");
            printf("**************************\n");
#endif
            RL(L);
            break;

        case 0x16://RL (HL)
            tempbyte=readMem(HL);
            RL(tempbyte);
            writeMem(HL,tempbyte);
#ifdef DEBUG
            printf("\nmnemonic:RL (HL)\n");
            printf("**************************\n");
#endif
            break;

        case 0x17://RL A

#ifdef DEBUG
            printf("\nmnemonic:RL A\n");
            printf("**************************\n");
#endif
            RL(A);
            break;

            /*RRC r*/
        case 0x08: //RRC B

#ifdef DEBUG
            printf("\nmnemonic:RRC B\n");
            printf("**************************\n");
#endif
            RRC(B);
            break;

        case 0x09://RRC C

#ifdef DEBUG
            printf("\nmnemonic:RRC C\n");
            printf("**************************\n");
#endif
            RRC(C);
            break;

        case 0x0A://RRC D

#ifdef DEBUG
            printf("\nmnemonic:RRC D\n");
            printf("**************************\n");
#endif
            RRC(D);
            break;

        case 0x0B://RRC E

#ifdef DEBUG
            printf("\nmnemonic:RRC E\n");
            printf("**************************\n");
#endif
            RRC(E);
            break;

        case 0x0C://RRC H

#ifdef DEBUG
            printf("\nmnemonic:RRC H\n");
            printf("**************************\n");
#endif
            RRC(H);
            break;

        case 0x0D://RRC L

#ifdef DEBUG
            printf("\nmnemonic:RRC L\n");
            printf("**************************\n");
#endif
            RRC (L);
            break;

        case 0x0E://RRC (HL)
            tempbyte=readMem(HL);
            RRC(tempbyte);
            writeMem(HL,tempbyte);
#ifdef DEBUG
            printf("\nmnemonic:RRC (HL)\n");
            printf("**************************\n");
#endif
            break;

        case 0x0F: //RRC A

#ifdef DEBUG
            printf("\nmnemonic:RRC A\n");
            printf("**************************\n");
#endif
            RRC (A);
            break;


            /*RR r*/
        case 0x18: //RR B

#ifdef DEBUG
            printf("\nmnemonic:RR B\n");
            printf("**************************\n");
#endif
            RR(B);
            break;

        case 0x19://RR C

#ifdef DEBUG
            printf("\nmnemonic:RR C\n");
            printf("**************************\n");
#endif
            RR(C);
            break;

        case 0x1A://RR D

#ifdef DEBUG
            printf("\nmnemonic:RR D\n");
            printf("**************************\n");
#endif
            RR(D);
            break;

        case 0x1B://RR E

#ifdef DEBUG
            printf("\nmnemonic:RR E\n");
            printf("**************************\n");
#endif
            RR(E);
            break;

        case 0x1C://RR H

#ifdef DEBUG
            printf("\nmnemonic:RR H\n");
            printf("**************************\n");
#endif
            RR(H);
            break;

        case 0x1D://RR L

#ifdef DEBUG
            printf("\nmnemonic:RR L\n");
            printf("**************************\n");
#endif
            RR (L);
            break;

        case 0x1E://RR (HL)
            tempbyte=readMem(HL);
            RR(tempbyte);
            writeMem(HL,tempbyte);
#ifdef DEBUG
            printf("\nmnemonic:RR (HL)\n");
            printf("**************************\n");
#endif
            break;

        case 0x1F: //RR A

#ifdef DEBUG
            printf("\nmnemonic:RR A\n");
            printf("**************************\n");
#endif
            RR (A);
            break;

            /*SLA r*/
        case 0x20: //SLA B

#ifdef DEBUG
            printf("\nmnemonic:SLA B\n");
            printf("**************************\n");
#endif
            SLA(B);
            break;

        case 0x21://SLA C

#ifdef DEBUG
            printf("\nmnemonic:SLA C\n");
            printf("**************************\n");
#endif
            SLA(C);
            break;

        case 0x22://SLA D

#ifdef DEBUG
            printf("\nmnemonic:SLA D\n");
            printf("**************************\n");
#endif
            SLA(D);
            break;

        case 0x23://SLA E

#ifdef DEBUG
            printf("\nmnemonic:SLA E\n");
            printf("**************************\n");
#endif
            SLA(E);
            break;

        case 0x24://SLA H

#ifdef DEBUG
            printf("\nmnemonic:SLA H\n");
            printf("**************************\n");
#endif
            SLA(H);
            break;

        case 0x25://SLA L

#ifdef DEBUG
            printf("\nmnemonic:SLA L\n");
            printf("**************************\n");
#endif
            SLA (L);
            break;

        case 0x26://SLA (HL)
            tempbyte=readMem(HL);
            SLA(tempbyte);
            writeMem(HL,tempbyte);
#ifdef DEBUG
            printf("\nmnemonic:SLA (HL)\n");
            printf("**************************\n");
#endif
            break;

        case 0x27: //SLA A

#ifdef DEBUG
            printf("\nmnemonic:SLA A\n");
            printf("**************************\n");
#endif
            SLA (A);
            break;

            /*SRA r*/
        case 0x28: //SRA B

#ifdef DEBUG
            printf("\nmnemonic:SRA B\n");
            printf("**************************\n");
#endif
            SRA(B);
            break;

        case 0x29://SRA C

#ifdef DEBUG
            printf("\nmnemonic:SRA C\n");
            printf("**************************\n");
#endif
            SRA(C);
            break;

        case 0x2A://SRA D

#ifdef DEBUG
            printf("\nmnemonic:SRA D\n");
            printf("**************************\n");
#endif
            SRA(D);
            break;

        case 0x2B://SRA E

#ifdef DEBUG
            printf("\nmnemonic:SRA E\n");
            printf("**************************\n");
#endif
            SRA(E);
            break;

        case 0x2C://SRA H

#ifdef DEBUG
            printf("\nmnemonic:SRA H\n");
            printf("**************************\n");
#endif
            SRA(H);
            break;

        case 0x2D://SRA L

#ifdef DEBUG
            printf("\nmnemonic:SRA L\n");
            printf("**************************\n");
#endif
            SRA (L);
            break;

            case 0x2E://SRA (HL)
                tempbyte=readMem(HL);
                SRA(tempbyte);
                writeMem(HL,tempbyte);
#ifdef DEBUG
            printf("\nmnemonic:SRA (HL)\n");
            printf("**************************\n");
#endif
                break;

            case 0x2F: //SRA A

#ifdef DEBUG
                printf("\nmnemonic:SRA A\n");
                printf("**************************\n");
#endif
                SRA (A);
                break;

                /*SRL r*/
            case 0x38: //SRL B

#ifdef DEBUG
                printf("\nmnemonic:SRL B\n");
                printf("**************************\n");
#endif
                SRL(B);
                break;

            case 0x39://SRL C

#ifdef DEBUG
                printf("\nmnemonic:SRL C\n");
                printf("**************************\n");
#endif
                SRL(C);
                break;

            case 0x3A://SRL D

#ifdef DEBUG
                printf("\nmnemonic:SRL D\n");
                printf("**************************\n");
#endif
                SRL(D);
                break;

            case 0x3B://SRL E

#ifdef DEBUG
                printf("\nmnemonic:SRL E\n");
                printf("**************************\n");
#endif
                SRL(E);
                break;

            case 0x3C://SRL H

#ifdef DEBUG
                printf("\nmnemonic:SRL H\n");
                printf("**************************\n");
#endif
                SRL(H);
                break;

            case 0x3D://SRL L

#ifdef DEBUG
                printf("\nmnemonic:SRL L\n");
                printf("**************************\n");
#endif
                SRL (L);
                break;

            case 0x3E://SRL (HL)
                tempbyte=readMem(HL);
                SRL(tempbyte);
                writeMem(HL,tempbyte);
#ifdef DEBUG
            printf("\nmnemonic:SRL (HL)\n");
            printf("**************************\n");
#endif
                break;

            case 0x3F: //SRL A

#ifdef DEBUG
                printf("\nmnemonic:SRL A\n");
                printf("**************************\n");
#endif
                SRL (A);
                break;

                /*SWAP r*/
            case 0x30: //SWAP B

#ifdef DEBUG
                printf("\nmnemonic:SWAP B\n");
                printf("**************************\n");
#endif
                SWAP(B);
                break;

            case 0x31://SWAP C

#ifdef DEBUG
                printf("\nmnemonic:SWAP C\n");
                printf("**************************\n");
#endif
                SWAP(C);
                break;

            case 0x32://SWAP D

#ifdef DEBUG
                printf("\nmnemonic:SWAP D\n");
                printf("**************************\n");
#endif
                SWAP(D);
                break;

            case 0x33://SWAP E

#ifdef DEBUG
                printf("\nmnemonic:SWAP E\n");
                printf("**************************\n");
#endif
                SWAP(E);
                break;

            case 0x34://SWAP H

#ifdef DEBUG
                printf("\nmnemonic:SWAP H\n");
                printf("**************************\n");
#endif
                SWAP(H);
                break;

            case 0x35://SWAP L

#ifdef DEBUG
                printf("\nmnemonic:SWAP L\n");
                printf("**************************\n");
#endif
                SWAP (L);
                break;

            case 0x36://SWAP (HL)
                tempbyte=readMem(HL);
                SWAP(tempbyte);
                writeMem(HL,tempbyte);
#ifdef DEBUG
            printf("\nmnemonic:SWAP (HL)\n");
            printf("**************************\n");
#endif
                break;

            case 0x37: //SWAP A

#ifdef DEBUG
                printf("\nmnemonic:SWAP A\n");
                printf("**************************\n");
#endif
                SWAP (A);
                break;

                /***bit opcodes**/

                /*BIT b,r*/
            case 0x40: //BIT 0,B

#ifdef DEBUG
                printf("\nmnemonic:BIT 0,B\n");
                printf("**************************\n");
#endif
                BIT(0,B);
                break;
            case 0x41: //BIT 0,C

#ifdef DEBUG
                printf("\nmnemonic:BIT 0,C\n");
                printf("**************************\n");
#endif
                BIT(0,C);
                break;
            case 0x42: //BIT 0,D

#ifdef DEBUG
                printf("\nmnemonic:BIT 0,D\n");
                printf("**************************\n");
#endif
                BIT(0,D);
                break;
            case 0x43: //BIT 0,E

#ifdef DEBUG
                printf("\nmnemonic:BIT 0,E\n");
                printf("**************************\n");
#endif
                BIT(0,E);
                break;
            case 0x44: //BIT 0,H

#ifdef DEBUG
                printf("\nmnemonic:BIT 0,H\n");
                printf("**************************\n");
#endif
                BIT(0,H);
                break;
            case 0x45: //BIT 0,L

#ifdef DEBUG
                printf("\nmnemonic:BIT 0,L\n");
                printf("**************************\n");
#endif
                BIT(0,L);
                break;
            case 0x47: //BIT 0,A

#ifdef DEBUG
                printf("\nmnemonic:BIT 0,A\n");
                printf("**************************\n");
#endif
                BIT(0,A);
                break;
            case 0x48: //BIT 1,B

#ifdef DEBUG
                printf("\nmnemonic:BIT 1,B\n");
                printf("**************************\n");
#endif
                BIT(1,B);
                break;
            case 0x49: //BIT 1,C

#ifdef DEBUG
                printf("\nmnemonic:BIT 1,C\n");
                printf("**************************\n");
#endif
                BIT(1,C);
                break;
            case 0x4A: //BIT 1,D

#ifdef DEBUG
                printf("\nmnemonic:BIT 1,D\n");
                printf("**************************\n");
#endif
                BIT(1,D);
                break;
            case 0x4B: //BIT 1,E

#ifdef DEBUG
                printf("\nmnemonic:BIT 1,E\n");
                printf("**************************\n");
#endif
                BIT(1,E);
                break;
            case 0x4C: //BIT 1,H

#ifdef DEBUG
                printf("\nmnemonic:BIT 1,H\n");
                printf("**************************\n");
#endif
                BIT(1,H);
                break;
            case 0x4D: //BIT 1,L

#ifdef DEBUG
                printf("\nmnemonic:BIT 1,L\n");
                printf("**************************\n");
#endif
                BIT(1,L);
                break;
            case 0x4F: //BIT 1,A

#ifdef DEBUG
                printf("\nmnemonic:BIT 1,A\n");
                printf("**************************\n");
#endif
                BIT(1,A);
                break;
            case 0x50: //BIT 2,B

#ifdef DEBUG
                printf("\nmnemonic:BIT 2,B\n");
                printf("**************************\n");
#endif
                BIT(2,B);
                break;
            case 0x51: //BIT 2,C

#ifdef DEBUG
                printf("\nmnemonic:BIT 2,C\n");
                printf("**************************\n");
#endif
                BIT(2,C);
                break;
            case 0x52: //BIT 2,D

#ifdef DEBUG
                printf("\nmnemonic:BIT 2,D\n");
                printf("**************************\n");
#endif
                BIT(2,D);
                break;
            case 0x53: //BIT 2,E

#ifdef DEBUG
                printf("\nmnemonic:BIT 2,E\n");
                printf("**************************\n");
#endif
                BIT(2,E);
                break;
            case 0x54: //BIT 2,H

#ifdef DEBUG
                printf("\nmnemonic:BIT 2,H\n");
                printf("**************************\n");
#endif
                BIT(2,H);
                break;
            case 0x55: //BIT 2,L

#ifdef DEBUG
                printf("\nmnemonic:BIT 2,L\n");
                printf("**************************\n");
#endif
                BIT(2,L);
                break;
            case 0x57: //BIT 2,A

#ifdef DEBUG
                printf("\nmnemonic:BIT 2,A\n");
                printf("**************************\n");
#endif
                BIT(2,A);
                break;
            case 0x58: //BIT 3,B

#ifdef DEBUG
                printf("\nmnemonic:BIT 3,B\n");
                printf("**************************\n");
#endif
                BIT(3,B);
                break;
            case 0x59: //BIT 3,C

#ifdef DEBUG
                printf("\nmnemonic:BIT 3,C\n");
                printf("**************************\n");
#endif
                BIT(3,C);
                break;
            case 0x5A: //BIT 3,D

#ifdef DEBUG
                printf("\nmnemonic:BIT 3,D\n");
                printf("**************************\n");
#endif
                BIT(3,D);
                break;
            case 0x5B: //BIT 3,E

#ifdef DEBUG
                printf("\nmnemonic:BIT 3,E\n");
                printf("**************************\n");
#endif
                BIT(3,E);
                break;
            case 0x5C: //BIT 3,H

#ifdef DEBUG
                printf("\nmnemonic:BIT 3,H\n");
                printf("**************************\n");
#endif
                BIT(3,H);
                break;
            case 0x5D: //BIT 3,L

#ifdef DEBUG
                printf("\nmnemonic:BIT 3,L\n");
                printf("**************************\n");
#endif
                BIT(3,L);
                break;
            case 0x5F: //BIT 3,A

#ifdef DEBUG
                printf("\nmnemonic:BIT 3,A\n");
                printf("**************************\n");
#endif
                BIT(3,A);
                break;
            case 0x60: //BIT 4,B

#ifdef DEBUG
                printf("\nmnemonic:BIT 4,B\n");
                printf("**************************\n");
#endif
                BIT(4,B);
                break;
            case 0x61: //BIT 4,C

#ifdef DEBUG
                printf("\nmnemonic:BIT 4,C\n");
                printf("**************************\n");
#endif
                BIT(4,C);
                break;
            case 0x62: //BIT 4,D

#ifdef DEBUG
                printf("\nmnemonic:BIT 4,D\n");
                printf("**************************\n");
#endif
                BIT(4,D);
                break;
            case 0x63: //BIT 4,E

#ifdef DEBUG
                printf("\nmnemonic:BIT 4,E\n");
                printf("**************************\n");
#endif
                BIT(4,E);
                break;
            case 0x64: //BIT 4,H

#ifdef DEBUG
                printf("\nmnemonic:BIT 4,H\n");
                printf("**************************\n");
#endif
                BIT(4,H);
                break;
            case 0x65: //BIT 4,L

#ifdef DEBUG
                printf("\nmnemonic:BIT 4,L\n");
                printf("**************************\n");
#endif
                BIT(4,L);
                break;
            case 0x67: //BIT 4,A

#ifdef DEBUG
                printf("\nmnemonic:BIT 4,A\n");
                printf("**************************\n");
#endif
                BIT(4,A);
                break;
            case 0x68: //BIT 5,B

#ifdef DEBUG
                printf("\nmnemonic:BIT 5,B\n");
                printf("**************************\n");
#endif
                BIT(5,B);
                break;
            case 0x69: //BIT 5,C

#ifdef DEBUG
                printf("\nmnemonic:BIT 5,C\n");
                printf("**************************\n");
#endif
                BIT(5,C);
                break;
            case 0x6A: //BIT 5,D

#ifdef DEBUG
                printf("\nmnemonic:BIT 5,D\n");
                printf("**************************\n");
#endif
                BIT(5,D);
                break;
            case 0x6B: //BIT 5,E

#ifdef DEBUG
                printf("\nmnemonic:BIT 5,E\n");
                printf("**************************\n");
#endif
                BIT(5,E);
                break;
            case 0x6C: //BIT 5,H

#ifdef DEBUG
                printf("\nmnemonic:BIT 5,H\n");
                printf("**************************\n");
#endif
                BIT(5,H);
                break;
            case 0x6D: //BIT 5,L

#ifdef DEBUG
                printf("\nmnemonic:BIT 5,L\n");
                printf("**************************\n");
#endif
                BIT(5,L);
                break;
            case 0x6F: //BIT 5,A

#ifdef DEBUG
                printf("\nmnemonic:BIT 5,A\n");
                printf("**************************\n");
#endif
                BIT(5,A);
                break;
            case 0x70: //BIT 6,B

#ifdef DEBUG
                printf("\nmnemonic:BIT 6,B\n");
                printf("**************************\n");
#endif
                BIT(6,B);
                break;
            case 0x71: //BIT 6,C

#ifdef DEBUG
                printf("\nmnemonic:BIT 6,C\n");
                printf("**************************\n");
#endif
                BIT(6,C);
                break;
            case 0x72: //BIT 6,D

#ifdef DEBUG
                printf("\nmnemonic:BIT 6,D\n");
                printf("**************************\n");
#endif
                BIT(6,D);
                break;
            case 0x73: //BIT 6,E

#ifdef DEBUG
                printf("\nmnemonic:BIT 6,E\n");
                printf("**************************\n");
#endif
                BIT(6,E);
                break;
            case 0x74: //BIT 6,H

#ifdef DEBUG
                printf("\nmnemonic:BIT 6,H\n");
                printf("**************************\n");
#endif
                BIT(6,H);
                break;
            case 0x75: //BIT 6,L

#ifdef DEBUG
                printf("\nmnemonic:BIT 6,L\n");
                printf("**************************\n");
#endif
                BIT(6,L);
                break;
            case 0x77: //BIT 6,A

#ifdef DEBUG
                printf("\nmnemonic:BIT 6,A\n");
                printf("**************************\n");
#endif
                BIT(6,A);
                break;
            case 0x78: //BIT 7,B

#ifdef DEBUG
                printf("\nmnemonic:BIT 7,B\n");
                printf("**************************\n");
#endif
                BIT(7,B);
                break;
            case 0x79: //BIT 7,C

#ifdef DEBUG
                printf("\nmnemonic:BIT 7,C\n");
                printf("**************************\n");
#endif
                BIT(7,C);
                break;
            case 0x7A: //BIT 7,D

#ifdef DEBUG
                printf("\nmnemonic:BIT 7,D\n");
                printf("**************************\n");
#endif
                BIT(7,D);
                break;
            case 0x7B: //BIT 7,E

#ifdef DEBUG
                printf("\nmnemonic:BIT 7,E\n");
                printf("**************************\n");
#endif
                BIT(7,E);
                break;
            case 0x7C: //BIT 7,H

#ifdef DEBUG
                printf("\nmnemonic:BIT 7,H\n");
                printf("**************************\n");
#endif
                BIT(7,H);
                break;
            case 0x7D: //BIT 7,L

#ifdef DEBUG
                printf("\nmnemonic:BIT 7,L\n");
                printf("**************************\n");
#endif
                BIT(7,L);
                break;
            case 0x7F: //BIT 7,A

#ifdef DEBUG
                printf("\nmnemonic:BIT 7,A\n");
                printf("**************************\n");
#endif
                BIT(7,A);
                break;

            case 0x46: //BIT 0,(HL)
#ifdef DEBUG
                printf("\nmnemonic:BIT 0,(HL)\n");
                printf("**************************\n");
#endif

                tempbyte=readMem(HL);
                BIT(0,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0x4E: //BIT 1,(HL)
#ifdef DEBUG
                printf("\nmnemonic:BIT 1,(HL)\n");
                printf("**************************\n");
#endif

                tempbyte=readMem(HL);
                BIT(1,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0x56: //BIT 2,(HL)
#ifdef DEBUG
                printf("\nmnemonic:BIT 2,(HL)\n");
                printf("**************************\n");
#endif

                tempbyte=readMem(HL);
                BIT(2,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0x5E: //BIT 3,(HL)
#ifdef DEBUG
                printf("\nmnemonic:BIT 3,(HL)\n");
                printf("**************************\n");
#endif

                tempbyte=readMem(HL);
                BIT(3,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0x66: //BIT 4,(HL)
#ifdef DEBUG
                printf("\nmnemonic:BIT 4,(HL)\n");
                printf("**************************\n");
#endif

                tempbyte=readMem(HL);
                BIT(4,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0x6E: //BIT 5,(HL)
#ifdef DEBUG
                printf("\nmnemonic:BIT 5,(HL)\n");
                printf("**************************\n");
#endif

                tempbyte=readMem(HL);
                BIT(5,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0x76: //BIT 6,(HL)
#ifdef DEBUG
                printf("\nmnemonic:BIT 6,(HL)\n");
                printf("**************************\n");
#endif

                tempbyte=readMem(HL);
                BIT(6,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0x7E: //BIT 7,(HL)
#ifdef DEBUG
                printf("\nmnemonic:BIT 7,(HL)\n");
                printf("**************************\n");
#endif

                tempbyte=readMem(HL);
                BIT(7,tempbyte);
                writeMem(HL,tempbyte);
                break;

                /*SET b,r */
            case  0xC0://SET 0,B

#ifdef DEBUG
                printf("\nmnemonic:SET 0,B\n");
                printf("**************************\n");
#endif
                SET(0,B);
                break;
            case  0xC1://SET 0,C

#ifdef DEBUG
                printf("\nmnemonic:SET 0,C\n");
                printf("**************************\n");
#endif
                SET(0,C);
                break;
            case  0xC2://SET 0,D

#ifdef DEBUG
                printf("\nmnemonic:SET 0,D\n");
                printf("**************************\n");
#endif
                SET(0,D);
                break;
            case  0xC3://SET 0,E

#ifdef DEBUG
                printf("\nmnemonic:SET 0,E\n");
                printf("**************************\n");
#endif
                SET(0,E);
                break;
            case  0xC4://SET 0,H

#ifdef DEBUG
                printf("\nmnemonic:SET 0,H\n");
                printf("**************************\n");
#endif
                SET(0,H);
                break;
            case  0xC5://SET 0,L

#ifdef DEBUG
                printf("\nmnemonic:SET 0,L\n");
                printf("**************************\n");
#endif
                SET(0,L);
                break;
            case  0xC6://SET 0,(HL)

#ifdef DEBUG
                printf("\nmnemonic:SET 0,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                SET(0,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case  0xC7://SET 0,A

#ifdef DEBUG
                printf("\nmnemonic:SET 0,A\n");
                printf("**************************\n");
#endif
                SET(0,A);
                break;
            case  0xC8://SET 1,B

#ifdef DEBUG
                printf("\nmnemonic:SET 1,B\n");
                printf("**************************\n");
#endif
                SET(1,B);
                break;
            case  0xC9://SET 1,C

#ifdef DEBUG
                printf("\nmnemonic:SET 1,C\n");
                printf("**************************\n");
#endif
                SET(1,C);
                break;
            case  0xCA://SET 1,D

#ifdef DEBUG
                printf("\nmnemonic:SET 1,D\n");
                printf("**************************\n");
#endif
                SET(1,D);
                break;
            case  0xCB://SET 1,E

#ifdef DEBUG
                printf("\nmnemonic:SET 1,E\n");
                printf("**************************\n");
#endif
                SET(1,E);
                break;
            case  0xCC://SET 1,H

#ifdef DEBUG
                printf("\nmnemonic:SET 1,H\n");
                printf("**************************\n");
#endif
                SET(1,H);
                break;
            case  0xCD://SET 1,L

#ifdef DEBUG
                printf("\nmnemonic:SET 1,L\n");
                printf("**************************\n");
#endif
                SET(1,L);
                break;
            case  0xCE://SET 1,(HL)

#ifdef DEBUG
                printf("\nmnemonic:SET 1,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                SET(1,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case  0xCF://SET 1,A

#ifdef DEBUG
                printf("\nmnemonic:SET 1,A\n");
                printf("**************************\n");
#endif
                SET(1,A);
                break;
            case  0xD0://SET 2,B

#ifdef DEBUG
                printf("\nmnemonic:SET 2,B\n");
                printf("**************************\n");
#endif
                SET(2,B);
                break;
            case  0xD1://SET 2,C

#ifdef DEBUG
                printf("\nmnemonic:SET 2,C\n");
                printf("**************************\n");
#endif
                SET(2,C);
                break;
            case  0xD2://SET 2,D

#ifdef DEBUG
                printf("\nmnemonic:SET 2,D\n");
                printf("**************************\n");
#endif
                SET(2,D);
                break;
            case  0xD3://SET 2,E

#ifdef DEBUG
                printf("\nmnemonic:SET 2,E\n");
                printf("**************************\n");
#endif
                SET(2,E);
                break;
            case  0xD4://SET 2,H

#ifdef DEBUG
                printf("\nmnemonic:SET 2,H\n");
                printf("**************************\n");
#endif
                SET(2,H);
                break;
            case  0xD5://SET 2,L

#ifdef DEBUG
                printf("\nmnemonic:SET 2,L\n");
                printf("**************************\n");
#endif
                SET(2,L);
                break;
            case  0xD6://SET 2,(HL)

#ifdef DEBUG
                printf("\nmnemonic:SET 2,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                SET(2,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case  0xD7://SET 2,A

#ifdef DEBUG
                printf("\nmnemonic:SET 2,A\n");
                printf("**************************\n");
#endif
                SET(2,A);
                break;
            case  0xD8://SET 3,B

#ifdef DEBUG
                printf("\nmnemonic:SET 3,B\n");
                printf("**************************\n");
#endif
                SET(3,B);
                break;
            case  0xD9://SET 3,C

#ifdef DEBUG
                printf("\nmnemonic:SET 3,C\n");
                printf("**************************\n");
#endif
                SET(3,C);
                break;
            case  0xDA://SET 3,D

#ifdef DEBUG
                printf("\nmnemonic:SET 3,D\n");
                printf("**************************\n");
#endif
                SET(3,D);
                break;
            case  0xDB://SET 3,E

#ifdef DEBUG
                printf("\nmnemonic:SET 3,E\n");
                printf("**************************\n");
#endif
                SET(3,E);
                break;
            case  0xDC://SET 3,H

#ifdef DEBUG
                printf("\nmnemonic:SET 3,H\n");
                printf("**************************\n");
#endif
                SET(3,H);
                break;
            case  0xDD://SET 3,L

#ifdef DEBUG
                printf("\nmnemonic:SET 3,L\n");
                printf("**************************\n");
#endif
                SET(3,L);
                break;
            case  0xDE://SET 3,(HL)

#ifdef DEBUG
                printf("\nmnemonic:SET 3,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                SET(3,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case  0xDF://SET 3,A

#ifdef DEBUG
                printf("\nmnemonic:SET 3,A\n");
                printf("**************************\n");
#endif
                SET(3,A);
                break;
            case  0xE0://SET 4,B

#ifdef DEBUG
                printf("\nmnemonic:SET 4,B\n");
                printf("**************************\n");
#endif
                SET(4,B);
                break;
            case  0xE1://SET 4,C

#ifdef DEBUG
                printf("\nmnemonic:SET 4,C\n");
                printf("**************************\n");
#endif
                SET(4,C);
                break;
            case  0xE2://SET 4,D

#ifdef DEBUG
                printf("\nmnemonic:SET 4,D\n");
                printf("**************************\n");
#endif
                SET(4,D);
                break;
            case  0xE3://SET 4,E

#ifdef DEBUG
                printf("\nmnemonic:SET 4,E\n");
                printf("**************************\n");
#endif
                SET(4,E);
                break;
            case  0xE4://SET 4,H

#ifdef DEBUG
                printf("\nmnemonic:SET 4,H\n");
                printf("**************************\n");
#endif
                SET(4,H);
                break;
            case  0xE5://SET 4,L

#ifdef DEBUG
                printf("\nmnemonic:SET 4,L\n");
                printf("**************************\n");
#endif
                SET(4,L);
                break;
            case  0xE6://SET 4,(HL)

#ifdef DEBUG
                printf("\nmnemonic:SET 4,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                SET(4,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case  0xE7://SET 4,A

#ifdef DEBUG
                printf("\nmnemonic:SET 4,A\n");
                printf("**************************\n");
#endif
                SET(4,A);
                break;
            case  0xE8://SET 5,B

#ifdef DEBUG
                printf("\nmnemonic:SET 5,B\n");
                printf("**************************\n");
#endif
                SET(5,B);
                break;
            case  0xE9://SET 5,C

#ifdef DEBUG
                printf("\nmnemonic:SET 5,C\n");
                printf("**************************\n");
#endif
                SET(5,C);
                break;
            case  0xEA://SET 5,D

#ifdef DEBUG
                printf("\nmnemonic:SET 5,D\n");
                printf("**************************\n");
#endif
                SET(5,D);
                break;
            case  0xEB://SET 5,E

#ifdef DEBUG
                printf("\nmnemonic:SET 5,E\n");
                printf("**************************\n");
#endif
                SET(5,E);
                break;
            case  0xEC://SET 5,H

#ifdef DEBUG
                printf("\nmnemonic:SET 5,H\n");
                printf("**************************\n");
#endif
                SET(5,H);
                break;
            case  0xED://SET 5,L

#ifdef DEBUG
                printf("\nmnemonic:SET 5,L\n");
                printf("**************************\n");
#endif
                SET(5,L);
                break;
            case  0xEE://SET 5,(HL)

#ifdef DEBUG
                printf("\nmnemonic:SET 5,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                SET(5,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case  0xEF://SET 5,A

#ifdef DEBUG
                printf("\nmnemonic:SET 5,A\n");
                printf("**************************\n");
#endif
                SET(5,A);
                break;
            case  0xF0://SET 6,B

#ifdef DEBUG
                printf("\nmnemonic:SET 6,B\n");
                printf("**************************\n");
#endif
                SET(6,B);
                break;
            case  0xF1://SET 6,C

#ifdef DEBUG
                printf("\nmnemonic:SET 6,C\n");
                printf("**************************\n");
#endif
                SET(6,C);
                break;
            case  0xF2://SET 6,D

#ifdef DEBUG
                printf("\nmnemonic:SET 6,D\n");
                printf("**************************\n");
#endif
                SET(6,D);
                break;
            case  0xF3://SET 6,E

#ifdef DEBUG
                printf("\nmnemonic:SET 6,E\n");
                printf("**************************\n");
#endif
                SET(6,E);
                break;
            case  0xF4://SET 6,H

#ifdef DEBUG
                printf("\nmnemonic:SET 6,H\n");
                printf("**************************\n");
#endif
                SET(6,H);
                break;
            case  0xF5://SET 6,L

#ifdef DEBUG
                printf("\nmnemonic:SET 6,L\n");
                printf("**************************\n");
#endif
                SET(6,L);
                break;
            case  0xF6://SET 6,(HL)

#ifdef DEBUG
                printf("\nmnemonic:SET 6,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                SET(6,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case  0xF7://SET 6,A

#ifdef DEBUG
                printf("\nmnemonic:SET 6,A\n");
                printf("**************************\n");
#endif
                SET(6,A);
                break;
            case  0xF8://SET 7,B

#ifdef DEBUG
                printf("\nmnemonic:SET 7,B\n");
                printf("**************************\n");
#endif
                SET(7,B);
                break;
            case  0xF9://SET 7,C

#ifdef DEBUG
                printf("\nmnemonic:SET 7,C\n");
                printf("**************************\n");
#endif
                SET(7,C);
                break;
            case  0xFA://SET 7,D

#ifdef DEBUG
                printf("\nmnemonic:SET 7,D\n");
                printf("**************************\n");
#endif
                SET(7,D);
                break;
            case  0xFB://SET 7,E

#ifdef DEBUG
                printf("\nmnemonic:SET 7,E\n");
                printf("**************************\n");
#endif
                SET(7,E);
                break;
            case  0xFC://SET 7,H

#ifdef DEBUG
                printf("\nmnemonic:SET 7,H\n");
                printf("**************************\n");
#endif
                SET(7,H);
                break;
            case  0xFD://SET 7,L

#ifdef DEBUG
                printf("\nmnemonic:SET 7,L\n");
                printf("**************************\n");
#endif
                SET(7,L);
                break;
            case  0xFE://SET 7,(HL)

#ifdef DEBUG
                printf("\nmnemonic:SET 7,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                SET(7,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case  0xFF://SET 7,A

#ifdef DEBUG
                printf("\nmnemonic:SET 7,A\n");
                printf("**************************\n");
#endif
                SET(7,A);
                break;

                /*RES b,r*/
            case 0x80://RES 0,B

#ifdef DEBUG
                printf("\nmnemonic:RES 0,B\n");
                printf("**************************\n");
#endif
                RES(0,B);
                break;
            case 0x81://RES 0,C

#ifdef DEBUG
                printf("\nmnemonic:RES 0,C\n");
                printf("**************************\n");
#endif
                RES(0,C);
                break;
            case 0x82://RES 0,D

#ifdef DEBUG
                printf("\nmnemonic:RES 0,D\n");
                printf("**************************\n");
#endif
                RES(0,D);
                break;
            case 0x83://RES 0,E

#ifdef DEBUG
                printf("\nmnemonic:RES 0,E\n");
                printf("**************************\n");
#endif
                RES(0,E);
                break;
            case 0x84://RES 0,H

#ifdef DEBUG
                printf("\nmnemonic:RES 0,H\n");
                printf("**************************\n");
#endif
                RES(0,H);
                break;
            case 0x85://RES 0,L

#ifdef DEBUG
                printf("\nmnemonic:RES 0,L\n");
                printf("**************************\n");
#endif
                RES(0,L);
                break;
            case 0x86://RES 0,(HL)

#ifdef DEBUG
                printf("\nmnemonic:RES 0,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                RES(0,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0x87://RES 0,A

#ifdef DEBUG
                printf("\nmnemonic:RES 0,A\n");
                printf("**************************\n");
#endif
                RES(0,A);
                break;
            case 0x88://RES 1,B

#ifdef DEBUG
                printf("\nmnemonic:RES 1,B\n");
                printf("**************************\n");
#endif
                RES(1,B);
                break;
            case 0x89://RES 1,C

#ifdef DEBUG
                printf("\nmnemonic:RES 1,C\n");
                printf("**************************\n");
#endif
                RES(1,C);
                break;
            case 0x8A://RES 1,D

#ifdef DEBUG
                printf("\nmnemonic:RES 1,D\n");
                printf("**************************\n");
#endif
                RES(1,D);
                break;
            case 0x8B://RES 1,E

#ifdef DEBUG
                printf("\nmnemonic:RES 1,E\n");
                printf("**************************\n");
#endif
                RES(1,E);
                break;
            case 0x8C://RES 1,H

#ifdef DEBUG
                printf("\nmnemonic:RES 1,H\n");
                printf("**************************\n");
#endif
                RES(1,H);
                break;
            case 0x8D://RES 1,L

#ifdef DEBUG
                printf("\nmnemonic:RES 1,L\n");
                printf("**************************\n");
#endif
                RES(1,L);
                break;
            case 0x8E://RES 1,(HL)

#ifdef DEBUG
                printf("\nmnemonic:RES 1,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                RES(1,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0x8F://RES 1,A

#ifdef DEBUG
                printf("\nmnemonic:RES 1,A\n");
                printf("**************************\n");
#endif
                RES(1,A);
                break;
            case 0x90://RES 2,B

#ifdef DEBUG
                printf("\nmnemonic:RES 2,B\n");
                printf("**************************\n");
#endif
                RES(2,B);
                break;
            case 0x91://RES 2,C

#ifdef DEBUG
                printf("\nmnemonic:RES 2,C\n");
                printf("**************************\n");
#endif
                RES(2,C);
                break;
            case 0x92://RES 2,D

#ifdef DEBUG
                printf("\nmnemonic:RES 2,D\n");
                printf("**************************\n");
#endif
                RES(2,D);
                break;
            case 0x93://RES 2,E

#ifdef DEBUG
                printf("\nmnemonic:RES 2,E\n");
                printf("**************************\n");
#endif
                RES(2,E);
                break;
            case 0x94://RES 2,H

#ifdef DEBUG
                printf("\nmnemonic:RES 2,H\n");
                printf("**************************\n");
#endif
                RES(2,H);
                break;
            case 0x95://RES 2,L

#ifdef DEBUG
                printf("\nmnemonic:RES 2,L\n");
                printf("**************************\n");
#endif
                RES(2,L);
                break;
            case 0x96://RES 2,(HL)

#ifdef DEBUG
                printf("\nmnemonic:RES 2,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                RES(2,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0x97://RES 2,A

#ifdef DEBUG
                printf("\nmnemonic:RES 2,A\n");
                printf("**************************\n");
#endif
                RES(2,A);
                break;
            case 0x98://RES 3,B

#ifdef DEBUG
                printf("\nmnemonic:RES 3,B\n");
                printf("**************************\n");
#endif
                RES(3,B);
                break;
            case 0x99://RES 3,C

#ifdef DEBUG
                printf("\nmnemonic:RES 3,C\n");
                printf("**************************\n");
#endif
                RES(3,C);
                break;
            case 0x9A://RES 3,D

#ifdef DEBUG
                printf("\nmnemonic:RES 3,D\n");
                printf("**************************\n");
#endif
                RES(3,D);
                break;
            case 0x9B://RES 3,E

#ifdef DEBUG
                printf("\nmnemonic:RES 3,E\n");
                printf("**************************\n");
#endif
                RES(3,E);
                break;
            case 0x9C://RES 3,H

#ifdef DEBUG
                printf("\nmnemonic:RES 3,H\n");
                printf("**************************\n");
#endif
                RES(3,H);
                break;
            case 0x9D://RES 3,L

#ifdef DEBUG
                printf("\nmnemonic:RES 3,L\n");
                printf("**************************\n");
#endif
                RES(3,L);
                break;
            case 0x9E://RES 3,(HL)

#ifdef DEBUG
                printf("\nmnemonic:RES 3,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                RES(3,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0x9F://RES 3,A

#ifdef DEBUG
                printf("\nmnemonic:RES 3,A\n");
                printf("**************************\n");
#endif
                RES(3,A);
                break;
            case 0xA0://RES 4,B

#ifdef DEBUG
                printf("\nmnemonic:RES 4,B\n");
                printf("**************************\n");
#endif
                RES(4,B);
                break;
            case 0xA1://RES 4,C

#ifdef DEBUG
                printf("\nmnemonic:RES 4,C\n");
                printf("**************************\n");
#endif
                RES(4,C);
                break;
            case 0xA2://RES 4,D

#ifdef DEBUG
                printf("\nmnemonic:RES 4,D\n");
                printf("**************************\n");
#endif
                RES(4,D);
                break;
            case 0xA3://RES 4,E

#ifdef DEBUG
                printf("\nmnemonic:RES 4,E\n");
                printf("**************************\n");
#endif
                RES(4,E);
                break;
            case 0xA4://RES 4,H

#ifdef DEBUG
                printf("\nmnemonic:RES 4,H\n");
                printf("**************************\n");
#endif
                RES(4,H);
                break;
            case 0xA5://RES 4,L

#ifdef DEBUG
                printf("\nmnemonic:RES 4,L\n");
                printf("**************************\n");
#endif
                RES(4,L);
                break;
            case 0xA6://RES 4,(HL)

#ifdef DEBUG
                printf("\nmnemonic:RES 4,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                RES(4,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0xA7://RES 4,A

#ifdef DEBUG
                printf("\nmnemonic:RES 4,A\n");
                printf("**************************\n");
#endif
                RES(4,A);
                break;
            case 0xA8://RES 5,B

#ifdef DEBUG
                printf("\nmnemonic:RES 5,B\n");
                printf("**************************\n");
#endif
                RES(5,B);
                break;
            case 0xA9://RES 5,C

#ifdef DEBUG
                printf("\nmnemonic:RES 5,C\n");
                printf("**************************\n");
#endif
                RES(5,C);
                break;
            case 0xAA://RES 5,D

#ifdef DEBUG
                printf("\nmnemonic:RES 5,D\n");
                printf("**************************\n");
#endif
                RES(5,D);
                break;
            case 0xAB://RES 5,E

#ifdef DEBUG
                printf("\nmnemonic:RES 5,E\n");
                printf("**************************\n");
#endif
                RES(5,E);
                break;
            case 0xAC://RES 5,H

#ifdef DEBUG
                printf("\nmnemonic:RES 5,H\n");
                printf("**************************\n");
#endif
                RES(5,H);
                break;
            case 0xAD://RES 5,L

#ifdef DEBUG
                printf("\nmnemonic:RES 5,L\n");
                printf("**************************\n");
#endif
                RES(5,L);
                break;
            case 0xAE://RES 5,(HL)

#ifdef DEBUG
                printf("\nmnemonic:RES 5,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                RES(5,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0xAF://RES 5,A

#ifdef DEBUG
                printf("\nmnemonic:RES 5,A\n");
                printf("**************************\n");
#endif
                RES(5,A);
                break;
            case 0xB0://RES 6,B

#ifdef DEBUG
                printf("\nmnemonic:RES 6,B\n");
                printf("**************************\n");
#endif
                RES(6,B);
                break;
            case 0xB1://RES 6,C

#ifdef DEBUG
                printf("\nmnemonic:RES 6,C\n");
                printf("**************************\n");
#endif
                RES(6,C);
                break;
            case 0xB2://RES 6,D

#ifdef DEBUG
                printf("\nmnemonic:RES 6,D\n");
                printf("**************************\n");
#endif
                RES(6,D);
                break;
            case 0xB3://RES 6,E

#ifdef DEBUG
                printf("\nmnemonic:RES 6,E\n");
                printf("**************************\n");
#endif
                RES(6,E);
                break;
            case 0xB4://RES 6,H

#ifdef DEBUG
                printf("\nmnemonic:RES 6,H\n");
                printf("**************************\n");
#endif
                RES(6,H);
                break;
            case 0xB5://RES 6,L

#ifdef DEBUG
                printf("\nmnemonic:RES 6,L\n");
                printf("**************************\n");
#endif
                RES(6,L);
                break;
            case 0xB6://RES 6,(HL)

#ifdef DEBUG
                printf("\nmnemonic:RES 6,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                RES(6,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0xB7://RES 6,A

#ifdef DEBUG
                printf("\nmnemonic:RES 6,A\n");
                printf("**************************\n");
#endif
                RES(6,A);
                break;
            case 0xB8://RES 7,B

#ifdef DEBUG
                printf("\nmnemonic:RES 7,B\n");
                printf("**************************\n");
#endif
                RES(7,B);
                break;
            case 0xB9://RES 7,C

#ifdef DEBUG
                printf("\nmnemonic:RES 7,C\n");
                printf("**************************\n");
#endif
                RES(7,C);
                break;
            case 0xBA://RES 7,D

#ifdef DEBUG
                printf("\nmnemonic:RES 7,D\n");
                printf("**************************\n");
#endif
                RES(7,D);
                break;
            case 0xBB://RES 7,E

#ifdef DEBUG
                printf("\nmnemonic:RES 7,E\n");
                printf("**************************\n");
#endif
                RES(7,E);
                break;
            case 0xBC://RES 7,H

#ifdef DEBUG
                printf("\nmnemonic:RES 7,H\n");
                printf("**************************\n");
#endif
                RES(7,H);
                break;
            case 0xBD://RES 7,L

#ifdef DEBUG
                printf("\nmnemonic:RES 7,L\n");
                printf("**************************\n");
#endif
                RES(7,L);
                break;
            case 0xBE://RES 7,(HL)

#ifdef DEBUG
                printf("\nmnemonic:RES 7,(HL)\n");
                printf("**************************\n");
#endif
                tempbyte=readMem(HL);
                RES(7,tempbyte);
                writeMem(HL,tempbyte);
                break;
            case 0xBF://RES 7,A

#ifdef DEBUG
                printf("\nmnemonic:RES 7,A\n");
                printf("**************************\n");
#endif
                RES(7,A);
                break;
            default:
                break;
            }
        break;

        /*****************GMB Jumpcommands*********************/

        /*JP nn*/
            case 0xC3:
        //TODO: mudar para gbcpu.pc provavelmente
        opAux.Byte.l=readMem(pc++);
        opAux.Byte.h= readMem(pc);
        pc=opAux.Word;
#ifdef DEBUG
        printf(" %02x %02x",opAux.Byte.l, opAux.Byte.h);
        printf("\nmnemonic:JP %04x\n",opAux.Word);
        printf("**************************\n");
#endif
        break;

        /* JP (HL) */
            case 0xE9:
        pc=HL;
#ifdef DEBUG
        printf("\nmnemonic:JP (HL)\n");
        printf("**************************\n");
#endif
        break;

        //TODO : verificar pc++
        /*JP cc,nn*/
            case 0xC2: //JP  NZ,nn
#ifdef DEBUG
        printf(" %02x %02x",readMem(pc), readMem(pc+1));
        printf("\nmnemonic:JP NZ,%04x\n",readMem(pc)|(readMem(pc+1)<<8));
        printf("**************************\n");
#endif
                if ((F & Z_FLAG)==0 ) {
                    opAux.Byte.l=readMem(pc++);
                    opAux.Byte.h= readMem(pc++);
                    pc=opAux.Word;
                }else pc+=2;
                break;

            case 0xCA: //JP  Z,nn
#ifdef DEBUG
        printf(" %02x %02x",readMem(pc), readMem(pc+1));
        printf("\nmnemonic:JP Z,%04x\n",readMem(pc)|(readMem(pc+1)<<8));
        printf("**************************\n");
#endif
                if ((F & Z_FLAG)==1 ) {
                    opAux.Byte.l=readMem(pc++);
                    opAux.Byte.h= readMem(pc++);
                    pc=opAux.Word;
                }else pc+=2;

                break;

            case 0xD2: //JP  NC,nn
#ifdef DEBUG
        printf(" %02x %02x",readMem(pc), readMem(pc+1));
        printf("\nmnemonic:JP NC,%04x\n",readMem(pc)|(readMem(pc+1)<<8));
        printf("**************************\n");
#endif
                if ((F & C_FLAG)==0 ) {
                    opAux.Byte.l=readMem(pc++);
                    opAux.Byte.h= readMem(pc++);
                    pc=opAux.Word;
                }else pc+=2;

                break;

            case 0xDA: //JP  C,nn
#ifdef DEBUG
        printf(" %02x %02x",readMem(pc), readMem(pc+1));
        printf("\nmnemonic:JP C,%04x\n",readMem(pc)|(readMem(pc+1)<<8));
        printf("**************************\n");
#endif
                if ((F & C_FLAG)==1 ){
                    opAux.Byte.l=readMem(pc++);
                    opAux.Byte.h= readMem(pc++);
                    pc=opAux.Word;
                }else pc+=2;

                break;

                /*JR PC+dd*/
                //TODO: verificar range (pc++)
            case 0x18:
                signedtempbyte = readMem(pc++);
                pc += signedtempbyte;
#ifdef DEBUG
            signedtempbyte=readMem(pc-1);
        printf(" %02x",readMem(pc-1));
        printf("\nmnemonic:JP PC+%d\n",signedtempbyte);
        printf("**************************\n");
#endif
                break;

                /*JR   f,PC+dd*/
            case 0x20://JR NZ,dd
#ifdef DEBUG
        signedtempbyte=readMem(pc);
        printf(" %02x",readMem(pc));
        printf("\nmnemonic:JP NZ,PC+%d\n",signedtempbyte);
        printf("**************************\n");
#endif
                if ((F & Z_FLAG)==0 ) {
                    signedtempbyte=readMem(pc++);
                    pc+=signedtempbyte;
                }else pc++;
                break;

            case 0x28://JR Z,dd
#ifdef DEBUG
            signedtempbyte=readMem(pc);
        printf(" %02x",readMem(pc));
        printf("\nmnemonic:JP Z,PC+%d\n",signedtempbyte);
        printf("**************************\n");
#endif
                if ((F & Z_FLAG)==1 ) {
                    signedtempbyte=readMem(pc++);
                    pc+=signedtempbyte;
                }else pc++;
                break;

            case 0x30://JR NC,dd
#ifdef DEBUG
        signedtempbyte=readMem(pc);
        printf(" %02x",readMem(pc));
        printf("\nmnemonic:JP NC,PC+%d\n",signedtempbyte);
        printf("**************************\n");
#endif
                if ((F & C_FLAG)==0 ) {
                    signedtempbyte=readMem(pc++);
                    pc+=signedtempbyte;
                }else pc++;
                break;

            case 0x38://JR C,dd
#ifdef DEBUG
        signedtempbyte=readMem(pc);
        printf(" %02x",readMem(pc));
        printf("\nmnemonic:JP C,PC+%d\n",signedtempbyte);
        printf("**************************\n");
#endif
                if ((F & C_FLAG)==1 ){
                    signedtempbyte=readMem(pc++);
                    pc+=signedtempbyte;
                }else pc++;
                break;

                /*CALL nn*/
                //TODO: mudar para PC provavelmente
            case 0xCD:
                opAux.Byte.l = readMem(pc++);
                opAux.Byte.h = readMem(pc++);
                writeMem(SP-1,((pc&0xFF00)>>8));
                writeMem(SP-2,(pc&0xFF));
                SP-=2;
                pc=opAux.Word;
#ifdef DEBUG
        printf(" %02x %02x", opAux.Byte.l, opAux.Byte.h);
        printf("\nmnemonic:CALL %04x\n",opAux.Word);
        printf("**************************\n");
#endif
                break;

            case 0xC4://CALL NZ,nn
#ifdef DEBUG
            opAux.Byte.l = readMem(pc);
            opAux.Byte.h = readMem(pc+1);
        printf(" %02x %02x", opAux.Byte.l, opAux.Byte.h);
        printf("\nmnemonic:CALL NZ,%04x\n",opAux.Word);
        printf("**************************\n");
#endif
                if ((F & Z_FLAG)==0 ) {
                    opAux.Byte.l = readMem(pc++);
                    opAux.Byte.h = readMem(pc++);
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=opAux.Word;
                }else pc+=2;
                break;

            case 0xCC://CALL Z,nn
#ifdef DEBUG
            opAux.Byte.l = readMem(pc);
            opAux.Byte.h = readMem(pc+1);
        printf(" %02x %02x", opAux.Byte.l, opAux.Byte.h);
        printf("\nmnemonic:CALL Z,%04x\n",opAux.Word);
        printf("**************************\n");
#endif
                if ((F & Z_FLAG)==1 ) {
                    opAux.Byte.l = readMem(pc++);
                    opAux.Byte.h = readMem(pc++);
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=opAux.Word;
                }else pc+=2;
                break;

            case 0xD4://CALL NC,nn
#ifdef DEBUG
            opAux.Byte.l = readMem(pc);
            opAux.Byte.h = readMem(pc+1);
        printf(" %02x %02x", opAux.Byte.l, opAux.Byte.h);
        printf("\nmnemonic:CALL NC,%04x\n",opAux.Word);
        printf("**************************\n");
#endif
                if ((F & C_FLAG)==0 ) {
                    opAux.Byte.l = readMem(pc++);
                    opAux.Byte.h = readMem(pc++);
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=opAux.Word;
                }else pc+=2;
                break;

            case 0xDC://CALL C,nn
#ifdef DEBUG
            opAux.Byte.l = readMem(pc);
            opAux.Byte.h = readMem(pc+1);
        printf(" %02x %02x", opAux.Byte.l, opAux.Byte.h);
        printf("\nmnemonic:CALL C,%04x\n",opAux.Word);
        printf("**************************\n");
#endif
                if ((F & C_FLAG)==1 ) {
                    opAux.Byte.l = readMem(pc++);
                    opAux.Byte.h = readMem(pc++);
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=opAux.Word;
                }else pc+=2;
                break;

                /*RET*/
            case 0xC9:
                opAux.Byte.l = readMem(SP);
                opAux.Byte.h = readMem(SP+1);
                SP+=2;
                pc=opAux.Word;
#ifdef DEBUG
        printf("\nmnemonic:RET\n");
        printf("**************************\n");
#endif
                break;

                /*RET cc*/
            case 0xC0://RET NZ
                if ((F & Z_FLAG)==0 ) {
                    opAux.Byte.l = readMem(SP);
                    opAux.Byte.h = readMem(SP+1);
                    SP+=2;
                    pc=opAux.Word;
                }
#ifdef DEBUG
        printf("\nmnemonic:RET NZ\n");
        printf("**************************\n");
#endif
                break;
            case 0xC8://RET Z
                if ((F & Z_FLAG)==1 ) {
                    opAux.Byte.l = readMem(SP);
                    opAux.Byte.h = readMem(SP+1);
                    SP+=2;
                    pc=opAux.Word;
                }
#ifdef DEBUG
        printf("\nmnemonic:RET Z\n");
        printf("**************************\n");
#endif
                break;
            case 0xD0://RET NC
                if ((F & C_FLAG)==0 ) {
                    opAux.Byte.l = readMem(SP);
                    opAux.Byte.h = readMem(SP+1);
                    SP+=2;
                    pc=opAux.Word;
                }
#ifdef DEBUG
        printf("\nmnemonic:RET NC\n");
        printf("**************************\n");
#endif
                break;
            case 0xD8://RET C
                if ((F & C_FLAG)==1 ){
                    opAux.Byte.l = readMem(SP);
                    opAux.Byte.h = readMem(SP+1);
                    SP+=2;
                    pc=opAux.Word;
                }
#ifdef DEBUG
        printf("\nmnemonic:RET C\n");
        printf("**************************\n");
#endif
        break;

        /*RETI*/
            case 0xD9:
                    IME=1;
                    opAux.Byte.l = readMem(SP);
                    opAux.Byte.h = readMem(SP+1);
                    SP+=2;
                    pc=opAux.Word;
#ifdef DEBUG
                    printf("\nmnemonic:RETI\n");
                    printf("**************************\n");
#endif
                    break;

                    /*RST n*/
            case 0xC7://RST 0x0
#ifdef DEBUG
                    printf("\nmnemonic:RST 0x0\n");
                    printf("**************************\n");
#endif
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0;
                    break;
            case 0xD7://RST 0x10
#ifdef DEBUG
                    printf("\nmnemonic:RST 0x10\n");
                    printf("**************************\n");
#endif
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0x10;
                    break;
            case 0xDF://RST 0x18
#ifdef DEBUG
                    printf("\nmnemonic:RST 0x18\n");
                    printf("**************************\n");
#endif
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0x18;
                    break;
            case 0xE7://RST 0x20
#ifdef DEBUG
                    printf("\nmnemonic:RST 0x20\n");
                    printf("**************************\n");
#endif
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0x20;
                    break;
            case 0xEF://RST 0x28
#ifdef DEBUG
                    printf("\nmnemonic:RST 0x28\n");
                    printf("**************************\n");
#endif
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0x28;
                    break;
            case 0xF7://RST 0x30
#ifdef DEBUG
                    printf("\nmnemonic:RST 0x30\n");
                    printf("**************************\n");
#endif
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0x30;
                    break;
            case 0xFF://RST 0x38
#ifdef DEBUG
                    printf("\nmnemonic:RST 0x38\n");
                    printf("**************************\n");
#endif
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0x38;
                    break;
            case 0xCF://RST 0x8
#ifdef DEBUG
                    printf("\nmnemonic:RST 0x8\n");
                    printf("**************************\n");
#endif
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0x8;
                    break;


                    /*****************GMB CPU-Controlcommands*********************/

            case 0x3F: //CCF
                F = (F &(Z_FLAG|C_FLAG))^C_FLAG;
#ifdef DEBUG
                    printf("\nmnemonic:CCF\n");
                    printf("**************************\n");
#endif
                break;
            case 0x37: //SCF
                F = (F&Z_FLAG)|C_FLAG;
#ifdef DEBUG
                    printf("\nmnemonic:SCF\n");
                    printf("**************************\n");
#endif
                break;

            case 0x76://HALT
                //TODO: fazer algo ou nao
#ifdef DEBUG
                    printf("\nmnemonic:HALT\n");
                    printf("**************************\n");
#endif
                break;
            case 0x10://STOP
                //TODO: fazer algo ou nao
                pc++;
#ifdef DEBUG
                    printf("\nmnemonic:STOP\n");
                    printf("**************************\n");
#endif
                break;
            case 0xF3: //DI
                IME=0;
#ifdef DEBUG
                    printf("\nmnemonic:DI\n");
                    printf("**************************\n");
#endif
                break;
            case 0xFB: //EI
                IME=1;
#ifdef DEBUG
                    printf("\nmnemonic:EI\n");
                    printf("**************************\n");
#endif
                break;
