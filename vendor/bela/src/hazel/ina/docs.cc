//////////////
#include "hazelinc.hpp"
#include "docs.hpp"
#include <charconv>
#include <bela/ascii.hpp>

namespace hazel::internal {

// RTF format
// https://en.wikipedia.org/wiki/Rich_Text_Format
/*{\rtf1*/
status_t lookup_rtfinternal(bela::bytes_view bv, hazel_result &hr) {
  constexpr uint8_t rtfMagic[] = {0x7B, 0x5C, 0x72, 0x74, 0x66};
  if (!bv.starts_bytes_with(rtfMagic) || bv.size() < 6) {
    return None;
  }
  // {\rtf1
  auto sv = bv.make_string_view(5);
  int version = 0;
  if (auto result = std::from_chars(sv.data(), sv.data() + sv.size(), version); result.ec != std::errc{}) {
    return None;
  }
  hr.assign(types::rtf, L"Rich Text Format");
  hr.append(L"Version", version);
  return Found;
}

// https://en.wikipedia.org/wiki/Compound_File_Binary_Format
// http://www.openoffice.org/sc/compdocfileformat.pdf
// https://interoperability.blob.core.windows.net/files/MS-PPT/[MS-PPT].pdf

status_t LookupDocs(bela::bytes_view bv, hazel_result &hr) {
  constexpr const uint8_t msoleMagic[] = {0xD0, 0xCF, 0x11, 0xE0, 0xA1, 0xB1, 0x1A, 0xE1};
  if (lookup_rtfinternal(bv, hr) == Found) {
    return Found;
  }
  constexpr const auto olesize = sizeof(oleheader_t);
  if (!bv.starts_bytes_with(msoleMagic) || bv.size() < 513) {
    return None;
  }
  if (bv[512] == 0xEC && bv[513] == 0xA5) {
    hr.assign(types::doc, L"Microsoft Word 97-2003");
    return Found;
  }
  if (bv[512] == 0x09 && bv[513] == 0x08) {
    hr.assign(types::doc, L"Microsoft Excel 97-2003");
    return Found;
  }
  if (bv[512] == 0xA0 && bv[513] == 0x46) {
    hr.assign(types::doc, L"Microsoft PowerPoint 97-2003");
    return Found;
  }
  hr.assign(types::msi, L"Windows Installer packages");
  return Found;
}
} // namespace hazel::internal
