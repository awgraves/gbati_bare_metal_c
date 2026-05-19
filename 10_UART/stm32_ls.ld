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
    *(.text.*)
    *(.rodata)
    *(.rodata.*)
    . = ALIGN(4);
  } >FLASH

  _la_data = LOADADDR(.data);
  .data : {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data.*)
    . = ALIGN(4);
    _edata = .;
  } >SRAM AT>FLASH /* VMA AT> LMA */

  .bss : {
    . = ALIGN(4);
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss.*)
    . = ALIGN(4);
    _ebss = .;
    end = _ebss;
    __bss_end__ = end;
  } >SRAM
}
