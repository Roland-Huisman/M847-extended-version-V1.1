# M847-extended-version-V1.1
M847 extended version V1.1 project files

This is a project to add a bootloader or bootstraploader to a Digital / DEC PDP8/e PDP8/m PDP8/f computer.

Originally Digital had an M847 diode bootstrap loader. Because the EPROM was not
invented yet, there were 32 x 12 diodes making it a 32 word bootloader.
So a -not programmed- board had 384 diodes in the program field. You could
write your program by cutting out these diodes.

Quite a lot of work to 'reprogram' such a board.

The M847 extended version does not have a 32 word limit. So much bigger programs can be loaded.
The idea is to put in as much test programs and bootloaders as possible. The first 15 programs
are selectable by the dipswitches on the board. This makes such a program a default program.

After toggeling the SW switch one time, the default will be loaded.

Toggeling more than once shows up the programnumber into the address lights.
After a time out of 3 seconds the displayed program will be loaded.

The initial V1 version puts out a lot of debugging data and is slowed down a lot.
This will be tuned up soon. But it does give a nice blinkenlight effect while loading.

The PCB has been made in trough hole components. This because many people can built it
without any special tools. The ATMEGA328 needs to have an Arduino bootloader in it.
You can program this also with an Arduino as programmer.

Regards, Roland Huisman

First demo: https://youtu.be/0nqb3zyAv2g

Second demo: https://youtu.be/xYt5kZuUb3A
