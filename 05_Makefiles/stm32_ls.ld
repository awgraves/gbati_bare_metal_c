/* Specifying the firmware's entrypoint */
ENTRY(Reset_Handler)

/* Detailing available memory */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K 
}

_estack = ORIGIN(SRAM)+LENGTH(SRAM);

/* Necessary heap and stack sizes */
__max_heap_size = 0x200;
__max_stack_size = 0x400;

/* Output sections */
SECTIONS {
  .text : {
    . = ALIGN(4);
    *(.isr_vector_tbl)
    . = ORIGIN(FLASH)+(113 * 4); /* skip over the other unused ISR slots */
    *(.text)
    *(.rodata)
    . = ALIGN(4);
    _etext = .;
  } >FLASH

  .data : {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    . = ALIGN(4);
    _edata = .;
  } >SRAM AT>FLASH /* VMA AT> LMA */

  .bss : {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    . = ALIGN(4);
    _ebss = .;
  } >SRAM
}
