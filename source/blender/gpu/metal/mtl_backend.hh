/** \file
 * \ingroup gpu
 */

#pragma once

#include "BLI_vector.hh"

#include "gpu_backend.hh"
#include "mtl_capabilities.hh"

namespace blender {
namespace gpu {

class Batch;
class DrawList;
class FrameBuffer;
class IndexBuf;
class QueryPool;
class Shader;
class Texture;
class UniformBuf;
class VertBuf;
class MTLContext;

class MTLBackend : public GPUBackend {
  friend class MTLContext;

 public:
  /* Capabilities. */
  static MTLCapabilities capabilities;

  inline ~MTLBackend()
  {
    MTLBackend::platform_exit();
  }

  static bool metal_is_supported();
  inline static MTLBackend *get()
  {
    return static_cast<MTLBackend *>(GPUBackend::get());
  }

  void samplers_update() override;
  inline void compute_dispatch(int groups_x_len, int groups_y_len, int groups_z_len) override
  {
    /* Placeholder */
  }

  /* MTL Allocators need to be implemented in separate .mm files, due to allocation of Objective-C
   * objects. */
  Context *context_alloc(void *ghost_window) override;
  Batch *batch_alloc() override;
  DrawList *drawlist_alloc(int list_length) override;
  FrameBuffer *framebuffer_alloc(const char *name) override;
  IndexBuf *indexbuf_alloc() override;
  QueryPool *querypool_alloc() override;
  Shader *shader_alloc(const char *name) override;
  Texture *texture_alloc(const char *name) override;
  UniformBuf *uniformbuf_alloc(int size, const char *name) override;
  VertBuf *vertbuf_alloc() override;

  /* Render Frame Coordination. */
  void render_begin() override;
  void render_end() override;
  void render_step() override;
  bool is_inside_render_boundary();

 private:
  static void platform_init(MTLContext *ctx);
  static void platform_exit();

  static void capabilities_init(MTLContext *ctx);
};

}  // namespace gpu
}  // namespace blender