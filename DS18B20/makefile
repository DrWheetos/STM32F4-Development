#
#
# -------------------------------------------------------------------------------------------------
# Toolchain prefix (i.e arm-none-eabi- -> arm-none-eabi-gcc.exe)
TCHAIN_PREFIX = C:\ARM\ARMGCC\bin\arm-none-eabi-

# -------------------------------------------------------------------------------------------------
# MCU name, submodel and board
# - MCU used for compiler-option (-mcpu)
MCU      = cortex-m4
CHIP     = STM32F4X
F_XTAL   = 8000000
#SYSCLOCK_CL = SYSCLK_FREQ_72MHz=72000000


# -------------------------------------------------------------------------------------------------
# *** This example only supports "FLASH_RUN" ***
# RUN_MODE is passed as define and used for the linker-script filename,
# the user has to implement the necessary operations for 
# the used mode(s) (i.e. no copy of .data, remapping)
# Create FLASH-Image
RUN_MODE=FLASH_RUN
# Create RAM-Image
#RUN_MODE=RAM_RUN


# -------------------------------------------------------------------------------------------------
# YES enables -mthumb option to flags for source-files listed 
# in SRC and CPPSRC and -mthumb-interwork option for all source
USE_THUMB_MODE = YES
#USE_THUMB_MODE = NO


# -------------------------------------------------------------------------------------------------
# Target file name (without extension).
TARGET = DS18B20


# -------------------------------------------------------------------------------------------------
# Directory for output files (lst, dep, elf, sym, map, hex, bin etc.)
OUTDIR = bin
# Directory for compiled object files.
OBJECTDIR = obj


# -------------------------------------------------------------------------------------------------
# Directory where the build, clean, rebuild all and linker scripts are held.
SCRIPTSDIR = scripts


# -------------------------------------------------------------------------------------------------
# Library folders
#GCCLIBDIR  = "E:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2014q2\arm-none-eabi\lib"


# -------------------------------------------------------------------------------------------------
# Paths to include folders
INC_DIR           = inc
CMSIS_INCDIR      = inc/CMSIS
STM32F4_INCDIR    = inc/STM32F4xx
STMLIB_INCDIR     = inc/STM32F4xx_StdPeriph_Driver/inc
STMLIB_SRCDIR     = inc/STM32F4xx_StdPeriph_Driver/src

#SYSTICK_INCDIR    = systick
#SYSCALLS_INCDIR   = syscalls
#STDIO_INCDIR      = stdio
#HELPERS_INCDIR    = helpers
#GLCD_INCDIR       = glcd
#FONTS_INCDIR      = fonts
#FATFS_INCDIR      = fatfs
#SDCARD_INCDIR     = sdcard
#IR_INCDIR         = ir


# -------------------------------------------------------------------------------------------------
# List C source files here. (C dependencies are automatically generated.)
# use file-extension c for "c-only"-files
# Main application files
SRC  = main.c

# helpers files
SRC += helpers/usart.c
SRC += helpers/onewire.c
SRC += helpers/delay.c
SRC += helpers/debug.c
SRC += helpers/formatters.c
SRC += helpers/ds18b20.c


# System and startup files
SRC += system/system_stm32f4xx.c
SRC += system/startup_stm32f4xx.s
SRC += system/stm32f4xx_it.c

# Syscalls files
# If you get this error:
# sbrkr.c:(.text._sbrk_r+0xc): undefined reference to `_sbrk'
# ensure you include this in your make.
SRC += system/syscalls.c

# stdio files
SRC += stdio/printf.c

# STM Library source files
SRC += $(STMLIB_SRCDIR)/misc.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_adc.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_can.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_crc.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_cryp_aes.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_cryp_des.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_cryp_tdes.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_cryp.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_dac.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_dbgmcu.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_dcmi.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_dma.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_exti.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_flash.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_fsmc.c
SRC += $(STMLIB_SRCDIR)/stm32f4xx_gpio.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_hash_md5.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_hash_sha1.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_hash.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_i2c.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_iwdg.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_pwr.c
SRC += $(STMLIB_SRCDIR)/stm32f4xx_rcc.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_rng.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_rtc.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_sdio.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_spi.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_syscfg.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_tim.c
SRC += $(STMLIB_SRCDIR)/stm32f4xx_usart.c
#SRC += $(STMLIB_SRCDIR)/stm32f4xx_wwdg.c







