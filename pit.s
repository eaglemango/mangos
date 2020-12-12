.intel_syntax noprefix

.global program_pit

# Input
# ebx   Desired PIT frequency in Hz
program_pit:
    mov ebx, 1000
    pushad
 
    # Do some checking
 
    mov eax,0x10000                   # eax = reload value for slowest possible frequency (65536)
    cmp ebx,18                        # Is the requested frequency too low?
    jbe .gotReloadValue               # yes, use slowest possible frequency
 
    mov eax,1                         # ax = reload value for fastest possible frequency (1)
    cmp ebx,1193181                   # Is the requested frequency too high?
    jae .gotReloadValue               # yes, use fastest possible frequency
 
    # Calculate the reload value
 
    mov eax,3579545
    mov edx,0                         # edx:eax = 3579545
    div ebx                           # eax = 3579545 / frequency, edx = remainder
    cmp edx,3579545 / 2               # Is the remainder more than half?
    jb .l1                            #  no, round down
    inc eax                           #  yes, round up
 .l1:
    mov ebx,3
    mov edx,0                         # edx:eax = 3579545 * 256 / frequency
    div ebx                           # eax = (3579545 * 256 / 3 * 256) / frequency
    cmp edx,3 / 2                     # Is the remainder more than half?
    jb .l2                            #  no, round down
    inc eax                           #  yes, round up
 .l2:

 .gotReloadValue:
    # push eax                          # Store reload_value for later
    # mov [PIT_reload_value],ax         # Store the reload value for later
    # mov ebx,eax                       # ebx = reload value
  
    # Program the PIT channel
 
    pushfd
    cli                               # Disabled interrupts (just in case)
    
    push eax
    xor eax, eax
    xor edx, edx
    mov edx, 0x43
    mov eax, 0b00110100                  # channel 0, lobyte/hibyte, rate generator
    out edx, eax
    
    pop eax
    xor edx, edx
    mov edx, 0x40
    # mov ax,[PIT_reload_value]         # ax = 16 bit reload value
    # out edx, al                       # Set low byte of PIT reload value
    # mov al, ah                         # ax = high 8 bits of reload value
    out edx, eax                       # Set high byte of PIT reload value
 
    popfd
 
    popad
    ret


.global pit_sleep

pit_sleep:
    