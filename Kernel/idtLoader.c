#include "idtLoader.h"

#pragma pack(push)		/* Push de la alineación actual */
#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */

/* Descriptor de interrupcion */
typedef struct {
  uint16_t offset_l, selector;
  uint8_t cero, access;
  uint16_t offset_m;
  uint32_t offset_h, other_cero;
} DESCR_INT;

#pragma pack(pop)		/* Reestablece la alinceación actual */



DESCR_INT * idt = (DESCR_INT *) 0;	// IDT de 255 entradas

static void setup_IDT_entry (int index, uint64_t offset);


void hang(){
  printString("double fault", 0,2,255);
  while(1);
}

void load_idt() {
  _cli();

  setup_IDT_entry(0x00, (uint64_t)&_divideByZeroHandler); // Divide by zero exception
  setup_IDT_entry(0x04, (uint64_t)&_overflowHandler); // Overflow exception
  setup_IDT_entry(0x06, (uint64_t)&_opcodeHandler); // Invalid opcode exception
  //setup_IDT_entry(0x08, (uint64_t)&hang); // Double fault
  setup_IDT_entry(0x13, (uint64_t)&_generalProtection); // Invalid general protection exception
  setup_IDT_entry(0x20, (uint64_t)&_irq00Handler);
  setup_IDT_entry(0x21, (uint64_t)&_irq01Handler); //Keyboard
  setup_IDT_entry(0x80, (uint64_t)&sysCallDispatcher);

	//Solo interrupcion timer tick habilitadas
	picMasterMask(0xFC);//FC
	picSlaveMask(0xFF);//FF

	_sti();
}

static void setup_IDT_entry (int index, uint64_t offset) {
  idt[index].selector = 0x08;
  idt[index].offset_l = offset & 0xFFFF;
  idt[index].offset_m = (offset >> 16) & 0xFFFF;
  idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
  idt[index].access = ACS_INT;
  idt[index].cero = 0;
  idt[index].other_cero = (uint64_t) 0;
}
