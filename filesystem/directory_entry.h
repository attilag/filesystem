#ifndef __DIRECTORY_ENTRY_H__
#define __DIRECTORY_ENTRY_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "path.h"

#include <system_error>

NAMESPACE_BEGIN(filesystem)

class file_status;

class directory_entry {
  public:
    directory_entry() noexcept = default;
    directory_entry(const directory_entry&) = default;
    directory_entry(directory_entry&&) = default;
    explicit directory_entry(const filesystem::path& p);

    ~directory_entry();

    directory_entry& operator=(const directory_entry&) = default;
    directory_entry& operator=(directory_entry&&) = default;

    void assign(const filesystem::path&);

    void replace_filename(const filesystem::path&);

    const class filesystem::path& path() const noexcept
      { return path_; }

    operator const class filesystem::path& () const noexcept
      { return path_; }

    filesystem::file_status status() const;

    filesystem::file_status status(std::error_code& ec) const noexcept;

    filesystem::file_status symlink_status() const;

    filesystem::file_status symlink_status(std::error_code& ec) const noexcept;

    bool operator == (const directory_entry& rhs) const noexcept
      { return path_ == rhs.path_; }

    bool operator != (const directory_entry& rhs) const noexcept
      { return path_ != rhs.path_; }

    bool operator < (const directory_entry& rhs) const noexcept
      { return path_ < rhs.path_; }

    bool operator <= (const directory_entry& rhs) const noexcept
      { return path_ <= rhs.path_; }

    bool operator > (const directory_entry& rhs) const noexcept
      { return path_ > rhs.path_; }

    bool operator >= (const directory_entry& rhs) const noexcept
      { return path_ >= rhs.path_; }

private:
    class filesystem::path path_;

}; // class directory_entry

NAMESPACE_END(filesystem)

#endif // __DIRECTORY_ENTRY_H__
