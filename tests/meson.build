katze_test_sources = files(
  'doctest.cpp',
  'core/testAlign.cpp',
  'core/testBVec2.cpp',
  'core/testEdges.cpp',
  'core/testRect.cpp',
  'core/testVec2.cpp',
)

executable(
  meson.project_name() + '-tests',
  katze_sources + katze_test_sources,
  dependencies: dependencies,
  include_directories: include_dir,
)