# -------------------------------------------------------------------------------------------------
# List C++ source files here.
# use file-extension .cpp for C++-files (not .C)
#CPPSRC = main.cpp


# -------------------------------------------------------------------------------------------------
# List C++ source files here which must be compiled in ARM-Mode.
# use file-extension .cpp for C++-files (not .C)
#CPPSRCARM = $(TARGET).cpp
CPPSRCARM = 



# -------------------------------------------------------------------------------------------------
# List any extra directories to look for include files here.
#    Each directory must be seperated by a space.
EXTRAINCDIRS  = $(INC_DIR) $(CMSIS_INCDIR) $(STM32F4_INCDIR) $(STMLIB_INCDIR)

# -------------------------------------------------------------------------------------------------
# Optimization level, can be [0, 1, 2, 3, s]. 
# 0 = Turn off optimization. Reduce compilation time and make debugging
#     produce the expected results.
# 1 = The compiler tries to reduce code size and execution time, without
#     performing any optimizations that take a great deal of compilation time.
# 2 = GCC performs nearly all supported optimizations that do not involve a 
#     space-speed tradeoff. As compared to -O1, this option increases
#     both compilation time and the performance of the generated code.
# 3 = Optimize yet more. Turns on -finline-functions and more.
# s = -Os enables all -O2 optimizations that do not typically increase code
#     size.
# (See gcc manual for further information)
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
#OPT = s
#OPT = 2
#OPT = 3
OPT = 0


# -------------------------------------------------------------------------------------------------
# Output format. (can be ihex or binary or both)
#  binary to create a load-image in raw-binary format i.e. for SAM-BA, 
#  ihex to create a load-image in Intel hex format i.e. for lpc21isp
LOADFORMAT = ihex
#LOADFORMAT = binary
#LOADFORMAT = both


# -------------------------------------------------------------------------------------------------
# Place project-specific -D and/or -U options for Assembler with preprocessor here.
ADEFS = -D__ASSEMBLY__


# -------------------------------------------------------------------------------------------------
# Debugging format.
#DEBUG = stabs
#DEBUG = dwarf-2


# -------------------------------------------------------------------------------------------------
# Place project-specific -D (define) and/or 
# -U options for C here.
CDEFS = -DSTM32F4x
#CDEFS += -DSTM32F10X_HD
#CDEFS += -DHSE_VALUE=$(F_XTAL)UL
#CDEFS += -D$(SYSCLOCK_CL)
CDEFS += -DUSE_STDPERIPH_DRIVER
#CDEFS += -DUSE_$(BOARD)
#CDEFS += -DSTM32_SD_USE_DMA
#CDEFS += -DSTARTUP_DELAY
# enable parameter-checking in STM's library
#CDEFS += -DUSE_FULL_ASSERT
CDEFS += -D__ASSEMBLY__
#CDEFS += -D__GNUC__
#CDEFS += -D__cplusplus


# -------------------------------------------------------------------------------------------------
# Extra libraries
#    Each library-name must be seperated by a space.
#    i.e. to link with libxyz.a, libabc.a and libefsl.a: 
#     EXTRA_LIBS = xyz abc efsl
#    for newlib-lpc (file: libnewlibc-lpc.a):
#     EXTRA_LIBS = newlib-lpc
EXTRA_LIBS = 


# -------------------------------------------------------------------------------------------------
# Compiler flags.

ifeq ($(USE_THUMB_MODE),YES)
THUMB    = -mthumb
THUMB_IW = -mthumb-interwork
else 
THUMB    = 
THUMB_IW = 
endif

