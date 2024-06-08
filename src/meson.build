apt_transport_droidian_sources = [
  'main.cpp',
  'transport.cpp',
]

apt_transport_droidian_deps = [
  dependency('apt-pkg'),
]

executable('droidian+http', apt_transport_droidian_sources,
  dependencies: apt_transport_droidian_deps,
  install: true,
  install_dir: get_option('prefix') / 'lib/apt/methods/'
)

install_symlink('droidian+https',
  install_dir: get_option('prefix') / 'lib/apt/methods/',
  pointing_to: 'droidian+http'
)