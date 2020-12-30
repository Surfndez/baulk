//
#ifndef BAULK_ZIP_HPP
#define BAULK_ZIP_HPP
#include <bela/base.hpp>
#include <bela/buffer.hpp>
#include <bela/str_cat_narrow.hpp>
#include <bela/time.hpp>
#include <span>
#include <bela/phmap.hpp>
#include "archive.hpp"

#define BAULK_COMPRESS_LEVEL_DEFAULT (-1)
#define BAULK_COMPRESS_LEVEL_FAST (2)
#define BAULK_COMPRESS_LEVEL_NORMAL (6)
#define BAULK_COMPRESS_LEVEL_BEST (9)

/* BAULK_ZIP_FLAG */
#define BAULK_ZIP_FLAG_ENCRYPTED (1 << 0)
#define BAULK_ZIP_FLAG_LZMA_EOS_MARKER (1 << 1)
#define BAULK_ZIP_FLAG_DEFLATE_MAX (1 << 1)
#define BAULK_ZIP_FLAG_DEFLATE_NORMAL (0)
#define BAULK_ZIP_FLAG_DEFLATE_FAST (1 << 2)
#define BAULK_ZIP_FLAG_DEFLATE_SUPER_FAST (BAULK_ZIP_FLAG_DEFLATE_FAST | BAULK_ZIP_FLAG_DEFLATE_MAX)
#define BAULK_ZIP_FLAG_DATA_DESCRIPTOR (1 << 3)
#define BAULK_ZIP_FLAG_UTF8 (1 << 11)
#define BAULK_ZIP_FLAG_MASK_LOCAL_INFO (1 << 13)

/* BAULK_ZIP_EXTENSION */
#define BAULK_ZIP_EXTENSION_ZIP64 (0x0001)
#define BAULK_ZIP_EXTENSION_NTFS (0x000a)
#define BAULK_ZIP_EXTENSION_AES (0x9901)
#define BAULK_ZIP_EXTENSION_UNIX1 (0x000d)
#define BAULK_ZIP_EXTENSION_SIGN (0x10c5)
#define BAULK_ZIP_EXTENSION_HASH (0x1a51)
#define BAULK_ZIP_EXTENSION_CDCD (0xcdcd)

/* BAULK_ZIP64 */
#define BAULK_ZIP64_AUTO (0)
#define BAULK_ZIP64_FORCE (1)
#define BAULK_ZIP64_DISABLE (2)

/* BAULK_HOST_SYSTEM */
#define BAULK_HOST_SYSTEM(VERSION_MADEBY) ((uint8_t)(VERSION_MADEBY >> 8))
#define BAULK_HOST_SYSTEM_MSDOS (0)
#define BAULK_HOST_SYSTEM_UNIX (3)
#define BAULK_HOST_SYSTEM_WINDOWS_NTFS (10)
#define BAULK_HOST_SYSTEM_RISCOS (13)
#define BAULK_HOST_SYSTEM_OSX_DARWIN (19)

/* BAULK_PKCRYPT */
#define BAULK_PKCRYPT_HEADER_SIZE (12)

/* BAULK_AES */
#define BAULK_AES_VERSION (1)
#define BAULK_AES_ENCRYPTION_MODE_128 (0x01)
#define BAULK_AES_ENCRYPTION_MODE_192 (0x02)
#define BAULK_AES_ENCRYPTION_MODE_256 (0x03)
#define BAULK_AES_KEY_LENGTH(MODE) (8 * (MODE & 3) + 8)
#define BAULK_AES_KEY_LENGTH_MAX (32)
#define BAULK_AES_BLOCK_SIZE (16)
#define BAULK_AES_HEADER_SIZE(MODE) ((4 * (MODE & 3) + 4) + 2)
#define BAULK_AES_FOOTER_SIZE (10)

/* BAULK_HASH */
#define BAULK_HASH_MD5 (10)
#define BAULK_HASH_MD5_SIZE (16)
#define BAULK_HASH_SHA1 (20)
#define BAULK_HASH_SHA1_SIZE (20)
#define BAULK_HASH_SHA256 (23)
#define BAULK_HASH_SHA256_SIZE (32)
#define BAULK_HASH_MAX_SIZE (256)

/* BAULK_ENCODING */
#define BAULK_ENCODING_CODEPAGE_437 (437)
#define BAULK_ENCODING_CODEPAGE_932 (932)
#define BAULK_ENCODING_CODEPAGE_936 (936)
#define BAULK_ENCODING_CODEPAGE_950 (950)
#define BAULK_ENCODING_UTF8 (65001)

