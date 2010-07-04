'''
Created on Jun 29, 2010

@author: bgouveia
'''

Z_FLAG  =   0x8   
N_FLAG =  0x4    
H_FLAG =    0x2    
C_FLAG  =   0x1    
H_FLAGDEC  =  0x20

TABLE=[1, 3, 2, 2, 1, 1, 2, 1, 5, 2, 2, 2, 1, 1, 2, 1,
    1, 3, 2, 2, 1, 1, 2, 1, 3, 2, 2, 2, 1, 1, 2, 1,
    3, 3, 2, 2, 1, 1, 2, 1, 3, 2, 2, 2, 1, 1, 2, 1,
    3, 3, 2, 2, 1, 3, 3, 3, 3, 2, 2, 2, 1, 1, 2, 1,
    
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1,
    
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    
    5, 3, 4, 4, 6, 4, 2, 4, 5, 4, 4, 1, 6, 6, 2, 4,
    5, 3, 4, 0, 6, 4, 2, 4, 5, 4, 4, 0, 6, 0, 2, 4,
    3, 3, 2, 0, 0, 4, 2, 4, 4, 1, 4, 0, 0, 0, 2, 4,
    3, 3, 2, 1, 0, 4, 2, 4, 3, 2, 4, 1, 0, 0, 2, 4]

TABLECB= [2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,

        2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2,
        2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2,
        2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2,
        2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2,

        2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,

        2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
        2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2]

def Denary2Binary(n):
    '''convert denary integer n to binary string bStr'''
    bStr = ''
    if n < 0:  raise ValueError, "must be a positive integer"
    if n == 0: return '0'
    while n > 0:
        bStr = str(n % 2) + bStr
        n = n >> 1
    return bStr

def int2bin(n, count=24):
    """returns the binary of integer n, using count number of digits"""
    return "".join([str((n >> y) & 1) for y in range(count-1, -1, -1)])

def daa():
    out = [0]*2048
    for i in range (2048):
        temp=0
        F = (i & 0x700) >> 8
        A= i & 0xFF
        #print "flag:",F," bin:",int(int2bin(F, 4))
        #print "A:",A," bin:",int(int2bin(A, 12))
        
        if A>0x99 or ((F&C_FLAG)==C_FLAG):
            temp=0x60
            F |= C_FLAG
        else:
            F &= ~C_FLAG
            temp=0
            
        if (A & 0xF) > 0x9 or (F & H_FLAG) == H_FLAG:
            temp+=6
        
        temp2=A
        
        if (F & N_FLAG) == N_FLAG:
            temp2+=temp;
        else:
            temp2-=temp;
        
        #H_FLAG    
        if (((A & 0x8) ^ (temp2 & 0x8)) >> 2) == H_FLAG :
            F |= H_FLAG
        else:
            F &= ~H_FLAG
         
        #Z_FLAG
        if (temp2 & 0xFF) == 0:
            F |= Z_FLAG;
        else:
            F &= ~Z_FLAG;
            
        out[i]|= (temp2 & 0XFF) << 8
        out[i]|= F
        
        if i%16 == 0:
            print ""
        if (i%(16*16))==0:
            print ""
            
        print "0x%x," % (out[i]),
        
