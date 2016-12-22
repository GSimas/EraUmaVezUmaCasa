################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../EraUmaVezUmaCasa.c \
../ls_atmega328.c \
../ls_hd44780.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
EraUmaVezUmaCasa.o \
ls_atmega328.o \
ls_hd44780.o

OBJS_AS_ARGS +=  \
EraUmaVezUmaCasa.o \
ls_atmega328.o \
ls_hd44780.o

C_DEPS +=  \
EraUmaVezUmaCasa.d \
ls_atmega328.d \
ls_hd44780.d

C_DEPS_AS_ARGS +=  \
EraUmaVezUmaCasa.d \
ls_atmega328.d \
ls_hd44780.d

OUTPUT_FILE_PATH +=EraUmaVezUmaCasa.elf

OUTPUT_FILE_PATH_AS_ARGS +=EraUmaVezUmaCasa.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler







./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Users\Gustavo\Documents\IFSC\0-Softwares\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Users\Gustavo\Documents\IFSC\0-Softwares\AtmelStudio\7.0\Packs\atmel\ATmega_DFP\1.0.90\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "C:\Users\Gustavo\Documents\IFSC\0-Softwares\AtmelStudio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega328p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.9.2
	$(QUOTE)C:\Users\Gustavo\Documents\IFSC\0-Softwares\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="EraUmaVezUmaCasa.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega328p -B "C:\Users\Gustavo\Documents\IFSC\0-Softwares\AtmelStudio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega328p"  
	@echo Finished building target: $@
	"C:\Users\Gustavo\Documents\IFSC\0-Softwares\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "EraUmaVezUmaCasa.elf" "EraUmaVezUmaCasa.hex"
	"C:\Users\Gustavo\Documents\IFSC\0-Softwares\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "EraUmaVezUmaCasa.elf" "EraUmaVezUmaCasa.eep" || exit 0
	"C:\Users\Gustavo\Documents\IFSC\0-Softwares\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "EraUmaVezUmaCasa.elf" > "EraUmaVezUmaCasa.lss"
	"C:\Users\Gustavo\Documents\IFSC\0-Softwares\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "EraUmaVezUmaCasa.elf" "EraUmaVezUmaCasa.srec"
	"C:\Users\Gustavo\Documents\IFSC\0-Softwares\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "EraUmaVezUmaCasa.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "EraUmaVezUmaCasa.elf" "EraUmaVezUmaCasa.a" "EraUmaVezUmaCasa.hex" "EraUmaVezUmaCasa.lss" "EraUmaVezUmaCasa.eep" "EraUmaVezUmaCasa.map" "EraUmaVezUmaCasa.srec" "EraUmaVezUmaCasa.usersignatures"
	