#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
#
# Flags for C and C++ (arm-elf-gcc/arm-elf-g++)
CFLAGS =  -g$(DEBUG)
CFLAGS += -O$(OPT)
CFLAGS += -mcpu=$(MCU)
CFLAGS += -Wall -Wextra
CFLAGS += -mlittle-endian $(THUMB) $(THUMB_IW)
CFLAGS += -mfloat-abi=softfp
#CFLAGS += -mfloat-abi=hard
#CFLAGS += -mfpu=fpv4-sp-d16
CFLAGS += $(CDEFS)
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS)) -I.
# when using ".ramfunc"s without longcall:
#CFLAGS += -mlong-calls
# -mapcs-frame is important if gcc's interrupt attributes are used
# (at least from my eabi tests), not needed if assembler-wrapper is used 
#CFLAGS += -mapcs-frame 
#CFLAGS += -fomit-frame-pointer
CFLAGS += -ffunction-sections -fdata-sections
#CFLAGS += --specs=rdimon.specs
#CFLAGS += -fpromote-loop-indices
#CFLAGS += -Wimplicit -Wcast-align -Wpointer-arith
#CFLAGS += -Wredundant-decls -Wshadow -Wcast-qual -Wcast-align
#CFLAGS += -pedantic
#CFLAGS += -Wa,-adhlns=$(addprefix $(OUTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))
# Compiler flags to generate dependency files:
#CFLAGS += -MD -MP -MF $(OUTDIR)/dep/$(@F).d


# flags only for C++ (arm-*-g++)
CPPFLAGS = -fno-rtti -fno-exceptions -std=c++11


# Link with the GNU C++ stdlib.
#CPLUSPLUS_LIB  = -lc
#CPLUSPLUS_LIB  = -lstdc++
#CPLUSPLUS_LIB += -lsupc++
#CPLUSPLUS_LIB += -lm
#CPLUSPLUS_LIB += -lnosys
#CPLUSPLUS_LIB += -lrdimon


# -------------------------------------------------------------------------------------------------
# Linker flags.
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS = -Wl,-Map=$(OUTDIR)/$(TARGET).map,--gc-sections
LDFLAGS += -T$(SCRIPTSDIR)/stm32_flash.ld
#LDFLAGS += --specs=nosys.specs
LDFLAGS += -lc
LDFLAGS += -lgcc
LDFLAGS += -lg
LDFLAGS += -lm
#LDFLAGS += -lnosys
#LDFLAGS += -lrdimon
LDFLAGS += $(CPLUSPLUS_LIB)
LDFLAGS += $(patsubst %,-L%,$(EXTRA_LIBDIRS))
LDFLAGS += $(patsubst %,-l%,$(EXTRA_LIBS))
#LDFLAGS += $(MATH_LIB)


# -------------------------------------------------------------------------------------------------
# List of all source files.
ALLSRC     = $(SRC) $(CPPSRC)
#ALLSRC     = $(SRCARM) $(SRC) $(CPPSRCARM) $(CPPSRC)
#ALLSRC     = $(SRCARM) $(SRC)
# List of all source files without directory and file-extension.
ALLSRCBASE = $(notdir $(basename $(ALLSRC)))


# -------------------------------------------------------------------------------------------------
# Define all object files.
#ALLOBJ     = $(addprefix $(OUTDIR)/, $(addsuffix .o, $(ALLSRCBASE)))
ALLOBJ     = $(addprefix $(OBJECTDIR)/, $(addsuffix .o, $(ALLSRCBASE)))




# -------------------------------------------------------------------------------------------------
# Default target.
#all: begin gppversion sizebefore build sizeafter finished end
all: begin createdirs gccversion build sizeafter finished end

elf: $(OUTDIR)/$(TARGET).elf 
lss: $(OUTDIR)/$(TARGET).lss 
sym: $(OUTDIR)/$(TARGET).sym 
hex: $(OUTDIR)/$(TARGET).hex 
bin: $(OUTDIR)/$(TARGET).bin 





ifeq ($(LOADFORMAT),ihex)
build: elf hex lss
else 
ifeq ($(LOADFORMAT),binary)
build: elf bin lss sym
else 
ifeq ($(LOADFORMAT),both)
build: elf hex bin lss sym
else 
$(error "$(MSG_FORMATERROR) $(FORMAT)")
endif
endif
endif



# -------------------------------------------------------------------------------------------------
# Create output directories.  md works on Windows.
createdirs:
	-@md $(OUTDIR) >NUL 2>&1 || echo "" >NUL
	-@md $(OUTDIR)\dep >NUL 2>&1 || echo "" >NUL
	-@md $(OBJECTDIR) >NUL 2>&1 || echo "" >NUL


