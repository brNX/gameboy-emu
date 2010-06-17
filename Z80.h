/*
 * Z80.h
 *
 *  Created on: 2010/06/17
 *      Author: brNX
 */

#ifndef Z80_H_
#define Z80_H_

#include <stdint.h>


//union para registo 16bit com accesso 8bit
typedef union
{
  struct { uint8_t h,l; } S;
  uint16_t M;
} reg16bit;

class Z80
{
	public:
		Z80();
		virtual ~Z80();
		void reset(); //            -> resets the CPU core
		void execute(int nclyces);//   -> the core executes n cycles
		//getcontext(); //      -> returns the CPU context
		//setcontext(); //   -> sets the CPU context
		void interrupt();  //      -> sends an interrupt signal
	private:
		reg16bit AF,BC,DE,HL,SP,PC;
};

#endif /* Z80_H_ */
