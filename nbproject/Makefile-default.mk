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
SOURCEFILES_QUOTED_IF_SPACED=src/core/options.c src/core/stopwatch.c src/drivers/buttons.c src/drivers/lcd.c src/drivers/rtcc.c src/ui/state.c src/ui/views.c src/main.c src/drivers/interrupts.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/core/options.o ${OBJECTDIR}/src/core/stopwatch.o ${OBJECTDIR}/src/drivers/buttons.o ${OBJECTDIR}/src/drivers/lcd.o ${OBJECTDIR}/src/drivers/rtcc.o ${OBJECTDIR}/src/ui/state.o ${OBJECTDIR}/src/ui/views.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/drivers/interrupts.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/core/options.o.d ${OBJECTDIR}/src/core/stopwatch.o.d ${OBJECTDIR}/src/drivers/buttons.o.d ${OBJECTDIR}/src/drivers/lcd.o.d ${OBJECTDIR}/src/drivers/rtcc.o.d ${OBJECTDIR}/src/ui/state.o.d ${OBJECTDIR}/src/ui/views.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/drivers/interrupts.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/core/options.o ${OBJECTDIR}/src/core/stopwatch.o ${OBJECTDIR}/src/drivers/buttons.o ${OBJECTDIR}/src/drivers/lcd.o ${OBJECTDIR}/src/drivers/rtcc.o ${OBJECTDIR}/src/ui/state.o ${OBJECTDIR}/src/ui/views.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/drivers/interrupts.o

# Source Files
SOURCEFILES=src/core/options.c src/core/stopwatch.c src/drivers/buttons.c src/drivers/lcd.c src/drivers/rtcc.c src/ui/state.c src/ui/views.c src/main.c src/drivers/interrupts.c



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
${OBJECTDIR}/src/core/options.o: src/core/options.c  .generated_files/flags/default/956665c6f569b5438357b4939ce79db0b7c330f8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/options.o.d 
	@${RM} ${OBJECTDIR}/src/core/options.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/options.c  -o ${OBJECTDIR}/src/core/options.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/core/options.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
	
${OBJECTDIR}/src/drivers/lcd.o: src/drivers/lcd.c  .generated_files/flags/default/c6cac3f0b24607e154b405f568aa56e5f6f819c4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/lcd.c  -o ${OBJECTDIR}/src/drivers/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/lcd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/rtcc.o: src/drivers/rtcc.c  .generated_files/flags/default/b438ecc7e000c3e4cdb44aeb4962f31d5ec3f213 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/rtcc.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/rtcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/rtcc.c  -o ${OBJECTDIR}/src/drivers/rtcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/rtcc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/ui/state.o: src/ui/state.c  .generated_files/flags/default/18a054bcc869f3d8d1fbd22186b896f31b8bd9cd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/ui" 
	@${RM} ${OBJECTDIR}/src/ui/state.o.d 
	@${RM} ${OBJECTDIR}/src/ui/state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ui/state.c  -o ${OBJECTDIR}/src/ui/state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/ui/state.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/ui/views.o: src/ui/views.c  .generated_files/flags/default/fef88ea3c7d55363d4fbcc866b217b068f98b9b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/ui" 
	@${RM} ${OBJECTDIR}/src/ui/views.o.d 
	@${RM} ${OBJECTDIR}/src/ui/views.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ui/views.c  -o ${OBJECTDIR}/src/ui/views.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/ui/views.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/f71ffef8148b542cb2d444eb4d82595c496730b4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/interrupts.o: src/drivers/interrupts.c  .generated_files/flags/default/5909d01f5733f23de0e9c2e88052809e116ff191 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/interrupts.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/interrupts.c  -o ${OBJECTDIR}/src/drivers/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/interrupts.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/src/core/options.o: src/core/options.c  .generated_files/flags/default/cc6560b6834f47474f03162fba6a5a75e80f69f4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/options.o.d 
	@${RM} ${OBJECTDIR}/src/core/options.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/options.c  -o ${OBJECTDIR}/src/core/options.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/core/options.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
	
${OBJECTDIR}/src/drivers/lcd.o: src/drivers/lcd.c  .generated_files/flags/default/a8545f7c2af392abc3020311ea87af32cd7951e2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/lcd.c  -o ${OBJECTDIR}/src/drivers/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/lcd.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/rtcc.o: src/drivers/rtcc.c  .generated_files/flags/default/88c0b668e9d4c42d38d960d0fa16865c33c942b6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/rtcc.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/rtcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/rtcc.c  -o ${OBJECTDIR}/src/drivers/rtcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/rtcc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/ui/state.o: src/ui/state.c  .generated_files/flags/default/bd08df044493c1388257d45404a81e6d92777017 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/ui" 
	@${RM} ${OBJECTDIR}/src/ui/state.o.d 
	@${RM} ${OBJECTDIR}/src/ui/state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ui/state.c  -o ${OBJECTDIR}/src/ui/state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/ui/state.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/ui/views.o: src/ui/views.c  .generated_files/flags/default/44f7e066c0a11c87666635b52b907f31cf68dc0a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/ui" 
	@${RM} ${OBJECTDIR}/src/ui/views.o.d 
	@${RM} ${OBJECTDIR}/src/ui/views.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ui/views.c  -o ${OBJECTDIR}/src/ui/views.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/ui/views.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/316423bc2eeb98761b4051a3747b84ec984be183 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/drivers/interrupts.o: src/drivers/interrupts.c  .generated_files/flags/default/5f0bf70257108319c6abfaa70447337ebc265bd3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/interrupts.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/interrupts.c  -o ${OBJECTDIR}/src/drivers/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/drivers/interrupts.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
