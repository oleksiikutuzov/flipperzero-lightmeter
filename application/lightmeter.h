#pragma once

#include <furi.h>
#include <furi_hal.h>

#include <stream/stream.h>
#include <flipper_format/flipper_format_i.h>

#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>

#include "gui/views/main_view.h"

#include <gui/modules/widget.h>
#include <gui/modules/variable_item_list.h>

#include "gui/scenes/config/lightmeter_scene.h"
#include <notification/notification_messages.h>

#include "lightmeter_config.h"
#include <BH1750.h>

#define APP_PATH_DIR "/ext/apps_data/lightmeter"
#define APP_PATH_CFG "config.txt"

typedef struct {
    uint8_t iso;
    uint8_t nd;
    uint8_t aperture;
    uint8_t dome;
    uint8_t backlight;
    uint8_t lux_only;
    uint8_t measurement_resolution;
    // uint8_t needed to use flipper_format_write_hex
    // int32_t coupled with flipper_format_write_int32 makes stack overflow for unknown reason
} LightMeterConfig;

typedef struct {
    Gui* gui;
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    MainView* main_view;
    VariableItemList* var_item_list;
    LightMeterConfig* config;
    NotificationApp* notifications;
    Widget* widget;

    Storage* storage;
    FuriString* cfg_path;
} LightMeterApp;

typedef enum {
    LightMeterAppViewMainView,
    LightMeterAppViewConfigView,
    LightMeterAppViewVarItemList,
    LightMeterAppViewAbout,
    LightMeterAppViewHelp,
} LightMeterAppView;

typedef enum {
    LightMeterAppCustomEventReset,
    LightMeterAppCustomEventConfig,
    LightMeterAppCustomEventHelp,
    LightMeterAppCustomEventAbout,
} LightMeterAppCustomEvent;

void lightmeter_app_set_config(LightMeterApp* context, LightMeterConfig* config);

void lightmeter_app_i2c_callback(LightMeterApp* context);

void lightmeter_app_reset_callback(LightMeterApp* context);
