set(SRCS
    inf/log.cpp
    inf/file.cpp
    inf/audio.cpp
    core/utils/textutils.cpp
    core/sprite/trigger.cpp
    core/sprite/textsprite.cpp
    core/sprite/rectsprite.cpp
    core/sprite/listsprite.cpp
    core/sprite/imagesprite.cpp
    core/sprite/container.cpp
    core/sprite/charactersprite.cpp
    core/sprite/charactershadowsprite.cpp
    core/sprite/animationsprite.cpp
    core/object/variableobject.cpp
    core/object/characterobject.cpp
    core/data/image.cpp
    core/data/equip.cpp
    core/assets/sheetassets.cpp
    core/assets/imageassets.cpp
    core/action/walkaction.cpp
    core/action/sheetaction.cpp
    core/action/popaction.cpp
    core/action/moveaction.cpp
    core/action/floataction.cpp
    core/action/action.cpp
    core/variable.cpp
    core/stage.cpp
    core/scriptfunction.cpp
    core/script.cpp
    core/render.cpp
    core/paintevent.cpp
    core/line.cpp
    core/game.cpp
    core/font.cpp
    core/archive.cpp
    core/actuator.cpp
    screen.c
    card.c
    button.c
    audio.c
    main.cpp
)

idf_component_register(SRCS ${SRCS} 
                    INCLUDE_DIRS .
                    PRIV_REQUIRES esp_lcd esp_lcd_st7735
                    REQUIRES fatfs sd_card esp_driver_i2s esp_driver_gpio
                    WHOLE_ARCHIVE)
