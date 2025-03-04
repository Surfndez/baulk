//
#include <type_traits>
#include <hazel/hazel.hpp>
#include <bela/path.hpp>
#include <bela/os.hpp>
#include "ina/hazelinc.hpp"

namespace hazel {

typedef hazel::internal::status_t (*lookup_handle_t)(bela::bytes_view bv, hazel_result &hr);

bool LookupBytes(bela::bytes_view bv, hazel_result &hr, bela::error_code &) {
  if (auto p = memchr(bv.data(), 0, bv.size()); p != nullptr) {
    hr.zeroPosition = static_cast<int64_t>(reinterpret_cast<const uint8_t *>(p) - bv.data());
  }

  constexpr lookup_handle_t handles[] = {
      hazel::internal::LookupExecutableFile, //
      hazel::internal::LookupArchives,       // 7z ...
      hazel::internal::LookupDocs,
      hazel::internal::LookupFonts,     //
      hazel::internal::LookupShellLink, // shortcut
      hazel::internal::LookupMedia,     // media
      hazel::internal::LookupImages,    // images
      hazel::internal::LookupText,
  };
  for (auto h : handles) {
    if (h(bv, hr) == hazel::internal::Found) {
      return true;
    }
  }
  return false;
}

bool LookupFile(const bela::io::FD &fd, hazel_result &hr, bela::error_code &ec, int64_t offset) {
  if ((hr.size_ = fd.Size(ec)) == bela::SizeUnInitialized) {
    return false;
  }
  if (offset < 0 || hr.size_ < offset) {
    ec = bela::make_error_code(ErrGeneral, L"file offset over size");
    return false;
  }
  uint8_t buffer[4096];
  auto minSize = (std::min)(hr.size_ - offset, 4096ll);
  if (!fd.ReadAt({buffer, static_cast<size_t>(minSize)}, offset, ec)) {
    return false;
  }
  bela::bytes_view bv(buffer, static_cast<size_t>(minSize));
  return LookupBytes(bv, hr, ec);
}

} // namespace hazel