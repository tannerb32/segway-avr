################################################################################
# PROJECT: Educational Robot Firmware                                          #
################################################################################

#---------------------------------------------------------------------
# COMPILER, COMPILER FLAGS, AND TARGET PROGRAM NAME
#---------------------------------------------------------------------
PROJECT	= Segbot
TARGET	= $(PROJECT).elf

## Select the type of robot to use

# Definitions for the Junior Educational Robot Kit
ROBOT=-DROBOT=3 -DUSART0_BAUD=19200

# Definitions for the Educational Robot Kit Version 1.0
#ROBOT=-DROBOT=1 -DUSART0_BAUD=19200

NO_BEHAVIOUR_TREE_USE_FLAGS += -DLEFT_MOTOR_GAIN=1 -DRIGHT_MOTOR_GAIN=1 -DAUTO_START=1.0 # Enable this if no behaviour tree is used.

USE_FLAGS = # USE_FLAGS define which part of the firmware is compiled and included
USE_FLAGS += -DUSE_LEDS # Enable LEDs
USE_FLAGS += -DUSE_USART0 # Enable serial port 0
USE_FLAGS += -DHIGH_RES # Enable 10 bit ADC resolution
USE_FLAGS += -DUSE_LCD # Enable the LCD output
USE_FLAGS += -DUSE_MOTOR # Enable DC motors connected to PWMs
USE_FLAGS += -DUSE_ADC # Enable analog to digital converter
USE_FLAGS += -DUSE_LIGHT_SENSORS # Enable the light sensors, requires USE_ADC
USE_FLAGS += -DUSE_ACCELEROMETER # Enable the accelerometer, requires USE_ADC
USE_FLAGS += -DUSE_BEHAVIOUR # Enable the behaviour tree
USE_FLAGS += -DUSE_MONITOR # Enable monitor thread via serial port USART0
USE_FLAGS += -DUSE_BUTTONS # Enable the buttons (Start, B1) on the board
USE_FLAGS += -DUSE_SOUND # Enable sound generation
#USE_FLAGS += $(NO_BEHAVIOUR_TREE_USE_FLAGS)

# Various debugging flags
# DEBUG_LCD_BEHAVIOUR_TREE = enable debugging of the behaviour tree on the LCD
# DEBUG_USART0_BEHAVIOUR_TREE = enable debugging of the behaviour tree via serial console at 19200 8N1
DEBUG_FLAGS= -DDEBUG_LCD_TIMER_INTERVAL # -DDEBUG_LCD_BEHAVIOUR_TREE #-DDEBUG_USART0_BEHAVIOUR_TREE

# Various flags to create a small applications to test various subsystems

#-DTEST_LCD -DUSE_LCD -DUSE_ADC -DTEST_TIMER_TICKS -DUSE_TIMER2 -DTEST_USART0 -DUSE_USART0 -DTEST_MOTOR -DUSE_MOTOR
#TEST_FLAGS=-DTEST_LCD -DUSE_LCD -DTEST_USART0 -DUSE_USART0 -DTEST_MOTOR -DUSE_MOTOR

TEST_FLAGS=
#TEST_FLAGS += -DTEST_LCD # Start two tasks to test kernel context switch and sleep as well as the LCD
#TEST_FLAGS += -DTEST_LEDS # Start a task to control the LEDs
#TEST_FLAGS += -DTEST_MOTOR_H_BRIDGE # Enable testing of the H bridge, prints to LCD, this happens before the kernel is up and interrupts are enabled.
#TEST_FLAGS += -DTEST_MOTOR # Start a task to test the motor functionality
#TEST_FLAGS += -DTEST_USART0 # Start a task to send a message via serial port USART0
#TEST_FLAGS += -DTEST_ADC
TEST_FLAGS += -DTEST_LIGHT_SENSORS
#TEST_FLAGS += -DTEST_TIMER_TICKS
#TEST_FLAGS += -DTEST_BUTTONS
TEST_FLAGS += -DTEST_SOUND
#TEST_FLAGS += -DTEST_ALL -DTEST_LCD -DTEST_SOUND # Enable complete system check on start up

CC      = avr-gcc
CX      = avr-g++
MCU     = atmega128
LDCC    = $(CC)
DIR_DEPS= .dep
DIR_OBJS= .obj
DIR_BHVR= BehaviourTree
DIR_DRVS= Drivers
DIR_KRNL= Kernel

INCLUDES= -I. -I./$(DIR_BHVR) -I./$(DIR_DRVS) -I./$(DIR_KRNL)

