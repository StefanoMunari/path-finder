{
  'targets': [
  {
  'include_dirs': [
    '../../core',
    '/usr/include/boost'
  ],
  'link_settings': {
    'libraries': [
      '-ljsoncpp'
    ],
    'library_dirs': [
      '/usr/include'
    ]
  },
  'target_name': 'ai_interface',
  'sources': [
    '../../core/ai.cc',
    '../../core/graph/graph_encoder.cc',
    '../../core/graph/graph_factory.cc',
    '../../core/graph/graph_observer.cc',
    '../../core/graph/graph_registry.cc',
    '../../core/io/json_reader.cc',
    'ai_interface.cc']
  }]
}