def daa2():
    out = [0]*2048
    for i in range (2048):
        F = (i & 0x700) >> 8
        A= i & 0xFF
        
        N=False
        C=False
        H=False
        
        if (F&C_FLAG)==C_FLAG:
            C=True
        
        if (F&N_FLAG)==N_FLAG:
            N=True

        if (F&H_FLAG)==H_FLAG:
            H=True

        #print "flag:",F," bin:",int(int2bin(F, 4))
        #print "A:",A," bin:",int(int2bin(A, 12))
        tempF=0
        
        if N : 
            tempF |= N_FLAG
            if H and (A & 0xF <=0x5):
                tempF |= H_FLAG
        else:
            if (A & 0xF >0x9):
                tempF |= H_FLAG
                
        
        if (((A & 0xF0) >>4) <=0x9) and (A & 0xF <=0x9):
            
            if not C and not H:
                A=(A << 8) & 0xFF00
                  
            if not C and H:
                if N :
                    A += 0xFA
                else:
                    A += 0x06
                
                A = (A << 8) & 0xFF00
                    
            if C and not H:
                if N :
                    A += 0xA0
                else:
                    A += 0x60
                tempF |= C_FLAG
                A = (A << 8) & 0xFF00
                
            if C and H:
                if N :
                    A += 0x9A
                else:
                    A += 0x66
                tempF |= C_FLAG
                A = (A << 8) & 0xFF00
                
        if (((A & 0xF0)>>4) <= 0x9) and ((A & 0xF) > 0x9):
            
            if not C and (((A & 0xF0)>>4) == 0x9):
                tempF|=C_FLAG
            
            if not C and not H:
                if N :
                    A = (A << 8) & 0xFF00
                else:
                    A+=0x06
                    A = (A<<8) & 0xFF00
                  
            if not C and H:
                if N :
                    A += 0xFA
                else:
                    A += 0x06
                
                A = (A << 8) & 0xFF00
                    
            if C and not H:
                if N :
                    A += 0xA0
                else:
                    A += 0x66
                tempF |= C_FLAG
                A = (A << 8) & 0xFF00
                
            if C and H:
                if N :
                    A += 0x9A
                else:
                    A += 0x66
                tempF |= C_FLAG
                A = (A << 8) & 0xFF00
                
                
        if (((A & 0xF0)>>4) > 0x9) and ((A & 0xF) <= 0x9):
            
            tempF|=C_FLAG
            
            if not C and not H:
                if N :
                    A = (A << 8) & 0xFF00
                else:
                    A+=0x60
                    A = (A<<8) & 0xFF00
                  
            if not C and H:
                if N :
                    A += 0xFA
                else:
                    A += 0x66
                A = (A << 8) & 0xFF00
                    
            if C and not H:
                if N :
                    A += 0xA0
                else:
                    A += 0x60
                A = (A << 8) & 0xFF00
                
            if C and H:
                if N :
                    A += 0x9A
                else:
                    A += 0x66
                A = (A << 8) & 0xFF00
                
        if (((A & 0xF0)>>4) > 0x9) and ((A & 0xF) > 0x9):
            
            tempF|=C_FLAG
            
            if not C and not H:
                if N :
                    A = (A << 8) & 0xFF00
                else:
                    A+=0x66
                    A = (A<<8) & 0xFF00
                  
            if not C and H:
                if N :
                    A += 0xFA
                else:
                    A += 0x66
                A = (A << 8) & 0xFF00
                    
            if C and not H:
                if N :
                    A += 0xA0
                else:
                    A += 0x66
                A = (A << 8) & 0xFF00
                
            if C and H:
                if N :
                    A += 0x9A
                else:
                    A += 0x66
                A = (A << 8) & 0xFF00
            
            
        if A==0: tempF |= Z_FLAG

        
        out[i]= (A | (tempF<<4))
        
        if i%8 == 0:
            print ""
        if (i%(16*16))==0:
            print ""
            
        print "0x%x," % (out[i]),

#CHECK_H(val) F |= (H_FLAG & ((A ^ (val) ^ opAux.Byte.l) << 1)); 
       
def HDEC():
    out = [0]*256
    for i in range(256):
        tempF=0
        tempF |= (H_FLAGDEC & ( ((i+1) ^ 1 ^ (i&0xFF)) <<1 ))
        out[i]=tempF
        if(i%16==0): print ""
        if(i%(16*4)==0): print ""
        if i==0:
            print "%s,"%("N_FLAG|Z_FLAG"),
        else:
            print "%s,"%("H_FLAG|N_FLAG" if out[i]==32 else "N_FLAG"),
    print "\n 14:",out[0x14]   
        
def HINC():
    out = [0]*256
    for i in range(256):
        tempF=0
        tempF |= (H_FLAGDEC & ( ((i-1) ^ 1 ^ (i&0xFF)) <<1 ))
        out[i]=tempF
        if(i%16==0): print ""
        if(i%(16*4)==0): print ""
        if i==0:
            print "%s,"%("H_FLAG|Z_FLAG"),
        else:
            print "%s,"%("H_FLAG" if out[i]==32 else "0"),
    print "\n 14:",out[0x14]   
                   
    

if __name__ == '__main__':
#    A=0x1C2
#    print "a: ",int2bin(A,16)
#    A=((A >> 1)|(A << 8)) & 0X1FF
#    B= (A & 0x1) << 4 
#    A= A >>1 
#    print "a: ",int2bin(A,8)
#    print "a: %x"%(A)
#    print "b: ",int2bin(B,8)
#    print "b: %x"%(B)
    #daa2()
    HDEC()
    
        
            
        
        
        