# -------------------------------------------------------------------------------------------------
# Define programs and commands.
CC      = $(TCHAIN_PREFIX)gcc
CPP     = "$(TCHAIN_PREFIX)g++"
AR      = $(TCHAIN_PREFIX)ar
OBJCOPY = "$(TCHAIN_PREFIX)objcopy"
OBJDUMP = "$(TCHAIN_PREFIX)objdump"
SIZE    = $(TCHAIN_PREFIX)size
NM      = $(TCHAIN_PREFIX)nm
#REMOVE  = cmd /C del
REMOVE  = rm -f 

# -------------------------------------------------------------------------------------------------
# Define Messages
# English
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = --------  begin, mode: $(RUN_MODE)  --------
MSG_END = --------  end  --------
MSG_SIZE_BEFORE = ---- Size before : 
MSG_SIZE_AFTER = ---- Size after build :
MSG_LOAD_FILE = ---- Creating load file :
MSG_EXTENDED_LISTING = ---- Creating Extended Listing/Disassembly :
MSG_SYMBOL_TABLE = ---- Creating Symbol Table :
MSG_LINKING = ---- Linking :
MSG_COMPILING = ---- Compiling C :
MSG_COMPILING_ARM = ---- Compiling C ARM-only :
MSG_COMPILINGCPP = ---- Compiling C++ :
MSG_COMPILINGCPP_ARM = ---- Compiling C++ ARM-only :
MSG_ASSEMBLING = ---- Assembling :
MSG_ASSEMBLING_ARM = ---- Assembling ARM-only :
MSG_CLEANING = ---- Cleaning project :
MSG_FORMATERROR = Can not handle output-format
#MSG_LPC21_RESETREMINDER = You may have to bring the target in bootloader-mode now.
MSG_ASMFROMC = "Creating asm-File from C-Source:"
MSG_ASMFROMC_ARM = "Creating asm-File from C-Source (ARM-only):"


# -------------------------------------------------------------------------------------------------
# Display C++ compiler version information.
gppversion : 
	@$(CPP) --version

# -------------------------------------------------------------------------------------------------
# Display C compiler version information.
gccversion:
	@$(CC) --version

# -------------------------------------------------------------------------------------------------
# Eye candy.
begin:
	@echo $(MSG_BEGIN)

# -------------------------------------------------------------------------------------------------
finished:
##	@echo $(MSG_ERRORS_NONE)

# -------------------------------------------------------------------------------------------------
end:
	@echo $(MSG_END)


# -------------------------------------------------------------------------------------------------
ELFSIZE = $(SIZE) $(OUTDIR)/$(TARGET).elf

# -------------------------------------------------------------------------------------------------
sizebefore:
#	@if [ -f $(OUTDIR)/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(ELFSIZE); echo; fi
	@echo $(MSG_SIZE_BEFORE)
	$(ELFSIZE)
	@echo .

# -------------------------------------------------------------------------------------------------
sizeafter:
#	@if [ -f  $(OUTDIR)/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(ELFSIZE); echo; fi
	@echo $(MSG_SIZE_AFTER)
	$(ELFSIZE)
	@echo .

# -------------------------------------------------------------------------------------------------
# Create final output file (.hex) from ELF output file.
%.hex: %.elf
	@echo $(MSG_LOAD_FILE) $@
	$(OBJCOPY) -O ihex $< $@
	@echo .
	
# -------------------------------------------------------------------------------------------------
# Create final output file (.bin) from ELF output file.
%.bin: %.elf
	@echo $(MSG_LOAD_FILE) $@
	$(OBJCOPY) -O binary $< $@
	@echo .

# -------------------------------------------------------------------------------------------------
# Create extended listing file/disassambly from ELF output file.
# using objdump testing: option -C
%.lss: %.elf
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S -C -r $< > $@
#	$(OBJDUMP) -x -S $< > $@
	@echo .
	
# -------------------------------------------------------------------------------------------------
# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo $(MSG_SYMBOL_TABLE) $@
	$(NM) -n $< > $@


# -------------------------------------------------------------------------------------------------
# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(ALLOBJ)
%.elf: $(ALLOBJ)
	@echo .
	@echo $(MSG_LINKING) $@
	@echo $(CFLAGS)
# use $(CC) for C-only projects or $(CPP) for C++-projects:
#	$(CC) $(THUMB) $(CFLAGS) $(ALLOBJ) --output $@ $(LDFLAGS)
#	$(CPP) $(THUMB) $(CFLAGS) $(ALLOBJ) --output $@ $(LDFLAGS)
ifeq "$(strip $(CPPSRC)$(CPPARM))" ""
	$(CC) $(THUMB) $(CFLAGS) $(ALLOBJ) --output $@ -nostartfiles $(LDFLAGS)
