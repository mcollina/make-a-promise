{
  "targets": [
    {
      "target_name": "make_promise",
      "cflags!": [ "--std=c++11 -fno-exceptions -fno-strict-aliasing" ],
      "cflags_cc!": [ "--std=c++11 -fno-exceptions -fno-strict-aliasing" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      "sources": [
        "./promise.cc"
      ],
    }
  ]
}