namespace baulk::archive::zip {
// https://www.hanshq.net/zip.html
constexpr long ErrCanceled = 654321;

// https://github.com/nih-at/libzip/blob/master/lib/zip.h
typedef enum zip_method_e : uint16_t {
  ZIP_STORE = 0,    /* stored (uncompressed) */
  ZIP_SHRINK = 1,   /* shrunk */
  ZIP_REDUCE_1 = 2, /* reduced with factor 1 */
  ZIP_REDUCE_2 = 3, /* reduced with factor 2 */
  ZIP_REDUCE_3 = 4, /* reduced with factor 3 */
  ZIP_REDUCE_4 = 5, /* reduced with factor 4 */
  ZIP_IMPLODE = 6,  /* imploded */
  /* 7 - Reserved for Tokenizing compression algorithm */
  ZIP_DEFLATE = 8,         /* deflated */
  ZIP_DEFLATE64 = 9,       /* deflate64 */
  ZIP_PKWARE_IMPLODE = 10, /* PKWARE imploding */
  /* 11 - Reserved by PKWARE */
  ZIP_BZIP2 = 12, /* compressed using BZIP2 algorithm */
  /* 13 - Reserved by PKWARE */
  ZIP_LZMA = 14, /* LZMA (EFS) */
  /* 15-17 - Reserved by PKWARE */
  ZIP_TERSE = 18, /* compressed using IBM TERSE (new) */
  ZIP_LZ77 = 19,  /* IBM LZ77 z Architecture (PFS) */
  /* 20 - old value for Zstandard */
  /* ZIP LZMA2*/
  ZIP_LZMA2 = 33,
  ZIP_ZSTD = 93,    /* Zstandard compressed data */
  ZIP_MP3 = 94,     /* MP3 compression data */
  ZIP_XZ = 95,      /* XZ compressed data */
  ZIP_JPEG = 96,    /* Compressed Jpeg data */
  ZIP_WAVPACK = 97, /* WavPack compressed data */
  ZIP_PPMD = 98,    /* PPMd version I, Rev 1 */
  ZIP_AES = 99,     /* AE-x encryption marker (see APPENDIX E) */

  // Private magic number
  ZIP_BROTLI = 121,
} zip_method_t;

struct directoryEnd {
  uint32_t diskNbr{0};            // unused
  uint32_t dirDiskNbr{0};         // unused
  uint64_t dirRecordsThisDisk{0}; // unused
  uint64_t directoryRecords{0};
  uint64_t directorySize{0};
  uint64_t directoryOffset{0}; // relative to file
  uint16_t commentLen;
  std::string comment;
};

// FileMode to string
std::string String(FileMode m);

struct File {
  std::string name;
  std::string comment;
  std::string extra;
  uint64_t compressedSize{0};
  uint64_t uncompressedSize{0};
  uint64_t position{0}; // file position
  bela::Time time;
  uint32_t crc32{0};
  uint32_t externalAttrs{0};
  uint16_t cversion{0};
  uint16_t rversion{0};
  uint16_t flags{0};
  uint16_t method{0};
  uint16_t aesVersion{0};
  uint8_t aesStrength{0};
  bool utf8{false};
  bool IsEncrypted() const { return (flags & 0x1) != 0; }
  bool IsDir() const { return name.ends_with('/'); }
  bool StartsWith(std::string_view prefix) const { return name.starts_with(prefix); }
  bool EndsWith(std::string_view suffix) const { return name.ends_with(suffix); }
  bool Contains(char ch) const { return name.find(ch) != std::string::npos; }
  bool Contains(std::string_view sv) { return name.find(sv) != std::string::npos; }
  baulk::archive::FileMode FileMode() const;
};

constexpr static auto size_max = (std::numeric_limits<std::size_t>::max)();

using Receiver = std::function<bool(const void *data, size_t len)>;
class Reader {
private:
  bool PositionAt(uint64_t pos, bela::error_code &ec) const {
    auto li = *reinterpret_cast<LARGE_INTEGER *>(&pos);
    LARGE_INTEGER oli{0};
    if (SetFilePointerEx(fd, li, &oli, SEEK_SET) != TRUE) {
      ec = bela::make_system_error_code(L"SetFilePointerEx: ");
      return false;
    }
    return true;
  }
  bool ReadFull(void *buffer, size_t len, bela::error_code &ec) const {
    auto p = reinterpret_cast<uint8_t *>(buffer);
    size_t total = 0;
    while (total < len) {
      DWORD dwSize = 0;
      if (ReadFile(fd, p + total, static_cast<DWORD>(len - total), &dwSize, nullptr) != TRUE) {
        ec = bela::make_system_error_code(L"ReadFile: ");
        return false;
      }
      if (dwSize == 0) {
        ec = bela::make_error_code(ERROR_HANDLE_EOF, L"Reached the end of the file");
        return false;
      }
      total += dwSize;
    }
    return true;
  }
  // ReadAt ReadFull
  bool ReadAt(void *buffer, size_t len, uint64_t pos, bela::error_code &ec) const {
    if (!PositionAt(pos, ec)) {
      return false;
    }
    return ReadFull(buffer, len, ec);
  }
  void Free() {
    if (needClosed && fd != INVALID_HANDLE_VALUE) {
      CloseHandle(fd);
      fd = INVALID_HANDLE_VALUE;
    }
  }
  void MoveFrom(Reader &&r) {
    Free();
    fd = r.fd;
    r.fd = INVALID_HANDLE_VALUE;
    needClosed = r.needClosed;
    r.needClosed = false;
    size = r.size;
    r.size = 0;
    uncompressedSize = r.uncompressedSize;
    r.uncompressedSize = 0;
    compressedSize = r.compressedSize;
    r.compressedSize = 0;
    comment = std::move(r.comment);
    files = std::move(r.files);
  }

public:
  Reader() = default;
  Reader(Reader &&r) { MoveFrom(std::move(r)); }
  Reader &operator=(Reader &&r) {
    MoveFrom(std::move(r));
    return *this;
  }
  ~Reader() { Free(); }
  bool OpenReader(std::wstring_view file, bela::error_code &ec);
  bool OpenReader(HANDLE nfd, int64_t sz, bela::error_code &ec);
  Reader &Credential(std::string_view password) {
    passwd.assign(password);
    return *this;
  }
  std::string_view Comment() const { return comment; }
  const auto &Files() const { return files; }
  int64_t CompressedSize() const { return compressedSize; }
  int64_t UncompressedSize() const { return uncompressedSize; }
  static std::optional<Reader> NewReader(HANDLE fd, int64_t sz, bela::error_code &ec) {
    Reader r;
    if (!r.OpenReader(fd, sz, ec)) {
      return std::nullopt;
    }
    return std::make_optional(std::move(r));
  }
  bool Decompress(const File &file, const Receiver &receiver, int64_t &decompressed, bela::error_code &ec) const;

private:
  std::string passwd;
  std::string comment;
  std::vector<File> files;
  HANDLE fd{INVALID_HANDLE_VALUE};
  int64_t size{bela::SizeUnInitialized};
  int64_t uncompressedSize{0};
  int64_t compressedSize{0};
  bool needClosed{false};
  bool Initialize(bela::error_code &ec);
  bool readDirectoryEnd(directoryEnd &d, bela::error_code &ec);
  bool readDirectory64End(int64_t offset, directoryEnd &d, bela::error_code &ec);
  int64_t findDirectory64End(int64_t directoryEndOffset, bela::error_code &ec);
  bool decompressDeflate(const File &file, const Receiver &receiver, int64_t &decompressed, bela::error_code &ec) const;
  bool decompressDeflate64(const File &file, const Receiver &receiver, int64_t &decompressed,
                           bela::error_code &ec) const;
  bool decompressZstd(const File &file, const Receiver &receiver, int64_t &decompressed, bela::error_code &ec) const;
  bool decompressBz2(const File &file, const Receiver &receiver, int64_t &decompressed, bela::error_code &ec) const;
  bool decompressXz(const File &file, const Receiver &receiver, int64_t &decompressed, bela::error_code &ec) const;
  bool decompressLZMA2(const File &file, const Receiver &receiver, int64_t &decompressed, bela::error_code &ec) const;
  bool decompressBrotli(const File &file, const Receiver &receiver, int64_t &decompressed, bela::error_code &ec) const;
};

// NewReader
inline std::optional<Reader> NewReader(HANDLE fd, int64_t size, bela::error_code &ec) {
  return Reader::NewReader(fd, size, ec);
}
//
} // namespace baulk::archive::zip

#endif