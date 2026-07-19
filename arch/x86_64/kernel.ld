OUTPUT_FORMAT(elf64-x86-64)
ENTRY(early_main)

PHDRS
{
    limine_requests PT_LOAD;
    text PT_LOAD;
    rodata PT_LOAD;
    data PT_LOAD;
}

SECTIONS
{
    . = 0xffffffff80000000;

    .limine_requests : {
        KEEP(*(.limine_requests_start))
        KEEP(*(.limine_requests))
        KEEP(*(.limine_requests_end))
    } :limine_requests
    . = ALIGN(0x1000);
    
    text_start = .;
    .text : {
        *(.text)
        *(.text.*)
    } :text
    . = ALIGN(0x1000);

    .rodata : {
        *(.rodata)
        *(.rodata.*)
    } :rodata
    . = ALIGN(0x1000);

    .data : {
        *(.data)
        *(.data.*)
    } :data
    . = ALIGN(0x1000);

    .bss : {
        *(COMMON)
        *(.bss)
        *(.bss.*)
    } :data
    . = ALIGN(0x1000);
    /DISCARD/ : {
        *(.eh_frame)
        *(.note.*)
    }

    endkernel = .;
}