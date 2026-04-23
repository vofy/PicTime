#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/PicTime.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/PicTime.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/core/alarm.c src/core/clock.c src/core/options.c src/core/state.c src/core/stopwatch.c src/drivers/buttons.c src/drivers/eeprom.c src/drivers/interrupt.c src/drivers/lcd.c src/drivers/led.c src/drivers/rtcc.c src/main.c src/drivers/controller.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/core/alarm.o ${OBJECTDIR}/src/core/clock.o ${OBJECTDIR}/src/core/options.o ${OBJECTDIR}/src/core/state.o ${OBJECTDIR}/src/core/stopwatch.o ${OBJECTDIR}/src/drivers/buttons.o ${OBJECTDIR}/src/drivers/eeprom.o ${OBJECTDIR}/src/drivers/interrupt.o ${OBJECTDIR}/src/drivers/lcd.o ${OBJECTDIR}/src/drivers/led.o ${OBJECTDIR}/src/drivers/rtcc.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/drivers/controller.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/core/alarm.o.d ${OBJECTDIR}/src/core/clock.o.d ${OBJECTDIR}/src/core/options.o.d ${OBJECTDIR}/src/core/state.o.d ${OBJECTDIR}/src/core/stopwatch.o.d ${OBJECTDIR}/src/drivers/buttons.o.d ${OBJECTDIR}/src/drivers/eeprom.o.d ${OBJECTDIR}/src/drivers/interrupt.o.d ${OBJECTDIR}/src/drivers/lcd.o.d ${OBJECTDIR}/src/drivers/led.o.d ${OBJECTDIR}/src/drivers/rtcc.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/drivers/controller.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/core/alarm.o ${OBJECTDIR}/src/core/clock.o ${OBJECTDIR}/src/core/options.o ${OBJECTDIR}/src/core/state.o ${OBJECTDIR}/src/core/stopwatch.o ${OBJECTDIR}/src/drivers/buttons.o ${OBJECTDIR}/src/drivers/eeprom.o ${OBJECTDIR}/src/drivers/interrupt.o ${OBJECTDIR}/src/drivers/lcd.o ${OBJECTDIR}/src/drivers/led.o ${OBJECTDIR}/src/drivers/rtcc.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/drivers/controller.o