## Options common to compile, link and assembly rules
COMMON  = -mmcu=$(MCU)

## Compile options common for all C compilation units.

CCFLAGS = $(COMMON)
CCFLAGS += -Wall -gdwarf-2 -std=gnu99
CCFLAGS += -DF_CPU=16000000UL 
## -Os -mcall-prologues is the optimization recommended by 
## the AVR libc documentation
CCFLAGS += -Os -mcall-prologues

CCFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CCFLAGS += -MD -MP -MT $(DIR_OBJS)/$(*F).o -MF $(DIR_DEPS)/$(@F).d
CCFLAGS += $(ROBOT)
CCFLAGS += $(DEBUG_FLAGS)
CCFLAGS += $(USE_FLAGS)
CCFLAGS += $(TEST_FLAGS)

CXFLAGS = $(CCFLAGS)

## Assembly specific flags
ASMFLAGS = $(COMMON) $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += -Wl,-Map=$(PROJECT).map

## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature
HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


#---------------------------------------------------------------------
# FILES
#---------------------------------------------------------------------
HEADERS=$(DIR_BHVR)/robot.h 

SOURCES= main.c \
		$(DIR_BHVR)/robot.c

OBJECTS=$(DIR_OBJS)/main.o \
		$(DIR_OBJS)/$(DIR_BHVR)/robot.o 


# Deal with some of the dependencies just to make sure

# Make sure we have USE_ADC if we want to use the light sensor
ifneq (,$(findstring USE_LIGHT,$(USE_FLAGS)))
   ifeq (,$(findstring USE_ADC,$(USE_FLAGS)))
      USE_FLAGS += -DUSE_ADC
   endif
endif

# Make sure we have USE_ADC if we want to use the light sensor
ifneq (,$(findstring TEST_ADC,$(TEST_FLAGS)))
   ifeq (,$(findstring USE_ADC,$(USE_FLAGS)))
      USE_FLAGS += -DUSE_ADC
   endif
endif

# Make sure that we enable the LCD if we enable LCD based debugging
ifneq (,$(findstring DEBUG_LCD,$(DEBUG_FLAGS)))
  ifeq (,$(findstring USE_LCD,$(USE_FLAGS)))
    USE_FLAGS += -DUSE_LCD
  endif
endif

# Make sure that we enable serial port USART0 if we use it for debugging
ifneq (,$(findstring DEBUG_USART0,$(DEBUG_FLAGS)))
  ifeq (,$(findstring USE_USART0,$(USE_FLAGS)))
    USE_FLAGS += -DUSE_USART0
  endif
endif

# Make sure that we enable serial port USART0 if we use it for debugging
ifneq (,$(findstring USE_BEHAVIOUR,$(USE_FLAGS)))
  ifeq (,$(findstring $(NO_BEHAVIOUR_TREE_USE_FLAGS),$(USE_FLAGS)))
    USE_FLAGS += $(NO_BEHAVIOUR_TREE_USE_FLAGS)
  endif
endif

# Optional components specified using USE_ flags

ifneq (,$(findstring USE_LCD,$(USE_FLAGS)))
  HEADERS += $(DIR_DRVS)/lcd_driver.h
  SOURCES += $(DIR_DRVS)/lcd_driver.c
  OBJECTS += $(DIR_OBJS)/$(DIR_DRVS)/lcd_driver.o
endif

ifneq (, $(findstring USE_MOTOR,$(USE_FLAGS)))
  HEADERS += $(DIR_DRVS)/motor_driver.h
  SOURCES += $(DIR_DRVS)/motor_driver.c
  OBJECTS += $(DIR_OBJS)/$(DIR_DRVS)/motor_driver.o
endif

ifneq (,$(findstring USE_TOUCH,$(USE_FLAGS)))
  HEADERS += $(DIR_DRVS)/touch_driver.h
  SOURCES += $(DIR_DRVS)/touch_driver.c
  OBJECTS += $(DIR_OBJS)/$(DIR_DRVS)/touch_driver.o
endif

ifneq (,$(findstring USE_USART,$(USE_FLAGS)))
  HEADERS += $(DIR_KRNL)/serial.h $(DIR_KRNL)/circular.h
  SOURCES += $(DIR_KRNL)/serial.c $(DIR_KRNL)/circular.c
  OBJECTS += $(DIR_OBJS)/$(DIR_KRNL)/serial.o $(DIR_OBJS)/$(DIR_KRNL)/circular.o
endif

