set(DEPENDENT_MP_BIN2HEXPicTime_default_cVwh67nv "c:/Program Files/Microchip/xc16/v2.10/bin/xc16-bin2hex.exe")
set(DEPENDENT_DEPENDENT_TARGET_ELFPicTime_default_cVwh67nv ${CMAKE_CURRENT_LIST_DIR}/../../../../out/PicTime/default.elf)
set(DEPENDENT_TARGET_DIRPicTime_default_cVwh67nv ${CMAKE_CURRENT_LIST_DIR}/../../../../out/PicTime)
set(DEPENDENT_BYPRODUCTSPicTime_default_cVwh67nv ${DEPENDENT_TARGET_DIRPicTime_default_cVwh67nv}/${sourceFileNamePicTime_default_cVwh67nv}.s)
add_custom_command(
    OUTPUT ${DEPENDENT_TARGET_DIRPicTime_default_cVwh67nv}/${sourceFileNamePicTime_default_cVwh67nv}.s
    COMMAND ${DEPENDENT_MP_BIN2HEXPicTime_default_cVwh67nv} ${DEPENDENT_DEPENDENT_TARGET_ELFPicTime_default_cVwh67nv} --image ${sourceFileNamePicTime_default_cVwh67nv} ${addressPicTime_default_cVwh67nv} ${modePicTime_default_cVwh67nv} -mdfp=C:/Users/vofy/.mchp_packs/Microchip/PIC24F-GA-GB_DFP/1.10.375/xc16 
    WORKING_DIRECTORY ${DEPENDENT_TARGET_DIRPicTime_default_cVwh67nv}
    DEPENDS ${DEPENDENT_DEPENDENT_TARGET_ELFPicTime_default_cVwh67nv})
add_custom_target(
    dependent_produced_source_artifactPicTime_default_cVwh67nv 
    DEPENDS ${DEPENDENT_TARGET_DIRPicTime_default_cVwh67nv}/${sourceFileNamePicTime_default_cVwh67nv}.s
    )
