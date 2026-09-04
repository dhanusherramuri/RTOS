#On Terminal one 
st-util




#On second terminal 
gdb-multiarch firmware.elf 
(gdb)

target extended-remote :4242
display/i $pc
display $sp
display/x $r7
display/8xw $sp
display/x $lr


break main
break Reset_Handler
monitor reset halt
set disassemble-next-line on
