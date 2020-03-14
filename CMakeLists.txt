cmake_minimum_required (VERSION 2.8)
project("WiRay")

include("CMakeConfig.txt")

include_directories(ext)

add_executable(WiRay

  include/nori/bbox.h
  include/nori/bitmap.h
  include/nori/block.h
  include/nori/bsdf.h
  include/nori/bvh.h
  include/nori/camera.h
  include/nori/color.h
  include/nori/common.h
  include/nori/dpdf.h
  include/nori/frame.h
  include/nori/gui.h
  include/nori/integrator.h
  include/nori/emitter.h
  include/nori/kdtree.h
  include/nori/mesh.h
  include/nori/object.h
  include/nori/parser.h
  include/nori/proplist.h
  include/nori/photon.h
  include/nori/ray.h
  include/nori/render.h
  include/nori/rfilter.h
  include/nori/sampler.h
  include/nori/scene.h
  include/nori/shape.h
  include/nori/texture.h
  include/nori/timer.h
  include/nori/transform.h
  include/nori/vector.h
  include/nori/warp.h
  include/nori/envmap.h
  include/nori/homogeneous.h

  src/Core/bitmap.cpp
  src/Core/block.cpp
  src/Accelerator/bvh.cpp
  src/Core/chi2test.cpp
  src/Core/common.cpp
  src/Texture/consttexture.cpp
  src/Core/checkerboard.cpp
  src/BSDFs/diffuse.cpp
  src/Core/gui.cpp
  src/Sampler/independent.cpp
  src/Core/main.cpp
  src/Core/mesh.cpp
  src/Core/obj.cpp
  src/Core/object.cpp
  src/Core/parser.cpp
  src/Core/perspective.cpp
  src/Core/proplist.cpp
  src/Core/render.cpp
  src/Core/rfilter.cpp
  src/Core/scene.cpp
  src/Core/shape.cpp
  src/Core/ttest.cpp
  src/Core/warp.cpp
  src/BSDFs/microfacet.cpp
  src/Intergrators/photon.cpp
  src/BSDFs/mirror.cpp
  src/BSDFs/dielectric.cpp
  src/Intergrators/photonmapper.cpp
  src/Core/sphere.cpp
  src/Lights/arealight.cpp
  src/Intergrators/normal.cpp
  src/Intergrators/ao.cpp
  src/Lights/pointlight.cpp
  src/Intergrators/direct_ems.cpp
  src/Intergrators/direct_mats.cpp
  src/Intergrators/direct_mis.cpp
  src/Intergrators/path.cpp
  src/Cameras/dof_camera.cpp
  src/BSDFs/disney.cpp
  src/Lights/envmap.cpp
  src/Lights/envlight.cpp
  src/Volumes/homogeneous.cpp
  src/Intergrators/volpath.cpp
)


add_executable(warptest
  include/nori/warp.h
  src/Core/warp.cpp
  src/Core/warptest.cpp
  src/BSDFs/microfacet.cpp
  src/Core/object.cpp
  src/Core/proplist.cpp
  src/Core/common.cpp
)

add_executable(tonemapper
        include/nori/bitmap.h
        src/Core/bitmap.cpp
        src/Core/common.cpp
        src/hdrToLdr.cpp)


add_dependencies(WiRay OpenEXR_p)
add_dependencies(WiRay nanogui_p)
add_dependencies(WiRay tbb_p)
add_dependencies(WiRay pugixml)
add_dependencies(warptest WiRay)
add_dependencies(tonemapper WiRay)

# Link to dependency libraries
target_link_libraries(WiRay ${extra_libs})
target_link_libraries(warptest ${extra_libs})
target_link_libraries(tonemapper ${extra_libs})

