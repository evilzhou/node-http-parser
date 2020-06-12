{
  'target_defaults': {
    'default_configuration': 'Debug',
    'configurations': {
      'Debug': {
        'defines': [ 'DEBUG', '_DEBUG' ],
        'cflags': [ '-Wall', '-Wextra', '-O0', '-g', '-ftrapv' ],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'RuntimeLibrary': 1, # static debug
          },
        },
      },
      'Release': {
        'defines': [ 'NDEBUG' ],
        'cflags': [ '-Wall', '-Wextra', '-O3' ],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'RuntimeLibrary': 0, # static release
          },
        },
      }
    },
    'msvs_settings': {
      'VCCLCompilerTool': {
      },
      'VCLibrarianTool': {
      },
      'VCLinkerTool': {
        'GenerateDebugInformation': 'true',
      },
    },
    'conditions': [
      ['OS == "win"', {
        'defines': [
          'WIN32'
        ],
      }]
    ],
  },

  'targets': [ 
    {
      'target_name': 'node-http-parser',
      'sources': ['addon.cc', 'http_parser.c'],
      "cflags!": [ '-fno-exceptions' ],
      "cflags_cc!": [ '-fno-exceptions' ],
      'include_dirs': [
        ".",
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'direct_dependent_settings': {
        'defines': [ 'HTTP_PARSER_STRICT=0' ],
        'include_dirs': [ '.' ],
      },
      'defines': [ 
        'NAPI_DISABLE_CPP_EXCEPTIONS', 
        'HTTP_PARSER_STRICT=0' 
      ],
      'conditions': [
        ['OS=="win"', {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'CompileAs': 2,
            },
          },
        }]
      ],
    }
  ]
}