# Source Files
SOURCEFILES=src/core/alarm.c src/core/clock.c src/core/options.c src/core/state.c src/core/stopwatch.c src/drivers/buttons.c src/drivers/eeprom.c src/drivers/interrupt.c src/drivers/lcd.c src/drivers/led.c src/drivers/rtcc.c src/main.c src/drivers/controller.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/PicTime.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ128GA010
MP_LINKER_FILE_OPTION=,--script=p24FJ128GA010.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/core/alarm.o: src/core/alarm.c  .generated_files/flags/default/fa322b896bd70146bcacc155b7939aeda7a081d3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/alarm.o.d 
	@${RM} ${OBJECTDIR}/src/core/alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/alarm.c  -o ${OBJECTDIR}/src/core/alarm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/core/alarm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/core/clock.o: src/core/clock.c  .generated_files/flags/default/7784c4f7f88a794992a7ee59c1d005d3a446b745 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/clock.o.d 
	@${RM} ${OBJECTDIR}/src/core/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/clock.c  -o ${OBJECTDIR}/src/core/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/core/clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/core/options.o: src/core/options.c  .generated_files/flags/default/956665c6f569b5438357b4939ce79db0b7c330f8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/options.o.d 
	@${RM} ${OBJECTDIR}/src/core/options.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/options.c  -o ${OBJECTDIR}/src/core/options.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/core/options.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/core/state.o: src/core/state.c  .generated_files/flags/default/785525c94b475eb318f95cc46a3edf8ffa785895 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/state.o.d 
	@${RM} ${OBJECTDIR}/src/core/state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/state.c  -o ${OBJECTDIR}/src/core/state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/core/state.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/core/stopwatch.o: src/core/stopwatch.c  .generated_files/flags/default/5a6ab0d103e5c36ee1093d15620963013ce35b5c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/stopwatch.o.d 
	@${RM} ${OBJECTDIR}/src/core/stopwatch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/stopwatch.c  -o ${OBJECTDIR}/src/core/stopwatch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/core/stopwatch.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/buttons.o: src/drivers/buttons.c  .generated_files/flags/default/faf674228d0cc4d2c21fe918ad90de37bd92e3e6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/buttons.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/buttons.c  -o ${OBJECTDIR}/src/drivers/buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/buttons.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/eeprom.o: src/drivers/eeprom.c  .generated_files/flags/default/d2f21b1bac8ac66ce45fb5636837666cbba9cb41 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/eeprom.c  -o ${OBJECTDIR}/src/drivers/eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/eeprom.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/interrupt.o: src/drivers/interrupt.c  .generated_files/flags/default/3e2b40a00bcca8c8f62f1a5e98a1118258ec145a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/interrupt.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/interrupt.c  -o ${OBJECTDIR}/src/drivers/interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/interrupt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/lcd.o: src/drivers/lcd.c  .generated_files/flags/default/c6cac3f0b24607e154b405f568aa56e5f6f819c4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/lcd.c  -o ${OBJECTDIR}/src/drivers/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/lcd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/led.o: src/drivers/led.c  .generated_files/flags/default/5ab4b461e76ccbdc37c6281db25862a458d09130 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/led.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/led.c  -o ${OBJECTDIR}/src/drivers/led.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/led.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/rtcc.o: src/drivers/rtcc.c  .generated_files/flags/default/b438ecc7e000c3e4cdb44aeb4962f31d5ec3f213 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/rtcc.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/rtcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/rtcc.c  -o ${OBJECTDIR}/src/drivers/rtcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/rtcc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/f71ffef8148b542cb2d444eb4d82595c496730b4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/controller.o: src/drivers/controller.c  .generated_files/flags/default/2ca0454761479b1c7a13def3514ee108fddfb82b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/controller.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/controller.c  -o ${OBJECTDIR}/src/drivers/controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/controller.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/src/core/alarm.o: src/core/alarm.c  .generated_files/flags/default/c560da654865e95be243fbbb6ae543ea78e98662 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/alarm.o.d 
	@${RM} ${OBJECTDIR}/src/core/alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/alarm.c  -o ${OBJECTDIR}/src/core/alarm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/core/alarm.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/core/clock.o: src/core/clock.c  .generated_files/flags/default/89e6b363e93b0d18e41f1d6c22de16fa5afea20a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/clock.o.d 
	@${RM} ${OBJECTDIR}/src/core/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/clock.c  -o ${OBJECTDIR}/src/core/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/core/clock.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/core/options.o: src/core/options.c  .generated_files/flags/default/cc6560b6834f47474f03162fba6a5a75e80f69f4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/options.o.d 
	@${RM} ${OBJECTDIR}/src/core/options.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/options.c  -o ${OBJECTDIR}/src/core/options.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/core/options.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/core/state.o: src/core/state.c  .generated_files/flags/default/f5df9978375f3f18744a2e6d0e42524f4e365611 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/state.o.d 
	@${RM} ${OBJECTDIR}/src/core/state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/state.c  -o ${OBJECTDIR}/src/core/state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/core/state.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/core/stopwatch.o: src/core/stopwatch.c  .generated_files/flags/default/d61f43dabc2ce754416f0e00b59068b107e144fc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/stopwatch.o.d 
	@${RM} ${OBJECTDIR}/src/core/stopwatch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/stopwatch.c  -o ${OBJECTDIR}/src/core/stopwatch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/core/stopwatch.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/buttons.o: src/drivers/buttons.c  .generated_files/flags/default/83b81fa94ec676a5a88d330da9db7eb645713e0c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/buttons.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/buttons.c  -o ${OBJECTDIR}/src/drivers/buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/buttons.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/eeprom.o: src/drivers/eeprom.c  .generated_files/flags/default/f4776f1839bbd74b6ec90646fc596fc2b5b4958c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/eeprom.c  -o ${OBJECTDIR}/src/drivers/eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/eeprom.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/interrupt.o: src/drivers/interrupt.c  .generated_files/flags/default/4abe408f1f8878d5642844a43a4f6fbd79da8629 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/interrupt.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/interrupt.c  -o ${OBJECTDIR}/src/drivers/interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/interrupt.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/lcd.o: src/drivers/lcd.c  .generated_files/flags/default/a8545f7c2af392abc3020311ea87af32cd7951e2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/lcd.c  -o ${OBJECTDIR}/src/drivers/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/lcd.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/led.o: src/drivers/led.c  .generated_files/flags/default/970664260a633ccfde87ab66d01a507adc70936 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/led.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/led.c  -o ${OBJECTDIR}/src/drivers/led.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/led.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/rtcc.o: src/drivers/rtcc.c  .generated_files/flags/default/88c0b668e9d4c42d38d960d0fa16865c33c942b6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/rtcc.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/rtcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/rtcc.c  -o ${OBJECTDIR}/src/drivers/rtcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/rtcc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/316423bc2eeb98761b4051a3747b84ec984be183 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/controller.o: src/drivers/controller.c  .generated_files/flags/default/8becd8697bfaf4c7623ff75e41fb10df53890aa4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/controller.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/controller.c  -o ${OBJECTDIR}/src/drivers/controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/controller.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/PicTime.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/PicTime.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/PicTime.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/PicTime.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/PicTime.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
