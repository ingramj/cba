require 'ffi'

module CBitArray
  extend FFI::Library
  ffi_lib 'cba'
  attach_function 'cba_true', [], :int
end