else
	$(CPP) $(THUMB) $(CFLAGS) $(ALLOBJ) --output $@ -nostartfiles $(LDFLAGS)
endif
	@echo .


# -------------------------------------------------------------------------------------------------
# Compile: create object files from C source files.
define COMPILE_C_TEMPLATE
$(OBJECTDIR)/$(notdir $(basename $(1))).o : $(1)
	@echo $(MSG_COMPILING) $$< to $$@
	$(CC) -c $(THUMB) $$(CFLAGS) $$(CONLYFLAGS) $$< -o $$@ 
endef
$(foreach src, $(SRC), $(eval $(call COMPILE_C_TEMPLATE, $(src)))) 


# -------------------------------------------------------------------------------------------------
# Compile: create object files from C source files. ARM-only
define COMPILE_C_ARM_TEMPLATE
$(OBJECTDIR)/$(notdir $(basename $(1))).o : $(1)
	@echo $(MSG_COMPILING_ARM) $$< to $$@
	$(CC) -c $$(CFLAGS) $$(CONLYFLAGS) $$< -o $$@ 
endef
$(foreach src, $(SRCARM), $(eval $(call COMPILE_C_ARM_TEMPLATE, $(src)))) 


# -------------------------------------------------------------------------------------------------
# Compile: create object files from C++ source files.
define COMPILE_CPP_TEMPLATE
$(OBJECTDIR)/$(notdir $(basename $(1))).o : $(1) $(BUILDONCHANGE)
	@echo $(MSG_COMPILINGCPP) $$< to $$@
	$(CPP) -c $(THUMB) $$(CFLAGS) $$(CPPFLAGS) $$< -o $$@ 
endef
$(foreach src, $(CPPSRC), $(eval $(call COMPILE_CPP_TEMPLATE, $(src)))) 


# -------------------------------------------------------------------------------------------------
# Compile: create object files from C++ source files. ARM-only
define COMPILE_CPP_ARM_TEMPLATE
$(OBJECTDIR)/$(notdir $(basename $(1))).o : $(1) $(BUILDONCHANGE)
	@echo $(MSG_COMPILINGCPP_ARM) $$< to $$@
	$(CC) -c $$(CFLAGS) $$(CPPFLAGS) $$< -o $$@ 
endef
$(foreach src, $(CPPSRCARM), $(eval $(call COMPILE_CPP_ARM_TEMPLATE, $(src)))) 


# -------------------------------------------------------------------------------------------------
# Compile: create assembler files from C source files. ARM/Thumb
#$(SRC:.c=.s) : %.s : %.c
#	@echo $(MSG_ASMFROMC) $< to $@
#	$(CC) $(THUMB) -S $(CFLAGS) $(CONLYFLAGS) $< -o $@

# -------------------------------------------------------------------------------------------------
# Compile: create assembler files from C source files. ARM only
#$(SRCARM:.c=.s) : %.s : %.c
#	@echo $(MSG_ASMFROMC_ARM) $< to $@
#	$(CC) -S $(CFLAGS) $(CONLYFLAGS) $< -o $@


# -------------------------------------------------------------------------------------------------
# Target: clean project.
clean: begin clean_list finished end

# -------------------------------------------------------------------------------------------------
clean_list :
	@echo $(MSG_CLEANING)
	$(REMOVE) $(OUTDIR)\$(TARGET).map
	$(REMOVE) $(OUTDIR)\$(TARGET).elf
	$(REMOVE) $(OUTDIR)\$(TARGET).hex
	$(REMOVE) $(OUTDIR)\$(TARGET).bin
	$(REMOVE) $(OUTDIR)\$(TARGET).sym
	$(REMOVE) $(OUTDIR)\$(TARGET).lss
	$(REMOVE) $(subst /,\,$(ALLOBJ))
#	$(REMOVE) $(LSTFILES)
#	$(REMOVE) $(DEPFILES)



# -------------------------------------------------------------------------------------------------
# Listing of phony targets.
.PHONY : all begin finish end sizebefore sizeafter gppversion \
build elf hex bin lss sym clean clean_list program createdirs



