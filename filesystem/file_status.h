#ifndef __FILE_STATUS_H__
#define __FILE_STATUS_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

NAMESPACE_BEGIN(filesystem)

enum class file_type {
  none      = -1,
  not_found = 0,
  regular   = 1,
  directory = 2,
  symlink   = 3,
  block     = 4,
  character = 5,
  fifo      = 6,
  socket    = 7,
  unknown   = 8
}; // enum class file_type

enum class perms: unsigned int {
  none             = 0,
  owner_read       = 00400,
  owner_write      = 00200,
  owner_exec       = 00100,
  owner_all        = 00700,
  group_read       = 00040,
  group_write      = 00020,
  group_exec       = 00010,
  group_all        = 00070,
  others_read      = 00001,
  others_write     = 00002,
  others_exec      = 00004,
  other_all        = 00007,
  all              = 00777,
  set_uid          = 04000,
  set_gid          = 02000,
  sticky_bit       = 01000,
  mask             = 07777,

  unknown          = 0xffff,
  add_persm        = 0x10000,
  remove_persm     = 0x20000,
  resolve_symlinks = 0x40000
}; // enum class perms;

class file_status {
  public:
    file_status(const file_status&) noexcept = default;
    file_status(file_status&&) noexcept = default;
    explicit file_status(filesystem::file_type type = filesystem::file_type::none,
        filesystem::perms permissions = filesystem::perms::unknown) noexcept
      : file_type_(type), permissions_(permissions) { }
    ~file_status() = default;

    file_status& operator=(const file_status&) noexcept = default;
    file_status& operator=(file_status&&) noexcept = default;

    filesystem::file_type type() const noexcept { return file_type_; }
    void type(filesystem::file_type type) noexcept { file_type_ = type; }

    filesystem::perms permissions() const noexcept { return permissions_; }
    void permissions(filesystem::perms perm) noexcept { permissions_ = perm; }

  private:
    filesystem::file_type file_type_;
    filesystem::perms permissions_;
}; // class file_status

NAMESPACE_END(filesystem)


inline constexpr filesystem::perms
  operator&(filesystem::perms lhs, filesystem::perms rhs) {
    return static_cast<filesystem::perms>(static_cast<int>(lhs) & static_cast<int>(rhs));
  }

inline constexpr filesystem::perms
  operator|(filesystem::perms lhs, filesystem::perms rhs) {
    return static_cast<filesystem::perms>(static_cast<int>(lhs) | static_cast<int>(rhs));
  }

inline constexpr filesystem::perms
  operator^(filesystem::perms lhs, filesystem::perms rhs) {
    return static_cast<filesystem::perms>(static_cast<int>(lhs) ^ static_cast<int>(rhs));
  }

#endif // __FILE_STATUS_H__