ifneq (,$(findstring USE_ADC,$(USE_FLAGS)))
  HEADERS += $(DIR_KRNL)/adc.h
  SOURCES += $(DIR_KRNL)/adc.c
  OBJECTS += $(DIR_OBJS)/$(DIR_KRNL)/adc.o
endif

ifneq (,$(findstring USE_BUTTONS,$(USE_FLAGS)))
  HEADERS += $(DIR_DRVS)/buttons.h
  SOURCES += $(DIR_DRVS)/buttons.c
  OBJECTS += $(DIR_OBJS)/$(DIR_DRVS)/buttons.o
endif

ifneq (,$(findstring USE_LEDS,$(USE_FLAGS)))
  HEADERS += $(DIR_DRVS)/led.h
  SOURCES += $(DIR_DRVS)/led.c
  OBJECTS += $(DIR_OBJS)/$(DIR_DRVS)/led.o
endif

ifneq (,$(findstring USE_SOUND,$(USE_FLAGS)))
  HEADERS += $(DIR_DRVS)/sound_driver.h
  SOURCES += $(DIR_DRVS)/sound_driver.c
  OBJECTS += $(DIR_OBJS)/$(DIR_DRVS)/sound_driver.o
endif


#TOOL_PATH=C:\Program Files (x86)\Atmel\AVR Tools\AVR Toolchain\bin\

#---------------------------------------------------------------------
# COMPILING RULES
#---------------------------------------------------------------------
all: clean default

default: $(TARGET) $(PROJECT).bin $(PROJECT).hex $(PROJECT).eep $(PROJECT).lss print_size

$(TARGET): make_directory $(OBJECTS)
	$(TOOL_PATH)$(LDCC) $(LDFLAGS) $(OBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.bin: %.hex
	$(TOOL_PATH)avr-objcopy -I ihex -O binary $< $@

%.hex: $(TARGET)
	$(TOOL_PATH)avr-objcopy -O ihex $(HEX_FLASH_FLAGS) $< $@

%.eep: $(TARGET)
	$(TOOL_PATH)avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	$(TOOL_PATH)avr-objdump -h -S $< > $@

make_directory:
	$(TOOL_PATH)mkdir -p $(DIR_DEPS)/ $(DIR_OBJS)/ $(DIR_OBJS)/$(DIR_BHVR)/ $(DIR_OBJS)/$(DIR_DRVS)/ $(DIR_OBJS)/$(DIR_KRNL)/

print_size: ${TARGET}
	@$(TOOL_PATH)echo
	@$(TOOL_PATH)avr-size -A ${TARGET} #-C --mcu=${MCU}

$(DIR_OBJS)/$(DIR_BHVR)/%.o: $(DIR_BHVR)/%.c
	$(TOOL_PATH)$(CC) $(INCLUDES) $(CCFLAGS) -c $? -o $@

$(DIR_OBJS)/$(DIR_BHVR)/%.o: $(DIR_BHVR)/%.cpp
	$(TOOL_PATH)$(CX) $(INCLUDES) $(CXFLAGS) -c $? -o $@

$(DIR_OBJS)/$(DIR_DRVS)/%.o: $(DIR_DRVS)/%.c
	$(TOOL_PATH)$(CC) $(INCLUDES) $(CCFLAGS) -c $? -o $@

$(DIR_OBJS)/$(DIR_DRVS)/%.o: $(DIR_DRVS)/%.cpp
	$(TOOL_PATH)$(CX) $(INCLUDES) $(CXFLAGS) -c $? -o $@

$(DIR_OBJS)/$(DIR_KRNL)/%.o: $(DIR_KRNL)/%.c
	$(TOOL_PATH)$(CC) $(INCLUDES) $(CCFLAGS) -c $? -o $@

$(DIR_OBJS)/$(DIR_KRNL)/%.o: $(DIR_KRNL)/%.cpp
	$(TOOL_PATH)$(CX) $(INCLUDES) $(CXFLAGS) -c $? -o $@

$(DIR_OBJS)/%.o: %.c
	$(TOOL_PATH)$(CC) $(INCLUDES) $(CCFLAGS) -c $? -o $@

$(DIR_OBJS)/%.o: %.cpp
	$(TOOL_PATH)$(CX) $(INCLUDES) $(CXFLAGS) -c $? -o $@

## Clean target
.PHONY: clean
clean:
	-$(TOOL_PATH)rm -rf $(OBJECTS) $(TARGET) $(PROJECT).hex $(PROJECT).eep $(PROJECT).lss $(PROJECT).map $(DIR_DEPS) $(DIR_OBJS)

