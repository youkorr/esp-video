#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/lvgl/lvgl_esphome.h"

#ifdef USE_ESP32_VARIANT_ESP32P4
#include "../mipi_dsi_cam/mipi_dsi_cam.h"
#include "driver/ppa.h"
#endif

namespace esphome {
namespace lvgl_camera_display {

enum RotationAngle {
  ROTATION_0 = 0,
  ROTATION_90 = 90,
  ROTATION_180 = 180,
  ROTATION_270 = 270
};

class LVGLCameraDisplay : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::LATE; }

  void set_camera(mipi_dsi_cam::MipiDsiCam *camera) { this->camera_ = camera; }
  void configure_canvas(lv_obj_t *canvas);
  void set_update_interval(uint32_t interval_ms) { this->update_interval_ = interval_ms; }
  
  void set_rotation(RotationAngle rotation) { this->rotation_ = rotation; }
  void set_mirror_x(bool enable) { this->mirror_x_ = enable; }
  void set_mirror_y(bool enable) { this->mirror_y_ = enable; }

 protected:
  mipi_dsi_cam::MipiDsiCam *camera_{nullptr};
  
#ifdef USE_ESP32_VARIANT_ESP32P4
  // Buffer d'affichage
  uint8_t *display_buffer_{nullptr};
  size_t frame_size_{0};
  
  // PPA pour transformations
  ppa_client_handle_t ppa_handle_{nullptr};
  uint8_t *transform_buffer_{nullptr};
  size_t transform_buffer_size_{0};
  
  // Méthodes PPA
  bool init_ppa_();
  void deinit_ppa_();
  bool transform_frame_(const uint8_t *src, uint8_t *dst);
#endif

  lv_obj_t *canvas_obj_{nullptr};
  
  uint16_t width_{1280};
  uint16_t height_{720};
  RotationAngle rotation_{ROTATION_0};
  bool mirror_x_{false};
  bool mirror_y_{false};
  uint32_t update_interval_{33};
  
  uint32_t frame_count_{0};
  uint32_t drop_count_{0};
  uint32_t last_frame_sequence_{0};
  uint32_t last_update_time_{0};
  uint32_t last_fps_time_{0};
  bool first_update_{true};
};

}  // namespace lvgl_camera_display
}  // namespace esphome










































































































































