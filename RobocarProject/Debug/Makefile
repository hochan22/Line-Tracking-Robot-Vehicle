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
../ADC.cpp \
../A_Counter.cpp \
../A_Tracing.cpp \
../Button.cpp \
../cplusplus.cpp \
../Cup.cpp \
../LCD.cpp \
../PID.cpp \
../RobocarProject.cpp \
../robocar_ll.cpp \
../servo.cpp \
../Timer.cpp \
../trackTable.cpp \
../wheel.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
ADC.o \
A_Counter.o \
A_Tracing.o \
Button.o \
cplusplus.o \
Cup.o \
LCD.o \
PID.o \
RobocarProject.o \
robocar_ll.o \
servo.o \
Timer.o \
trackTable.o \
wheel.o

OBJS_AS_ARGS +=  \
ADC.o \
A_Counter.o \
A_Tracing.o \
Button.o \
cplusplus.o \
Cup.o \
LCD.o \
PID.o \
RobocarProject.o \
robocar_ll.o \
servo.o \
Timer.o \
trackTable.o \
wheel.o

C_DEPS +=  \
ADC.d \
A_Counter.d \
A_Tracing.d \
Button.d \
cplusplus.d \
Cup.d \
LCD.d \
PID.d \
RobocarProject.d \
robocar_ll.d \
servo.d \
Timer.d \
trackTable.d \
wheel.d

C_DEPS_AS_ARGS +=  \
ADC.d \
A_Counter.d \
A_Tracing.d \
Button.d \
cplusplus.d \
Cup.d \
LCD.d \
PID.d \
RobocarProject.d \
robocar_ll.d \
servo.d \
Timer.d \
trackTable.d \
wheel.d

OUTPUT_FILE_PATH +=RobocarProject.elf

OUTPUT_FILE_PATH_AS_ARGS +=RobocarProject.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler





























./%.o: .././%.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.8.1
	$(QUOTE)D:\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -mmcu=atmega1284p -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
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
	@echo Invoking: AVR8/GNU Linker : 4.8.1
	$(QUOTE)D:\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="RobocarProject.map" -Wl,--start-group -Wl,-llamos -Wl,-lm  -Wl,--end-group -Wl,-L"D:\PolyU\Semester2\Integrated Project\Robocar\RobocarProject\RobocarProject" -Wl,-L"C:\Users\15111567d\Desktop\RobocarProject\RobocarProject" -Wl,-L"F:\RobocarProject\RobocarProject" -Wl,-L"C:\Users\Administrator\Desktop\RobocarProject\RobocarProject" -Wl,-L"E:\RoboCar\demo_week3\RobocarProject" -Wl,-L"C:\Users\lujiale\Desktop\demo_week3\RobocarProject" -Wl,-L"C:\Users\lujiale\Desktop\Working Vrision\RobocarProject" -Wl,-L"C:\Users\lujiale\Desktop\Working Version\RobocarProject" -Wl,-L"C:\Users\lujiale\Desktop\Woring version\RobocarProject" -Wl,-L"F:\car_week8&9\310servo\RobocarProject3" -Wl,-L"C:\Users\student\Desktop\G51_week8\Desktop\Working Version2222"  -Wl,--gc-sections -mrelax -mmcu=atmega1284p  
	@echo Finished building target: $@
	"D:\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "RobocarProject.elf" "RobocarProject.hex"
	"D:\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "RobocarProject.elf" "RobocarProject.eep" || exit 0
	"D:\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "RobocarProject.elf" > "RobocarProject.lss"
	"D:\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "RobocarProject.elf" "RobocarProject.srec"
	"D:\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-size.exe" "RobocarProject.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "RobocarProject.elf" "RobocarProject.a" "RobocarProject.hex" "RobocarProject.lss" "RobocarProject.eep" "RobocarProject.map" "RobocarProject.srec" "RobocarProject.usersignatures"
	