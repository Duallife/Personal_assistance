///ISDN2001/2
#include "setting.h"
#include "scr.h"

static void event_handler(lv_event_t * e);
static void slider_event_cb(lv_event_t * e);
static lv_obj_t * slider_label;
static void anim_x_cb(void * var, int32_t v);
static void sw_event_cb(lv_event_t * e);

void time_task(lv_timer_t * task);
static void time_cb(lv_event_t * e);

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay( 5 );
}

void load_scr1(){
    lv_obj_t * scr1 = lv_obj_create(NULL);
    lv_scr_load(scr1);

    lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_align(btn1, LV_ALIGN_CENTER);

    lv_obj_t * label = lv_label_create(btn1);
    
    lv_label_set_text(label, "Button");
    lv_obj_center(label);
/////////////////////////////////////////////
    lv_obj_t * slider = lv_slider_create(lv_scr_act());
    lv_obj_center(slider);
    lv_obj_set_pos(slider, 0, 50);
    lv_obj_set_width(slider, 200);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    /*Create a label below the slider*/
    slider_label = lv_label_create(lv_scr_act());
    lv_label_set_text(slider_label, "0%");

    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

/////////////////////////
    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_set_style_radius(obj, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_size(obj, 10, 10);
    lv_obj_set_pos(obj,10,10);


    lv_obj_t * sw = lv_switch_create(lv_scr_act());
    lv_obj_center(sw);
    lv_obj_set_pos(sw, 0, -50);
    lv_obj_add_state(sw, LV_STATE_CHECKED);
    lv_obj_add_event_cb(sw, sw_event_cb, LV_EVENT_VALUE_CHANGED, obj);

//////////////////////////////
    // lv_obj_t * time = lv_label_create(lv_scr_act());
    // lv_obj_center(time);
    // lv_obj_set_pos(time,0,100);
    // lv_label_set_text(time, "Finding");
    lv_obj_t * timebtn = lv_btn_create(lv_scr_act());
    lv_obj_center(timebtn);
    lv_obj_set_pos(timebtn, 0, 100);
    lv_obj_add_event_cb(timebtn, time_cb, LV_EVENT_ALL, NULL);


}
//support functions
static void back_cb(lv_event_t * e);
lv_obj_t * scr2;

void load_scr2(){
    scr2 = lv_obj_create(NULL);
    lv_scr_load(scr2);

    lv_obj_t * back = lv_btn_create(scr2);
    lv_obj_center(back);
    lv_obj_set_pos(back, 0, -50);
    lv_obj_add_event_cb(back, back_cb, LV_EVENT_ALL, NULL);
    

    lv_obj_t * time = lv_label_create(scr2);

    static lv_style_t clock_style;
    lv_style_init(&clock_style);
    lv_style_set_text_color(&clock_style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_text_font(&clock_style, &lv_font_montserrat_36);
    lv_obj_add_style(time, &clock_style, 0);

    lv_timer_t * timer = lv_timer_create(time_task, 1000, time);
    lv_timer_ready(timer);
}

static void back_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        load_scr1();
    }
}


void time_task(lv_timer_t * task){
    
    lv_obj_t * time = (lv_obj_t*)task->user_data;
    timeClient.update();
    lv_obj_center(time);
    lv_label_set_text(time, timeClient.getFormattedTime().c_str() );
    
    // static lv_style_t clock_style;
    // lv_style_init(&clock_style);

    // lv_style_set_text_font(&clock_style, LV_FONT_MONTSERRAT_48);
    // lv_obj_add_style(time, &clock_style, 0);
}

static void time_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        load_scr2();
    }
}

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        Serial.println("ihi1");
    }
}

static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
    lv_label_set_text(slider_label, buf);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}

static void anim_x_cb(void * var, int32_t v)
{
    lv_obj_set_x((lv_obj_t *)var, v);
}

static void anim_size_cb(void * var, int32_t v)
{
    lv_obj_set_size((lv_obj_t *)var, v, v);
}

static void sw_event_cb(lv_event_t * e)
{
    lv_obj_t * sw = lv_event_get_target(e);
    lv_obj_t * obj = (lv_obj_t *)lv_event_get_user_data(e);

    if(lv_obj_has_state(sw, LV_STATE_CHECKED)) {
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, obj);
        lv_anim_set_time(&a, 1000);
        lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
        lv_anim_set_exec_cb(&a, anim_size_cb);
        lv_anim_set_values(&a, 50, 10);
        lv_anim_start(&a);
        lv_anim_set_exec_cb(&a, anim_x_cb);
        lv_anim_set_values(&a, 50, 10);
        lv_anim_start(&a);

    } else {
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, obj);
        lv_anim_set_time(&a, 1000);
        lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
        lv_anim_set_exec_cb(&a, anim_x_cb);
        lv_anim_set_values(&a, 10, 50);
        lv_anim_start(&a);
        lv_anim_set_exec_cb(&a, anim_size_cb);
        lv_anim_set_values(&a, 10, 50);
        lv_anim_start(&a);
    }

}