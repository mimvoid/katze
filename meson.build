project(
  'katze',
  'cpp',
  version: '0.1.0',
  license: 'MIT',
  default_options: ['warning_level=3', 'cpp_std=c++17', 'default_library=static']
)

dependencies = [
  dependency('sdl3'),
  dependency('sdl3-ttf'),
]

include_dir = include_directories('include')

subdir('include')
subdir('src')

libkatze = library(
  meson.project_name(),
  katze_sources,
  version: meson.project_version(),
  dependencies: dependencies,
  include_directories: include_dir,
  install: true,
)

katze_dep = declare_dependency(
  link_with: libkatze,
  version: meson.project_version(),
  dependencies: dependencies,
  include_directories: include_dir,
)

if get_option('examples')
  subdir('examples')
endif

import('pkgconfig').generate(
  libkatze,
  name: meson.project_name(),
  filebase: meson.project_name(),
  description: 'Dynamic retained GUI library written in C++17',
  version: meson.project_version(),
  requires: dependencies,
)
